#include <cstdlib>
#include <iostream>
#include <string>

#include "../include/lista_adjacencia.hpp"
#include "../include/utils.hpp"
#include "../include/lista_encadeada.hpp"

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
    
    // Dado o número de armazéns, é possível modelar eles com um grafo bidirecional não ponderado.
    // Vou utilizar a lista de adjacência implementada na PA2 para esse fim.
    ListaAdjacencia grafo;
    int vertice;
    for (int i = 0; i < numeroArmazens; i++) {
        grafo.InsereVertice();
        for (int j = 0; j < numeroArmazens; j++) {
            std::cin >> vertice;
            if (vertice == 1) {
                grafo.InsereAresta(i, j); // o TAD implementa a "bidireção" inserindo (i, j) e (j, i)
            }
        }
    }

    // Lê a quantidade de pacotes
    int numeroPacotes;
    std::cin >> numeroPacotes;

    // Inicialização dos pacotes
    int tempoChegada;
    int idPacote;
    int origemPacote;
    int destinoPacote;
    std::string temp; // Utilizada para descartar descrições da entrada: "pac", "org", "dst".
    ListaEncadeada<int>* rota;
    for (int i = 0; i < numeroPacotes; i++) {
        std::cin >> tempoChegada >>
                    temp         >>
                    idPacote     >>
                    temp         >>
                    origemPacote >>
                    temp         >>
                    destinoPacote;
    }

    return EXIT_SUCCESS;
}