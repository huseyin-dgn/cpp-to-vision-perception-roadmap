#include <iostream>
#include <memory>

int main()
{
    int stackVal = 10;          // STACK
    int *heapVal = new int(20); // HEAP

    std::unique_ptr<int> smart = std::make_unique<int>(30); // HEAP ama auto-delete

    std::cout << "stack: " << stackVal << "\n";
    std::cout << "heap: " << *heapVal << "\n";
    std::cout << "smart: " << *smart << "\n";

    delete heapVal; // HEAP temizliği
    heapVal = nullptr;

    return 0;
}
