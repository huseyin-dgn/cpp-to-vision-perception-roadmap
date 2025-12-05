// 🔹 SORU 7 – Search (Değer Arama)
//
// Aşağıdaki node yapısını kullanarak, verilen değeri linked list içinde
// ARAYAN bir fonksiyon yaz.
//
// struct Node {
//     int data;
//     Node* next;
//     Node(int v) : data(v), next(nullptr) {}
// };
//
// Fonksiyon imzası:
//
//     Node* search(Node* head, int value);
//
// Davranış:
//
//   - head'ten başlayarak sona kadar (nullptr olana kadar) ilerle
//   - Her adımda:
//        - Eğer current->data == value ise:
//              → current'ı return et (bulduğun node'un adresini döndür)
//   - Liste sonuna kadar gidip bulamazsan:
//        → nullptr döndür
//
// Örnek:
//
//   Liste:
//       head → 10 → 20 → 30 → nullptr
//
//   Node* p = search(head, 20);
//       → p, data'sı 20 olan düğümü gösterir
//
//   Node* q = search(head, 99);
//       → q == nullptr (çünkü 99 yok)
//
// Kurallar:
//
//   - Listeyi BOZMAYACAKSIN, sadece okuyorsun
//   - head parametresi referans olmak zorunda değil, değiştirmiyoruz:
//         Node* head
//   - Sadece next ile yürüyerek ara (dizi gibi index yok)
//   - Bulursan Node* döndür, bulamazsan nullptr
//
// İpucu:
//   Node* p = head;
//   while (p != nullptr) {
//       // kontrol
//       p = p->next;
//   }

#include <iostream>

struct Node
{
    int data;
    Node *next;
    Node(int v) : data(v), next(nullptr) {}
};

Node *search(Node *head, int value)
{
    if (head == nullptr)
    {
        return nullptr;
    }

    Node *p = head;

    while (p != nullptr)
    {
        if (p->data == value)
        {
            return p;
        }
        p = p->next;
    }
    return nullptr;
}
