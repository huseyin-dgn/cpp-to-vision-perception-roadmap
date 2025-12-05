# 📘 cpp-to-perception-roadmap

Modern C++ ile bilgisayarlı görü (computer vision) ve algılama (perception) sistemlerine adım adım ilerleyen kapsamlı bir öğrenme ve uygulama yol haritası.  
Bu repo, C++ temellerinden başlayarak OpenCV, LibTorch, TorchScript, CIFAR-10 ve YOLO tabanlı gerçek zamanlı algılama pipeline’larına kadar uzanan **12 bölümlük eksiksiz bir mühendislik eğitim setidir.**

## 🎯 Amaç
Bu çalışma, C++ bilen veya öğrenen bir kişinin aşağıdaki alanlarda uzmanlaşmasını hedefler:
- Görüntü işleme (OpenCV)
- Derin öğrenme inference (LibTorch / TorchScript)
- CIFAR-10 ve YOLO modelleriyle çalışmak
- Modüler Perception Node mimarisi kurmak
- Modern C++ proje yapıları (CMake)
- Gerçek zamanlı algılama sistemi tasarlamak

Hedef, basit kodlardan çıkıp **gerçek bir algılama pipeline’ı** geliştirme becerisini kazanmaktır.

---

## 📂 Bölümler (Klasör Yapısı)

01-temel-cpp  
02-fonksiyon-ve-pointer  
03-pointer-ve-bellek  
04-oop-temelleri  
05-ileri-oop  
06-veri-yapilari  
07-cpp-kolayliklari  
08-hata-ayiklama-try-catch  
09-cmake  
10-opencv  
11-libtorch  
12-perception-node  

---

## 📌 Bölüm Detayları

### **01 – Temel C++**  
C++ sözdizimi, giriş/çıkış, veri tipleri, koşullar, döngüler.  
**12 temel örnek**

### **02 – Fonksiyonlar & Pointer**  
Value/reference, pointer mantığı.  
**10 örnek**

### **03 – Pointer Arithmetic & Bellek**  
Pointer arithmetic, dynamic memory, smart pointer temeli.  
**15 örnek**

### **04 – OOP Temelleri**  
Class, constructor, destructor, encapsulation.  
**8 örnek**

### **05 – İleri OOP**  
Inheritance, polymorphism, virtual functions, move semantics.  
**10 örnek**

### **06 – Veri Yapıları**  
- 20 dizi algoritması  
- 8 linked list algoritması  
- 9 sıralama algoritması  
**Toplam: 37 algoritma**

### **07 – C++ Kolaylıkları**  
10 int algoritması, 10 string algoritması, 10 vector uygulaması.  
**Toplam: 30 uygulama**

### **08 – Hata Ayıklama**  
Try/catch, istisna yönetimi.  
**5 örnek**

### **09 – CMake**  
Modern proje yapısı ve bağımlılık ekleme.  
**4 proje**

### **10 – OpenCV**  
10 görüntü işleme + 11 video akış uygulaması.  
**Toplam: 21 OpenCV uygulaması**

### **11 – LibTorch**  
TorchScript model yükleme, tensor işlemleri, inference pipeline.  
**8 LibTorch uygulaması**

### **12 – Perception Node**  
ImageFrame, DetectedObject, PerceptionNode, CIFAR10 inference, YOLO realtime detection.  
**5 algılama projesi**

---

## 🧩 Genel Öğrenme Diyagramı

Bu diyagram, C++ temelinden başlayıp gerçek zamanlı algılama modülüne (Perception Node) kadar uzanan tek yönlü ve katmanlı bir öğrenme yolunu ifade eder:

```bash
[ Temel C++ ]
▼
[ Fonksiyon & Pointer ]
▼
[ Pointer & Bellek ]
▼
[ OOP Temelleri ]
▼
[ İleri OOP ]
▼
[ Veri Yapıları & Kolaylıklar ]
▼
[ Hata Ayıklama & CMake ]
▼
[ OpenCV ]
▼
[ LibTorch ]
▼
[ Perception Node ]
```



---

## 🔁 Algılama Pipeline Akış Şeması (PerceptionNode)

```bash
flowchart LR
A[Camera / Video Source] --> B[ImageFrame oluştur]
B --> C[Preprocess (cv::Mat → Tensor)]
C --> D[Model Inference (LibTorch / TorchScript)]
D --> E[Postprocess (bbox, score, class)]
E --> F[DetectedObject listesi]
F --> G[Çizim & Gösterim (OpenCV window)]
```


Bu akış şeması, `12-perception-node` bölümünde geliştirilen projelerin temel mimarisidir:

- **Giriş:** Kamera veya video kaynağı  
- **Orta Katman:** Preprocess + Inference + Postprocess  
- **Çıkış:** Tespit edilen nesneler + görselleştirme  

---

## 🧠 Bu Repo Kimler İçin?
- C++ öğrenip gerçek dünyada uygulamak isteyenler  
- Görüntü işleme + derin öğrenmeyi C++ ile birleştirmek isteyenler  
- Model inference tarafında uzmanlaşmak isteyenler  
- Otonom sürüş, savunma, robotik gibi perception odaklı alanlara hazırlananlar  

---

## 🚀 Sonuç
Bu repo, C++ temellerinden başlayarak gerçek zamanlı algılama sistemlerinin çekirdek tasarımına kadar uzanan **tam kapsamlı bir perception roadmap** sunar.  
Her bölüm, sayısal olarak tanımlanmış örnekler ve projelerle gerçek mühendislik pratiğini öğretir.  
C++ → OpenCV → LibTorch → PerceptionNode zincirini uçtan uca görmek isteyenler için referans niteliğindedir.


