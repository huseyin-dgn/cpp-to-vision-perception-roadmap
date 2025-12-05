// 🔹 SORU 6 – Insert at Position (Index'e Göre Araya Ekleme)
//
// Aşağıdaki node yapısını kullanarak, verilen index'e yeni bir değer ekleyen
// fonksiyonu yaz.
//
// struct Node {
//     int data;
//     Node* next;
//     Node(int v) : data(v), next(nullptr) {}
// };
//
// Fonksiyon imzası:
//
//     void insert_at_position(Node*& head, int index, int value);
//
// Davranış:
//
//   - Eğer index 0 ise:
//        → Baştan ekle (insert_at_head mantığı):
//             - newNode oluştur
//             - newNode->next = head
//             - head = newNode
//
//   - Eğer index > 0 ise:
//        → head'den başlayarak index - 1 adım ilerle:
//             Node* p = head;
//             int i = 0;
//             while (i < index - 1 && p != nullptr) {
//                 p = p->next;
//                 i++;
//             }
//        → Eğer p == nullptr ise:
//             → index out of range, hiçbir şey yapma (veya sona ekleyebilirsin, ama şimdilik boşver).
//        → Aksi halde:
//             - newNode oluştur
//             - newNode->next = p->next
//             - p->next = newNode
//
// Örnek:
//
//   Liste:
//       head → 10 → 20 → 30 → nullptr
//
//   insert_at_position(head, 0, 5);
//       → 5 → 10 → 20 → 30 → nullptr
//
//   insert_at_position(head, 2, 99); // index 2'ye 99 ekle
//       → 5 → 10 → 99 → 20 → 30 → nullptr
//
// Kurallar:
//   - head parametresi Node*& olmalı
//   - new ile node oluşturmalısın
//   - index 0 ve index > 0 için ayrı mantık kur

#include <iostream>

struct Node
{
    int data;
    Node *next;
    Node(int v) : data(v), next(nullptr) {}
};

void insert_at_position(Node *&head, int index, int value)
{
    if (head == nullptr)
    {
        return;
    }
    if (index == 0)
    {
        Node *newNode = new Node(value);
        newNode->next = head;
        head = newNode;
        return;
    }

    if (index > 0)
    {
        Node *p = head;
        int i = 0;
        while (i < index - 1 && p != nullptr)
        {
            p = p->next;
            i++;
        }

        Node *newNode1 = new Node(value);
        newNode1->next = p->next;
        p->next = newNode1;
    }
}