import torch
import torch.nn as nn
import torch.optim as optim
from torch.utils.data import DataLoader
import torchvision
import torchvision.transforms as transforms

# --------------------------
# Geliştirilmiş CNN Mimarisi
# --------------------------

class ConvBlock(nn.Module):
    def __init__(self, in_channels, out_channels, kernel_size=3, padding=1):
        super(ConvBlock, self).__init__()
        self.block = nn.Sequential(
            nn.Conv2d(in_channels, out_channels, kernel_size=kernel_size, padding=padding),
            nn.BatchNorm2d(out_channels),
            nn.ReLU(inplace=True)
        )

    def forward(self, x):
        return self.block(x)


class ImprovedCNN(nn.Module):
    def __init__(self, num_classes=10):
        super(ImprovedCNN, self).__init__()

        self.features = nn.Sequential(
            # Giriş: [B, 3, 64, 64]
            ConvBlock(3, 32),              # [B, 32, 64, 64]
            ConvBlock(32, 64),             # [B, 64, 64, 64]
            nn.MaxPool2d(2, 2),            # [B, 64, 32, 32]

            ConvBlock(64, 128),            # [B, 128, 32, 32]
            ConvBlock(128, 128),           # [B, 128, 32, 32]
            nn.MaxPool2d(2, 2),            # [B, 128, 16, 16]

            ConvBlock(128, 256),           # [B, 256, 16, 16]
            nn.MaxPool2d(2, 2),            # [B, 256, 8, 8]

            # Global Average Pooling: [B, 256, 1, 1]
            nn.AdaptiveAvgPool2d((1, 1))
        )

        self.classifier = nn.Sequential(
            nn.Flatten(),                  # [B, 256]
            nn.Linear(256, 128),
            nn.ReLU(inplace=True),
            nn.Dropout(p=0.5),
            nn.Linear(128, num_classes)    # [B, num_classes]
        )

    def forward(self, x):
        x = self.features(x)
        x = self.classifier(x)
        return x


# --------------------------
# Veri hazırlığı
# --------------------------

# CIFAR-10 için tipik normalize değerleri (RGB)
transform = transforms.Compose([
    transforms.Resize((64, 64)),
    transforms.ToTensor(),  # 0-1
    transforms.Normalize(
        mean=[0.4914, 0.4822, 0.4465],
        std=[0.2470, 0.2435, 0.2616]
    ),
])

train_dataset = torchvision.datasets.CIFAR10(
    root="./data",
    train=True,
    download=True,
    transform=transform
)

test_dataset = torchvision.datasets.CIFAR10(
    root="./data",
    train=False,
    download=True,
    transform=transform
)

train_loader = DataLoader(train_dataset, batch_size=64, shuffle=True, num_workers=2)
test_loader  = DataLoader(test_dataset, batch_size=64, shuffle=False, num_workers=2)

print("Dataset hazır, model oluşturuluyor...")

# --------------------------
# Model, cihaz, loss, optimizer
# --------------------------

device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
print("Kullanilan cihaz:", device)

model = ImprovedCNN(num_classes=10).to(device)
print(model)

criterion = nn.CrossEntropyLoss()
optimizer = optim.Adam(model.parameters(), lr=1e-3)
# İstersen scheduler da ekleyebilirsin:
# scheduler = optim.lr_scheduler.StepLR(optimizer, step_size=10, gamma=0.1)

EPOCHS = 1  # İstersen artır (10-20 arası daha makul)


# --------------------------
# Eğitim + basit eval döngüsü
# --------------------------

best_acc = 0.0

for epoch in range(EPOCHS):
    # ---- Train ----
    model.train()
    running_loss = 0.0
    correct = 0
    total = 0

    for images, labels in train_loader:
        images = images.to(device)
        labels = labels.to(device)

        optimizer.zero_grad()

        outputs = model(images)
        loss = criterion(outputs, labels)

        loss.backward()
        optimizer.step()

        running_loss += loss.item()
        _, preds = outputs.max(1)
        correct += preds.eq(labels).sum().item()
        total += labels.size(0)

    train_loss = running_loss / len(train_loader)
    train_acc = 100.0 * correct / total

    # ---- Eval (test) ----
    model.eval()
    correct_test = 0
    total_test = 0

    with torch.no_grad():
        for images, labels in test_loader:
            images = images.to(device)
            labels = labels.to(device)

            outputs = model(images)
            _, preds = outputs.max(1)
            correct_test += preds.eq(labels).sum().item()
            total_test += labels.size(0)

    test_acc = 100.0 * correct_test / total_test

    # scheduler kullanıyorsan burada step:
    # scheduler.step()

    print(f"Epoch [{epoch+1}/{EPOCHS}] | "
          f"Train Loss: {train_loss:.4f} | "
          f"Train Acc: {train_acc:.2f}% | "
          f"Test Acc: {test_acc:.2f}%")

    # En iyi modeli kaydet
    if test_acc > best_acc:
        best_acc = test_acc
        torch.save(model.state_dict(), "best_model.pth")
        print(f"  -> Yeni en iyi model kaydedildi! (best_model.pth, acc={best_acc:.2f}%)")

print("Egitim tamamlandi. En iyi test accuracy:", best_acc)


# --------------------------
# TorchScript export (LibTorch için)
# --------------------------

# Aynı mimariyi yeniden kur
export_model = ImprovedCNN(num_classes=10)
export_model.load_state_dict(torch.load("best_model.pth", map_location="cpu"))
export_model.eval()

# Örnek giriş (dummy input)
example_input = torch.randn(1, 3, 64, 64)

# TorchScript trace
traced_script_module = torch.jit.trace(export_model, example_input)

# Kaydet
traced_script_module.save("model_ts.pt")

print("TorchScript modeli kaydedildi: model_ts.pt")
