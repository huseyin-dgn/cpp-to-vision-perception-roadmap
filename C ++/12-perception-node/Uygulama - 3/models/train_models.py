import os
import time

import torch
import torch.nn as nn
import torch.optim as optim
import torch.nn.functional as F

from torch.utils.data import DataLoader
from torchvision import datasets, transforms


# ============================================================
# 1. Cihaz seçimi
# ============================================================
device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
print(f"[INFO] Using device: {device}")


# ============================================================
# 2. CIFAR-10 transform ve dataset tanımı
#    (C++ tarafında da aynı mean/std kullanılacak)
# ============================================================
# CIFAR-10 standart normalize değerleri:
# mean = (0.4914, 0.4822, 0.4465)
# std  = (0.2470, 0.2435, 0.2616)

transform_train = transforms.Compose([
    transforms.RandomCrop(32, padding=4),
    transforms.RandomHorizontalFlip(),
    transforms.ToTensor(),
    transforms.Normalize(
        mean=(0.4914, 0.4822, 0.4465),
        std=(0.2470, 0.2435, 0.2616),
    ),
])

transform_test = transforms.Compose([
    transforms.ToTensor(),
    transforms.Normalize(
        mean=(0.4914, 0.4822, 0.4465),
        std=(0.2470, 0.2435, 0.2616),
    ),
])

data_root = "./data"

train_dataset = datasets.CIFAR10(
    root=data_root,
    train=True,
    download=True,        # DATASET BURADA OTOMATİK İNDİRİLİYOR
    transform=transform_train
)

test_dataset = datasets.CIFAR10(
    root=data_root,
    train=False,
    download=True,
    transform=transform_test
)

batch_size = 128

train_loader = DataLoader(
    train_dataset,
    batch_size=batch_size,
    shuffle=True,
    num_workers=2,
    pin_memory=True
)

test_loader = DataLoader(
    test_dataset,
    batch_size=batch_size,
    shuffle=False,
    num_workers=2,
    pin_memory=True
)

print(f"[INFO] Train set size: {len(train_dataset)}")
print(f"[INFO] Test set  size: {len(test_dataset)}")


# ============================================================
# 3. Basit bir CIFAR-10 CNN modeli
#    (C++ tarafında sadece TorchScript kullanacağımız için
#     çok karmaşık olmasına gerek yok)
# ============================================================
class Cifar10CNN(nn.Module):
    def __init__(self, num_classes: int = 10):
        super().__init__()

        # 3x32x32
        self.conv1 = nn.Conv2d(3, 32, kernel_size=3, padding=1)   # 32x32x32
        self.conv2 = nn.Conv2d(32, 64, kernel_size=3, padding=1)  # 64x32x32
        self.pool  = nn.MaxPool2d(2, 2)                           # → 64x16x16

        self.conv3 = nn.Conv2d(64, 128, kernel_size=3, padding=1) # 128x16x16
        self.conv4 = nn.Conv2d(128, 128, kernel_size=3, padding=1)# 128x16x16
        # pool → 128x8x8

        self.fc1   = nn.Linear(128 * 8 * 8, 256)
        self.fc2   = nn.Linear(256, num_classes)

        self.dropout = nn.Dropout(0.5)

    def forward(self, x):
        # blok 1
        x = F.relu(self.conv1(x))
        x = F.relu(self.conv2(x))
        x = self.pool(x)

        # blok 2
        x = F.relu(self.conv3(x))
        x = F.relu(self.conv4(x))
        x = self.pool(x)

        # flatten
        x = torch.flatten(x, 1)

        x = self.dropout(F.relu(self.fc1(x)))
        x = self.fc2(x)
        return x


model = Cifar10CNN(num_classes=10).to(device)
print(f"[INFO] Model params: {sum(p.numel() for p in model.parameters())}")


# ============================================================
# 4. Loss, optimizer, training ayarları
# ============================================================
criterion = nn.CrossEntropyLoss()
optimizer = optim.Adam(model.parameters(), lr=1e-3)

num_epochs = 15


# ============================================================
# 5. Train & eval fonksiyonları
# ============================================================
def train_one_epoch(epoch):
    model.train()
    running_loss = 0.0
    correct = 0
    total = 0

    start_time = time.time()

    for batch_idx, (inputs, targets) in enumerate(train_loader):
        inputs = inputs.to(device, non_blocking=True)
        targets = targets.to(device, non_blocking=True)

        optimizer.zero_grad()

        outputs = model(inputs)
        loss = criterion(outputs, targets)
        loss.backward()
        optimizer.step()

        running_loss += loss.item() * inputs.size(0)

        _, predicted = outputs.max(1)
        total += targets.size(0)
        correct += predicted.eq(targets).sum().item()

        if (batch_idx + 1) % 100 == 0:
            print(f"[TRAIN] Epoch [{epoch}/{num_epochs}] "
                  f"Step [{batch_idx+1}/{len(train_loader)}] "
                  f"Loss: {loss.item():.4f}")

    epoch_loss = running_loss / len(train_dataset)
    epoch_acc = 100.0 * correct / total
    elapsed = time.time() - start_time

    print(f"[TRAIN] Epoch {epoch} finished "
          f"Loss: {epoch_loss:.4f}, Acc: {epoch_acc:.2f}%, "
          f"Time: {elapsed:.1f} sec")


def eval_model():
    model.eval()
    correct = 0
    total = 0
    eval_loss = 0.0

    with torch.no_grad():
        for inputs, targets in test_loader:
            inputs = inputs.to(device, non_blocking=True)
            targets = targets.to(device, non_blocking=True)

            outputs = model(inputs)
            loss = criterion(outputs, targets)

            eval_loss += loss.item() * inputs.size(0)

            _, predicted = outputs.max(1)
            total += targets.size(0)
            correct += predicted.eq(targets).sum().item()

    avg_loss = eval_loss / len(test_dataset)
    acc = 100.0 * correct / total
    print(f"[EVAL] Test Loss: {avg_loss:.4f}, Acc: {acc:.2f}%")
    return avg_loss, acc


# ============================================================
# 6. Eğitim döngüsü
# ============================================================
best_acc = 0.0
os.makedirs("checkpoints", exist_ok=True)

for epoch in range(1, num_epochs + 1):
    train_one_epoch(epoch)
    _, acc = eval_model()

    # En iyi modeli kaydet
    if acc > best_acc:
        best_acc = acc
        ckpt_path = f"checkpoints/cifar10_cnn_best.pth"
        torch.save(model.state_dict(), ckpt_path)
        print(f"[SAVE] Yeni en iyi model kaydedildi: {ckpt_path} (Acc: {best_acc:.2f}%)")

print(f"[INFO] Eğitim tamamlandı. En iyi doğruluk: {best_acc:.2f}%")


# ============================================================
# 7. TorchScript export (C++ için)
# ============================================================
# En iyi modeli yeniden yükleyip script'e çeviriyoruz.
best_model = Cifar10CNN(num_classes=10)
best_model.load_state_dict(torch.load("checkpoints/cifar10_cnn_best.pth", map_location="cpu"))
best_model.eval()

example_input = torch.randn(1, 3, 32, 32)
scripted = torch.jit.script(best_model)
os.makedirs("models", exist_ok=True)
script_path = "models/cifar10_cnn_scripted.pt"
scripted.save(script_path)

print(f"[EXPORT] TorchScript model kaydedildi: {script_path}")
