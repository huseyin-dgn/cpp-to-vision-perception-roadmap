Buraya TorchScript formatında YOLO tabanlı bir dedektör modeli koymalısın.
Dosya adı varsayılan olarak:

  yolo_detector.torchscript.pt

C++ kodu, modelin forward çağrısının tek bir görüntü için aşağıdaki formatta
bir tensor döndürdüğünü varsayar:

  shape: [N, 6]
  her satır: [x1, y1, x2, y2, score, class_id]

x1, y1, x2, y2 koordinatları, 640x640 giriş boyutuna göredir. Uygulama
bunları orijinal frame boyutuna ölçekler.
