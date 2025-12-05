// 🔹 SORU 4 – Delete Tail (Son Elemanı Sil)
//
// Aşağıdaki node yapısını kullanarak linked list’in SON elemanını silen
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
//     void delete_tail(Node*& head);
//
// Görev:
//   1) Eğer liste boşsa (head == nullptr):
//          - Hiçbir şey yapma, return et.
//
//   2) Eğer listede SADECE 1 eleman varsa (head->next == nullptr):
//          - O node'u delete et
//          - head = nullptr yap
//          - return
//
//   3) Eğer listede 2 veya daha fazla eleman varsa:
//          - head'den başlayarak, SONDAN BİR ÖNCEKİ düğümü bul:
//                Node* p = head;
//                while (p->next->next != nullptr) {
//                    p = p->next;
//                }
//            Bu döngü bittiğinde:
//                p → sondan bir önceki düğüm
//                p->next → son düğüm (silinecek olan)
//          - temp = p->next al
//          - p->next = nullptr yap
//          - temp'i delete et
//
// Örnek:
//
//   Başlangıç:
//       head → 10 → 20 → 30 → nullptr
//
//   delete_tail(head);
//
//   Sonuç:
//       head → 10 → 20 → nullptr
//
// Kurallar:
//   - head parametresi Node*& olmalı
//   - delete kullanmak zorundasın
//   - Hem 0 elemanlı, hem 1 elemanlı, hem de çok elemanlı liste durumlarını düşün

#include <iostream>

struct Node
{
    int data;
    Node *next;
    Node(int v) : data(v), next(nullptr) {}
};

void delete_tail(Node *&head)
{
    if (head == nullptr)
    {
        return;
    }

    if (head->next == nullptr)
    {
        delete head;
        head = nullptr;
        return;
    }

    Node *p = head;
    while (p->next->next != nullptr)
    {
        p = p->next;
    }

    Node *temp = p->next;
    p->next = nullptr;
    delete temp;
}