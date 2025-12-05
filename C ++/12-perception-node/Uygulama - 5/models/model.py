import torch
import torch.nn as nn
import torch.nn.functional as F


class SimpleYoloDetector(nn.Module):
    """
    Girdi:  x -> [1, 3, 640, 640]
    Çıktı:  [N, 6]  (her satır: [x1, y1, x2, y2, score, class_id])

    - 640x640 input varsayar.
    - Basit bir backbone + tek seviyeli detection head.
    - YOLO benzeri mantık:
        - Her grid hücresi için (x, y, w, h, obj, sınıf logits)
        - Sigmoid + softmax + skor threshold
    """

    def __init__(self, num_classes: int = 80, score_threshold: float = 0.25):
        super().__init__()
        self.num_classes = num_classes
        self.score_threshold = score_threshold

        # Basit backbone (gerçek YOLO değil, ama detection mantığına uygun)
        self.backbone = nn.Sequential(
            # [3, 640, 640] -> [32, 320, 320]
            nn.Conv2d(3, 32, kernel_size=3, stride=2, padding=1),
            nn.BatchNorm2d(32),
            nn.SiLU(inplace=True),

            # [32, 320, 320] -> [64, 160, 160]
            nn.Conv2d(32, 64, kernel_size=3, stride=2, padding=1),
            nn.BatchNorm2d(64),
            nn.SiLU(inplace=True),

            # [64, 160, 160] -> [128, 80, 80]
            nn.Conv2d(64, 128, kernel_size=3, stride=2, padding=1),
            nn.BatchNorm2d(128),
            nn.SiLU(inplace=True),

            # [128, 80, 80] -> [256, 40, 40]
            nn.Conv2d(128, 256, kernel_size=3, stride=2, padding=1),
            nn.BatchNorm2d(256),
            nn.SiLU(inplace=True),

            # [256, 40, 40] -> [256, 20, 20]
            nn.Conv2d(256, 256, kernel_size=3, stride=2, padding=1),
            nn.BatchNorm2d(256),
            nn.SiLU(inplace=True),
        )

        # Tek anchor, tek seviye head: [B, 5 + num_classes, H, W]
        out_channels = 5 + num_classes  # x, y, w, h, obj + C sınıf
        self.head = nn.Conv2d(256, out_channels, kernel_size=1, stride=1, padding=0)

    def forward(self, x: torch.Tensor) -> torch.Tensor:
        """
        x: [1, 3, 640, 640]
        return: [N, 6] tensor (x1, y1, x2, y2, score, class_id)
        """
        # Sadece batch=1 kullanımını hedefliyoruz.
        assert x.dim() == 4 and x.size(0) == 1, "Bu model batch=1 için tasarlandı."
        _, _, in_h, in_w = x.shape
        assert in_h == 640 and in_w == 640, "Girdi boyutu 640x640 olmalı."

        # Backbone
        feat = self.backbone(x)       # [1, 256, h, w]
        pred = self.head(feat)        # [1, 5+C, h, w]

        b, ch, h, w = pred.shape      # b=1
        # [1, 5+C, h, w] -> [1, h, w, 5+C] -> [1, h*w, 5+C]
        pred = pred.permute(0, 2, 3, 1).contiguous().view(1, h * w, 5 + self.num_classes)

        # Ayır: bbox(4), obj(1), cls_logits(C)
        bbox_raw = pred[:, :, 0:4]                # [1, N, 4]  (cx, cy, w, h) normalized
        obj_logit = pred[:, :, 4]                 # [1, N]
        cls_logits = pred[:, :, 5:]               # [1, N, C]

        # Box değerlerini [0,1] aralığında tut, sonra 640 ile çarp
        bbox_norm = bbox_raw.sigmoid()            # [1, N, 4]

        cx = bbox_norm[:, :, 0] * 640.0           # [1, N]
        cy = bbox_norm[:, :, 1] * 640.0
        bw = bbox_norm[:, :, 2] * 640.0
        bh = bbox_norm[:, :, 3] * 640.0

        # (cx, cy, w, h) -> (x1, y1, x2, y2)
        x1 = cx - bw / 2.0
        y1 = cy - bh / 2.0
        x2 = cx + bw / 2.0
        y2 = cy + bh / 2.0

        # Kırp: 0–640 arası
        x1 = torch.clamp(x1, 0.0, 640.0)
        y1 = torch.clamp(y1, 0.0, 640.0)
        x2 = torch.clamp(x2, 0.0, 640.0)
        y2 = torch.clamp(y2, 0.0, 640.0)

        # Sınıf skorları
        obj = obj_logit.sigmoid()                 # [1, N]
        cls_probs = F.softmax(cls_logits, dim=-1) # [1, N, C]
        # En yüksek sınıfı seç
        cls_scores, cls_ids = torch.max(cls_probs, dim=-1)  # [1, N], [1, N]

        final_scores = obj * cls_scores           # [1, N]

        # Score threshold uygula
        scores_0 = final_scores[0]                # [N]
        keep_mask = scores_0 > self.score_threshold

        if keep_mask.sum().item() == 0:
            # Hiç tespit yoksa [0,6] döndür
            return torch.zeros((0, 6), dtype=torch.float32, device=x.device)

        x1_0 = x1[0][keep_mask]
        y1_0 = y1[0][keep_mask]
        x2_0 = x2[0][keep_mask]
        y2_0 = y2[0][keep_mask]
        scores_kept = scores_0[keep_mask]
        cls_ids_kept = cls_ids[0][keep_mask].to(torch.float32)

        n = x1_0.size(0)
        out = torch.zeros((n, 6), dtype=torch.float32, device=x.device)
        out[:, 0] = x1_0
        out[:, 1] = y1_0
        out[:, 2] = x2_0
        out[:, 3] = y2_0
        out[:, 4] = scores_kept
        out[:, 5] = cls_ids_kept

        return out


if __name__ == "__main__":
    # Parametreleri istersen değiştir
    num_classes = 80
    score_threshold = 0.25

    model = SimpleYoloDetector(num_classes=num_classes,
                               score_threshold=score_threshold)
    model.eval()

    # Örnek girdi: [1, 3, 640, 640]
    example = torch.randn(1, 3, 640, 640)

    # TorchScript'e çevir ve kaydet
    scripted = torch.jit.script(model)
    scripted.save("yolo_detector.torchscript.pt")

    print("Kaydedildi: yolo_detector.torchscript.pt")
