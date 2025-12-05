// 🔹 SORU 5 – Delete at Position (Index'e Göre Silme)
//
// Aşağıdaki node yapısını kullanarak, verilen index'teki elemanı
// linked list'ten silen fonksiyonu yaz.
//
// struct Node {
//     int data;
//     Node* next;
//     Node(int v) : data(v), next(nullptr) {}
// };
//
// Fonksiyon imzası:
//
//     void delete_at_position(Node*& head, int index);
//
// Davranış:
//
//   - Eğer liste boşsa (head == nullptr):
//        → Hiçbir şey yapma, return et.
//
//   - index 0 ise:
//        → Baştaki elemanı sil (delete_head mantığı):
//             - temp = head
//             - head = head->next
//             - delete temp
//
//   - index > 0 ise:
//        → head'den başlayarak, index - 1 adım ilerle:
//             Node* p = head;
//             int i = 0;
//             while (i < index - 1 && p != nullptr) {
//                 p = p->next;
//                 i++;
//             }
//        → Eğer p == nullptr veya p->next == nullptr ise:
//             → index out of range, hiçbir şey silme, return et.
//        → Aksi halde:
//             - silinecek = p->next
//             - p->next = p->next->next
//             - delete silinecek
//
// Örnek:
//
//   Liste:
//       head → 10 → 20 → 30 → 40 → nullptr
//
//   delete_at_position(head, 0);
//       → 20 → 30 → 40 → nullptr
//
//   delete_at_position(head, 1);  // (şu an index 1'de 30 var)
//       → 20 → 40 → nullptr
//
// Kurallar:
//
//   - head parametresi Node*& olmalı
//   - delete kullanmak zorundasın
//   - index'in 0 veya pozitif olduğunu varsayabilirsin
//   - Güvenlik için p veya p->next nullptr olursa hiçbir şey yapmadan return edebilirsin

#include <iostream>

struct Node
{
    int data;
    Node *next;
    Node(int v) : data(v), next(nullptr) {}
};

void delete_at_position(Node *&head, int index)
{
    if (head == nullptr)
    {
        return;
    }

    if (index == 0)
    {
        Node *temp = head;
        head = head->next;
        delete temp;
        return;
    }

    Node *p = head;
    int i = 0;
    while (i < index - 1 && p != nullptr)
    {
        p = p->next;
        i++;
    }

    if (p == nullptr || p->next == nullptr)
    {
        return;
    }

    Node *silinecek = p->next;
    p->next = p->next->next;
    delete silinecek;
}