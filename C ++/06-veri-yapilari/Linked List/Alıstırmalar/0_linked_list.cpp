// 🔹 SORU 1 – Insert at Head
//
// Aşağıdaki node yapısını kullanarak, linked list’in BAŞINA eleman ekleyen
// fonksiyonu yaz.
//
// struct Node {
//     int data;
//     Node* next;
//     Node(int v) : data(v), next(nullptr) {}
// };
//
// Görev:
//     - Yeni bir node oluştur
//     - newNode->next = head yap
//     - head = newNode yap
//
// Fonksiyon imzası:
//
//     void insert_at_head(Node*& head, int value);
//
// Kurallar:
//   1) head başlangıçta nullptr olabilir (boş liste)
//   2) Bellek sızıntısı olmasın (new kullanıyoruz, delete yok bu soruda)
//   3) Sadece pointer işlemleri yapılacak, başka bir şey yok
//
// Örnek:
//
//   Başlangıç: head → nullptr
//   insert_at_head(head, 30);
//   insert_at_head(head, 20);
//   insert_at_head(head, 10);
//
// Sonuç liste:
//   head → 10 → 20 → 30 → nullptr

#include <iostream>

// 1) Önce Node tanımı
struct Node
{
    int data;
    Node *next;

    Node(int v)
        : data(v), next(nullptr) {}
};

// 2) Sonra insert_at_head fonksiyonu
void insert_at_head(Node *&head, int value)
{
    Node *newNode = new Node(value); // yeni node oluştur
    newNode->next = head;            // yeni node’un next'ini eski heade bağla
    head = newNode;                  // head artık yeni node'u göstersin
}

// 3) Listeyi ekrana yazdırmak için yardımcı fonksiyon
void print_list(Node *head)
{
    while (head != nullptr)
    {
        std::cout << head->data << " ";
        head = head->next;
    }
    std::cout << "\n";
}

// 4) Test için main
int main()
{
    Node *head = nullptr; // başlangıçta boş liste

    insert_at_head(head, 30);
    insert_at_head(head, 20);
    insert_at_head(head, 10);

    print_list(head); // Beklenen çıktı: 10 20 30

    return 0;
}
