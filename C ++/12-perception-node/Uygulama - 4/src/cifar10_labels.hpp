#ifndef CIFAR10_LABELS_HPP
#define CIFAR10_LABELS_HPP

#include <vector>
#include <string>

// CIFAR-10 sınıf etiketleri (model çıkışıyla aynı sırada olmalı)
static const std::vector<std::string> CIFAR10_LABELS = {
    "airplane",   // 0
    "automobile", // 1
    "bird",       // 2
    "cat",        // 3
    "deer",       // 4
    "dog",        // 5
    "frog",       // 6
    "horse",      // 7
    "ship",       // 8
    "truck"       // 9
};

#endif // CIFAR10_LABELS_HPP
