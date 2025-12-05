// 🔹 SORU 8 – Reverse (Linked List'i Ters Çevirme)
//
// Aşağıdaki node yapısını kullanarak, linked list'i YERİNDE ters çeviren
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
//     void reverse_list(Node*& head);
//
// Davranış:
//
//   - Başlangıç:
//         head → 10 → 20 → 30 → nullptr
//
//   - reverse_list(head) çağrısından sonra:
//         head → 30 → 20 → 10 → nullptr
//
// İpucu (klasik 3 pointer tekniği):
//
//   Node* prev = nullptr;
//   Node* curr = head;
//   Node* next = nullptr;
//
//   while (curr != nullptr) {
//       next = curr->next;   // 1) ilerideki node'u sakla
//       curr->next = prev;   // 2) oku terse çevir
//       prev = curr;         // 3) prev'i bir adım ileri kaydır
//       curr = next;         // 4) curr'ı ilerlet
//   }
//
//   En sonda:
//       head = prev;
//
// Kurallar:
//   - Ekstra dizi vs. kullanmak yok
//   - Sadece pointer'ları çeviriyorsun, yeni node oluşturmuyorsun
//   - Liste boşsa (head == nullptr) veya tek elemanlıysa, olduğu gibi kalır

#include <iostream>

struct Node
{
    int data;
    Node *next;
    Node(int v) : data(v), next(nullptr) {}
};

void reverse_list(Node *&head)
{
    if (head == nullptr)
    {
        return;
    }

    Node *gecici = nullptr; // prev
    Node *curr = head;
    Node *next = nullptr;

    while (curr != nullptr)
    {
        next = curr->next;   // 1) sonraki node'u kaydet
        curr->next = gecici; // 2) oku terse çevir
        gecici = curr;       // 3) prev'i (gecici) bir ileri al
        curr = next;         // 4) curr'ı ilerlet
    }

    head = gecici; // en son prev (gecici) yeni head olur
}

void print_list(Node *head)
{
    Node *p = head;
    while (p != nullptr)
    {
        std::cout << p->data << " ";
        p = p->next;
    }
    std::cout << std::endl;
}

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

    // Listeye rastgele değerler ekleyelim
    insert_at_tail(head, 10);
    insert_at_tail(head, 20);
    insert_at_tail(head, 30);
    insert_at_tail(head, 40);

    std::cout << "Orijinal liste: ";
    print_list(head);

    reverse_list(head);

    std::cout << "Ters cevrilmis liste: ";
    print_list(head);

    return 0;
}
