#include <iostream>

#include "../include/grafo.hpp"

int main() {
    int u, v;
    std::cin >> u >> v;

    Grafo grafo(u, v);
    grafo.LerStdIn();
}