// 🔹 SORU 3 – Delete Head (Baştaki Elemanı Sil)
//
// Aşağıdaki node yapısını kullanarak linked list’in BAŞINDAKİ elemanı silen
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
//     void delete_head(Node*& head);
//
// Görev:
//   1) Eğer liste boşsa (head == nullptr):
//          - Hiçbir şey yapma, sadece return et
//
//   2) Eğer liste boş değilse:
//          - Eski head’i geçici bir pointer’da tut: temp = head
//          - head’i bir sonrakine kaydır: head = head->next
//          - temp’i delete ile serbest bırak: delete temp
//
// Örnek:
//
//   Başlangıç:
//       head → 10 → 20 → 30 → nullptr
//
//   delete_head(head);
//
//   Sonuç:
//       head → 20 → 30 → nullptr
//
//   delete_head(head);  // tekrar
//
//   Sonuç:
//       head → 30 → nullptr
//
//   delete_head(head);  // tekrar
//
//   Sonuç:
//       head → nullptr
//
// Kurallar:
//   - head parametresi Node*& (referans) olmalı, çünkü head değişebilir
//   - delete kullanmak ZORUNLU (artık hafızayı da temizliyoruz)
//   - Boş listeyi (head == nullptr) patlatmayacaksın, önce kontrol edeceksin

#include <iostream>

struct Node
{
    int data;
    Node *next;
    Node(int v) : data(v), next(nullptr) {}
};

void delete_head(Node *&head)
{
    if (head == nullptr)
    {
        return;
    }

    Node *tmp = head;
    head = head->next;
    delete tmp;
}
