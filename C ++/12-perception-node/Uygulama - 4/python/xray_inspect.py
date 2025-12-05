import torch
import torch.nn.functional as F
from torchvision import transforms
from PIL import Image

import os
import sys

MEAN = (0.4914, 0.4822, 0.4465)
STD  = (0.2470, 0.2435, 0.2616)

transform = transforms.Compose([
    transforms.Resize((32, 32)),
    transforms.ToTensor(),
    transforms.Normalize(MEAN, STD),
])

CIFAR10_LABELS = [
    "airplane",
    "automobile",
    "bird",
    "cat",
    "deer",
    "dog",
    "frog",
    "horse",
    "ship",
    "truck"
]


def load_image(image_path: str):
    img = Image.open(image_path).convert("RGB")
    return img


def xray_preprocess(image_path: str):
    img = load_image(image_path)
    print(f"[PY-XRAY] Orijinal boyut: {img.size} (width, height)")

    tensor = transform(img)  # [C, H, W]
    print(f"[PY-XRAY] Tensor shape (CHW): {tensor.shape}")

    tensor_batched = tensor.unsqueeze(0)  # [1, C, H, W]
    print(f"[PY-XRAY] Tensor shape (NCHW): {tensor_batched.shape}")

    c0 = tensor[0, 0, 0].item()
    c1 = tensor[1, 0, 0].item()
    c2 = tensor[2, 0, 0].item()
    print(f"[PY-XRAY] (0,0) normalized RGB: "
          f"R={c0:.4f}, G={c1:.4f}, B={c2:.4f}")

    return tensor_batched


def xray_inference(model_path: str, image_path: str):
    device = torch.device("cpu")
    model = torch.jit.load(model_path, map_location=device)
    model.eval()

    input_tensor = xray_preprocess(image_path)

    with torch.no_grad():
        logits = model(input_tensor)

    print(f"[PY-XRAY] Logits shape: {logits.shape}")

    print("[PY-XRAY] İlk 10 logits:")
    for i in range(min(10, logits.shape[1])):
        val = logits[0, i].item()
        print(f"  class {i} ({CIFAR10_LABELS[i]}): {val:.4f}")

    probs = F.softmax(logits, dim=1)
    print("[PY-XRAY] Top-5 olasılıklar:")

    topk_vals, topk_idx = probs.topk(5, dim=1)
    for rank in range(5):
        idx = topk_idx[0, rank].item()
        val = topk_vals[0, rank].item()
        print(f"  #{rank+1}: id={idx}, "
              f"name={CIFAR10_LABELS[idx]}, "
              f"score={val:.4f}")


if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Kullanım: python xray_inspect.py MODEL_PATH IMAGE_PATH")
        sys.exit(1)

    model_path = sys.argv[1]
    image_path = sys.argv[2]

    if not os.path.exists(model_path):
        print(f"Model bulunamadı: {model_path}")
        sys.exit(1)

    if not os.path.exists(image_path):
        print(f"Resim bulunamadı: {image_path}")
        sys.exit(1)

    xray_inference(model_path, image_path)
