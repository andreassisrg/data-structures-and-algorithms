#include <cstdlib>
#include <iostream>

int main() {
    // Declaração e leitura das variáveis de configuração.
    int capacidadeTransporte;
    int latenciaTransporte;
    int intervaloTransportes;
    int custoRemocao;
    int numeroArmazens;
    std::cin >> capacidadeTransporte >>
                latenciaTransporte   >>
                intervaloTransportes >>
                custoRemocao         >>
                numeroArmazens;
    
    // Dado o número de armazéns, vamos criar um grafo bidirecional não ponderado para armazená-los.
    // Vou utilizar a lista de adjacência implementada na PA2 para esse fim.
    
    // TO-DO conferir se consigo fazer BFS na minha lista de adjacência
    
    int vertice;
    for (int i = 0; i < numeroArmazens; i++) {
        // TO-DO: insere vértice
        for (int j = 0; i < numeroArmazens; j++) {
            std::cin >> vertice;
            // TO-DO: if vertice == 1 insere aresta (i, j)
        }
    }

    return EXIT_SUCCESS;
}