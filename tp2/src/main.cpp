#include <cstdlib>
#include <iostream>
#include <string>

#include "../include/utils.hpp"
#include "../include/lista_encadeada.hpp"
#include "../include/pacote.hpp"
#include "../include/armazem.hpp"

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
    // Também é feita a inicialização dos armazéns.
    Armazem armazens[numeroArmazens];
    ListaAdjacencia grafo;
    int vertice;
    for (int i = 0; i < numeroArmazens; i++) {
        grafo.InsereVertice();
        armazens[i].Inicializar(numeroArmazens);
        for (int j = 0; j < numeroArmazens; j++) {
            std::cin >> vertice;
            if (vertice == 1) {
                grafo.InsereAresta(i, j); // o TAD implementa a "bidireção" inserindo (i, j) e (j, i)
            }
        }
    }

    // Lê a quantidade de pacotes.
    int numeroPacotes;
    std::cin >> numeroPacotes;

    // Inicialização dos pacotes.
    // Inicialização do escalonador com eventos de armazenamento.
    int tempoChegada, id;
    std::string temp; // Utilizada para descartar descrições da entrada: "pac", "org", "dst".
    Pacote* pacotes = new Pacote[numeroPacotes];
    MinHeapEvento escalonador(numeroPacotes * 2); // Capacidade inicial arbitrária
    for (int i = 0; i < numeroPacotes; i++) {
        std::cin >> tempoChegada         >>
                    temp                 >>
                    id                   >>
                    temp                 >>
                    pacotes[id].origem    >>
                    temp                 >>
                    pacotes[id].destino;

        // É importante armazenar o pacote na posição de seu ID para facilitar obtê-lo novamente.
        pacotes[id].id = id;
        pacotes[id].estado_atual = NAO_POSTADO;
        pacotes[id].caminho = BFS(&grafo, pacotes[i].origem, pacotes[i].destino);
    
        escalonador.insere(novoEventoChegada(tempoChegada, pacotes[i].id));
    }

    Pacote pacote;
    while(!escalonador.vazio()) {
        Evento eventoAtual = escalonador.retiraProximo();

        if (eventoAtual.tipo == CHEGADA) {
            pacote = pacotes[eventoAtual.pacote_id];

            // Lidando com possível caso degenerado de origem igual ao destino
            if (pacote.origem == pacote.destino) {
                std::cout << eventoAtual.hora                            <<
                             " pacote "                                  << 
                             pacote.id                                   <<
                             " entregue em "                             <<
                             pacote.origem                               <<
                             " na secao "                                <<
                             pacote.caminho->GetCabeca()->proximo->valor <<
                             std::endl;
            }

            // TO-DO: estou apenas imprimindo, tenho que armazenar no armazém!
            std::cout << eventoAtual.hora                            <<
                         " pacote "                                  << 
                         pacote.id                                   <<
                         " armazenado em "                           <<
                         pacote.origem                               <<
                         " na secao "                                <<
                         pacote.caminho->GetCabeca()->proximo->valor <<
                         std::endl;
        }
    };

    delete[] pacotes;
    return EXIT_SUCCESS;
}