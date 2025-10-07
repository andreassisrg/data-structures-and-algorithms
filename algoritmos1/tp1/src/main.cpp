#include <iostream>
#include <set>
#include "../include/grafo.hpp"

int main() {
    int n, m;
    std::cin >> n >> m;

    Grafo grafo(n, m);
    grafo.LerStdIn();
    
    // Parte 1: Distância mínima entre a praça e o parque
    int menorDistanciaEntre1eN = grafo.MenorCaminhoEntre1eN();
    std::cout << "Parte 1: " << menorDistanciaEntre1eN << std::endl;

    // Parte 2: Ruas que participam de pelo menos um caminho mínimo
    std::set<int> ruasEmCaminhoMinimo = grafo.RuasEmCaminhoMinimo();
    std::cout << "Parte 2:";
    for (int rua : ruasEmCaminhoMinimo) {
        std::cout << " " << rua;
    }
    std::cout << std::endl;

    // Parte 3: Ruas críticas
    std::set<int> ruasCriticas = grafo.RuasCriticas();
    std::cout << "Parte 3:";
    if (ruasCriticas.empty()) {
        std::cout << " -1";
    } else {
        for (int rua : ruasCriticas) {
            std::cout << " " << rua;
        }
    }
    std::cout << std::endl;
    
    return 0;
}