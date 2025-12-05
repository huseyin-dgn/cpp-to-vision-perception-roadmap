import torch
import torch.nn as nn
import torch.nn.functional as F

class SimpleCNN(nn.Module):
    def __init__(self, num_classes: int = 10):
        super().__init__()
        # [B, 3, 64, 64]
        self.conv1 = nn.Conv2d(3, 16, kernel_size=3, padding=1)   # [B,16,64,64]
        self.conv2 = nn.Conv2d(16, 32, kernel_size=3, padding=1)  # [B,32,64,64]
        self.pool = nn.MaxPool2d(2, 2)                            # boyut yarıya iner
        self.conv3 = nn.Conv2d(32, 64, kernel_size=3, padding=1)  # [B,64,16,16] civarı
        self.avgpool = nn.AdaptiveAvgPool2d((4, 4))               # [B,64,4,4]
        self.fc = nn.Linear(64 * 4 * 4, num_classes)              # [B,10]

    def forward(self, x):
        x = F.relu(self.conv1(x))     # [B,16,64,64]
        x = self.pool(x)              # [B,16,32,32]
        x = F.relu(self.conv2(x))     # [B,32,32,32]
        x = self.pool(x)              # [B,32,16,16]
        x = F.relu(self.conv3(x))     # [B,64,16,16]
        x = self.avgpool(x)           # [B,64,4,4]
        x = torch.flatten(x, 1)       # [B,64*4*4]
        x = self.fc(x)                # [B,10]
        return x

if __name__ == "__main__":
    # 1) Modeli oluştur
    num_classes = 10
    model = SimpleCNN(num_classes=num_classes)
    model.eval()

    # 2) Örnek giriş tensörü (dummy)
    example_input = torch.randn(1, 3, 64, 64)

    # 3) TorchScript trace
    traced = torch.jit.trace(model, example_input)

    # 4) Kaydet
    traced.save("model_ts.pt")
    print("TorchScript model kaydedildi: model_ts.pt")