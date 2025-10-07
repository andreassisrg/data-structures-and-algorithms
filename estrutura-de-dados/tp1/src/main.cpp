#include <iostream>
#include <fstream>
#include "../include/utils.hpp"
#include "../include/ordenadorUniversal.hpp"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Uso: " << argv[0] << " <arquivo_entrada>\n";
        return 1;
    }

    std::ifstream inputFile(argv[1]);
    if (!inputFile) {
        std::cerr << "Erro ao abrir o arquivo: " << argv[1] << "\n";
        return 1;
    }

    int seed;
    double limiarCusto, a, b, c;
    int tam;

    inputFile >> seed >> limiarCusto >> a >> b >> c >> tam;
    
    int *V = new int[tam];
    for (int i = 0; i < tam; ++i) {
        inputFile >> V[i];
    }
    inputFile.close();

    OrdenadorUniversal ou(limiarCusto, a, b, c, tam, seed, V);
    ou.run();

    delete[] V;
    return 0;
}