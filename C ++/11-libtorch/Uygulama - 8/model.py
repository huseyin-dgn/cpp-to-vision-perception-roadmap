import torch
from ultralytics import YOLO

def main():
    # 1) Hangi modeli kullanacağım?
    # yolov8n.pt (nano), yolov8s.pt (small) vs. seçebilirsin.
    model_name = "yolov8n.pt"

    print(f"[INFO] YOLOv8 modeli yukleniyor: {model_name}")
    model = YOLO(model_name)  # Ultralytics, hazır egitimli modeli indirip yüklüyor

    # 2) TorchScript'e export
    # format="torchscript" -> .torchscript uzantılı dosya üretir
    # imgsz=640 -> girdi boyutu (C++ tarafında da 640x640 kullanacağız)
    # nms=True  -> NMS'i export edilen modele gömer (C++ tarafını basitleştirir)
    print("[INFO] TorchScript formatina export ediliyor...")
    ts_path = model.export(
        format="torchscript",
        imgsz=640,
        nms=True,
        batch=1
    )

    print(f"[OK] TorchScript modeli olusturuldu: {ts_path}")
    print("Bu dosyayi C++ projemde model olarak kullanacagim.")

if __name__ == "__main__":
    # Gerekli paketler:
    # pip install ultralytics torch torchvision
    main()
