import torch
import torch.nn as nn
import torch.optim as optim
from torch.utils.data import DataLoader
import torchvision
import torchvision.transforms as transforms

# --------------------------
# Simple CNN Mimarisi
# --------------------------

class SimpleCNN(nn.Module):
    def __init__(self, num_classes=10):
        super(SimpleCNN, self).__init__()

        self.features = nn.Sequential(
            nn.Conv2d(3, 32, kernel_size=3, padding=1),  # [B, 32, 64, 64]
            nn.ReLU(),

            nn.Conv2d(32, 64, kernel_size=3, padding=1), # [B, 64, 64, 64]
            nn.ReLU(),
            nn.MaxPool2d(2, 2),                          # [B, 64, 32, 32]

            nn.Conv2d(64, 128, kernel_size=3, padding=1),# [B, 128, 32, 32]
            nn.ReLU(),
            nn.MaxPool2d(2, 2),                          # [B, 128, 16, 16]
        )

        self.classifier = nn.Sequential(
            nn.Flatten(),                                # [B, 128*16*16]
            nn.Linear(128*16*16, 256),
            nn.ReLU(),
            nn.Linear(256, num_classes)
        )

    def forward(self, x):
        x = self.features(x)
        x = self.classifier(x)
        return x


transform = transforms.Compose([
    transforms.Resize((64, 64)),
    transforms.ToTensor(),           # 0-1 aralığı
    # Normalizasyon eklenecekse buraya eklenir
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

train_loader = DataLoader(train_dataset, batch_size=64, shuffle=True)
test_loader  = DataLoader(test_dataset, batch_size=64, shuffle=False)

print("Dataset hazır, model oluşturuluyor...")

model = SimpleCNN(num_classes=10)
print(model)

# Cihaz seçimi
device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
print("Kullanilan cihaz:", device)

# Modeli cihaza taşı
model = SimpleCNN(num_classes=10).to(device)

criterion = nn.CrossEntropyLoss()
optimizer = optim.Adam(model.parameters(), lr=1e-3)

EPOCHS = 1  # İstersen artırabilirsin (ör: 10)

best_acc = 0.0

for epoch in range(EPOCHS):
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

    # Basit bir test/validation değerlendirmesi
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


# Aynı mimariyi yeniden kur
export_model = SimpleCNN(num_classes=10)
export_model.load_state_dict(torch.load("best_model.pth", map_location="cpu"))
export_model.eval()

# Örnek giriş (dummy input)
example_input = torch.randn(1, 3, 64, 64)

# TorchScript trace
traced_script_module = torch.jit.trace(export_model, example_input)

# Kaydet
traced_script_module.save("model_ts.pt")

print("TorchScript modeli kaydedildi: model_ts.pt")
