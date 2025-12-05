#include <iostream>
#include <cstddef> // std::size_t

// Statik dizi ile basit fonksiyon: toplam alma
int sum_array(const int *arr, std::size_t n)
{
    int sum = 0;
    for (std::size_t i = 0; i < n; ++i)
    {
        sum += arr[i]; // index ile erişim
    }
    return sum;
}

// Statik dizi ile ters çevirme
void reverse_array(int *arr, std::size_t n)
{
    std::size_t left = 0;
    std::size_t right = (n == 0) ? 0 : n - 1;

    while (left < right)
    {
        int tmp = arr[left];
        arr[left] = arr[right];
        arr[right] = tmp;

        ++left;
        --right;
    }
}

// Çok basit bir dinamik dizi: push_back + [] + size
template <typename T>
class DynamicArray
{
public:
    DynamicArray()
        : data_(nullptr), size_(0), capacity_(0)
    {
    }

    ~DynamicArray()
    {
        delete[] data_; // heap'teki diziyi serbest bırak
    }

    void push_back(const T &value)
    {
        if (size_ == capacity_)
        {
            // Yer yoksa kapasiteyi büyüt
            std::size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
            reserve(new_capacity);
        }
        data_[size_] = value;
        ++size_;
    }

    T &operator[](std::size_t index)
    {
        // Basit olsun diye bounds kontrolü yok
        return data_[index];
    }

    std::size_t size() const
    {
        return size_;
    }

private:
    void reserve(std::size_t new_capacity)
    {
        if (new_capacity <= capacity_)
        {
            return;
        }

        // Yeni daha büyük bir dizi al
        T *new_data = new T[new_capacity];

        // Eski elemanları kopyala
        for (std::size_t i = 0; i < size_; ++i)
        {
            new_data[i] = data_[i];
        }

        // Eski diziyi sil
        delete[] data_;

        // Pointer ve kapasiteyi güncelle
        data_ = new_data;
        capacity_ = new_capacity;
    }

private:
    T *data_;              // heap'te tutulan dizi
    std::size_t size_;     // kaç eleman var
    std::size_t capacity_; // bellekte ayrılmış yer
};

int main()
{
    std::cout << "== Statik dizi ==\n";

    int arr[5] = {1, 2, 3, 4, 5};
    std::size_t n = 5;

    std::cout << "arr[2] = " << arr[2] << '\n';

    int toplam = sum_array(arr, n);
    std::cout << "Toplam = " << toplam << '\n';

    reverse_array(arr, n);
    std::cout << "Ters cevrilmis dizi: ";
    for (std::size_t i = 0; i < n; ++i)
    {
        std::cout << arr[i] << ' ';
    }
    std::cout << "\n\n";

    std::cout << "== Dinamik dizi ==\n";

    DynamicArray<int> dyn; // heap üstünde büyüyebilen dizi
    dyn.push_back(10);
    dyn.push_back(20);
    dyn.push_back(30);

    std::cout << "Elemanlar: ";
    for (std::size_t i = 0; i < dyn.size(); ++i)
    {
        std::cout << dyn[i] << ' '; // operator[] ile erişim
    }
    std::cout << '\n';

    return 0;
}
