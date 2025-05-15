#include <iostream>
#include "../include/utils.hpp"
#include "../include/ordenadorUniversal.hpp"

int main() {
    int seed;
    double limiarCusto, a, b, c;
    int tam;

    std::cin >> seed >> limiarCusto >> a >> b >> c >> tam;

    // Lê vetor de entrada
    int *V = new int[tam];
    for (int i = 0; i < tam; ++i)
        std::cin >> V[i];

    // Cria e executa o calibrador
    OrdenadorUniversal ou(limiarCusto, a, b, c, tam, seed, V);
    ou.run();

    delete[] V;
    return 0;
}