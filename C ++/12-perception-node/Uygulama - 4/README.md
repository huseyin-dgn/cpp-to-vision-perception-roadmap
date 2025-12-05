# CIFAR-10 Perception X-Ray Projesi

Bu proje, CIFAR-10 veri kümesi üzerinde eğitilmiş bir CNN modelini
TorchScript formatında C++ (LibTorch + OpenCV) tarafında kullanarak
hem normal bir sınıflandırma pipeline'ı, hem de bu pipeline'ın içini
inceleyen bir **X-Ray / Denetleyici modu** sağlar.

## Klasör Yapısı

- `CMakeLists.txt`  
- `src/`  
  - `frame_types.hpp`  
  - `cifar10_labels.hpp`  
  - `preprocess_node.hpp/.cpp`  
  - `classifier_node.hpp/.cpp`  
  - `main.cpp`  
- `python/`  
  - `train_cifar10.py` → CIFAR-10 CNN eğitimi + TorchScript export  
  - `xray_inspect.py` → Python tarafında X-Ray incelemesi  
- `models/`  
  - `cifar10_cnn_scripted.pt` (Python tarafında üretip buraya koymalısın)  
- `docs/`  
  - `*_aciklamalar.ipynb` → Her kaynak dosya için açıklama not defterleri
