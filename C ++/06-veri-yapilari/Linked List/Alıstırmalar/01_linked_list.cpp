// 🔹 SORU 2 – Insert at Tail
//
// Aşağıdaki node yapısını kullanarak linked list’in SONUNA eleman ekleyen
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
//     void insert_at_tail(Node*& head, int value);
//
// Görev:
//   1) Yeni bir node oluştur (newNode)
//   2) Eğer liste boşsa:
//          head = newNode
//          return
//   3) Liste boş değilse:
//          tail’i bulmak için head’ten itibaren sona kadar ilerle
//          tail->next = newNode
//
// Kurallar:
//   - new kullanıyoruz, delete yok (şu an için)
//   - next pointer'ı doğru bağla
//   - Döngü ile sona kadar yürümek zorundasın
//   - tail diye ayrı bir pointer YOK, kendin bulacaksın
//
// Örnek:
//
//   Başlangıç:
//       head → 10 → 20 → nullptr
//
//   insert_at_tail(head, 30);
//
//   Sonuç:
//       head → 10 → 20 → 30 → nullptr

#include <iostream>

struct Node
{
    int data;
    Node *next;
    Node(int v) : data(v), next(nullptr) {}
};

void insert_at_tail(Node *&head, int value)
{
    Node *newNode = new Node(value);

    if (head == nullptr)
    {
        head = newNode;
        return;
    }

    Node *p = head;
    while (p->next != nullptr)
    {
        p = p->next;
    }

    p->next = newNode;
}

int main()
{
    Node *head = nullptr;

    insert_at_tail(head, 10); // 10
    insert_at_tail(head, 20); // 10 → 20
    insert_at_tail(head, 30); // 10 → 20 → 30

    // burada istersen print_list yazıp kontrol edebilirsin
}
