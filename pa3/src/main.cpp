#include <iostream>
#include "../include/heap.hpp"

int main() {
    int n;
    std::cin >> n;

    Heap h = Heap(n);

    int temp;
    for (int i = 0; i < n; i++) {
        std::cin >> temp;
        h.Inserir(temp);
    }

    for (int i = 0; i < n; i++) {
        temp = h.Remover();
        std::cout << temp << " ";
    }

    std::cout << std::endl;
    return 0;
}