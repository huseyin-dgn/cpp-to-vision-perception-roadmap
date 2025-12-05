# YOLO Perception Realtime Project (C++ / LibTorch / OpenCV)

Kaynak:
- `src/main.cpp` gerçek zamanlı akış (kamera veya video) üzerinde YOLO tabanlı nesne tespiti yapar.
- Giriş: webcam index (0,1,2) veya video dosyası yolu.
- Çıktı: OpenCV penceresinde çizilmiş bbox + skorlar.

Derleme (örnek):

```bash
mkdir build
cd build
cmake .. -DCMAKE_PREFIX_PATH="LIBTORCH_KLASORUN"
cmake --build .
```

Çalıştırma (örnek):

```bash
./yolo_perception 0 --model ../models/yolo_detector.torchscript.pt
```

Model dosyasının formatı için `models/README_models.txt` dosyasına bak.
