#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>

#include "../include/utils.hpp"
#include "../include/lista_encadeada.hpp"
#include "../include/pacote.hpp"
#include "../include/armazem.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Uso correto: " << argv[0] << " arquivo.wkl" << std::endl;
        return EXIT_FAILURE;
    }

    std::ifstream entrada(argv[1]);
    if (!entrada) {
        std::cerr << "Erro ao abrir o arquivo: " << argv[1] << std::endl;
        return EXIT_FAILURE;
    }

    // Declaração e leitura das variáveis de configuração.
    int capacidadeTransporte;
    int latenciaTransporte;
    int intervaloTransportes;
    int custoRemocao;
    int numeroArmazens;
    entrada >> capacidadeTransporte >>
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
            entrada >> vertice;
            if (vertice == 1) {
                grafo.InsereAresta(i, j); // o TAD implementa a "bidireção" inserindo (i, j) e (j, i)
            }
        }
    }

    // Lê a quantidade de pacotes
    int numeroPacotes;
    entrada >> numeroPacotes;

    // Inicialização dos pacotes.
    // Inicialização do escalonador com eventos de armazenamento
    int tempoChegada, id;
    std::string temp; // Utilizada para descartar descrições da entrada: "pac", "org", "dst"
    Pacote* pacotes = new Pacote[numeroPacotes];
    MinHeapEvento escalonador(numeroPacotes * 2); // Capacidade inicial arbitrária
    int tempoPrimeiroPacote = -1; // O tempo começa a contar a partir da postagem de um primeiro pacote
    for (int i = 0; i < numeroPacotes; i++) {
        entrada >> tempoChegada          >>
                   temp                  >>
                   temp                  >>
                   temp                  >>
                   pacotes[i].origem     >>
                   temp                  >>
                   pacotes[i].destino;

        // É importante armazenar o pacote na posição de seu ID para facilitar obtê-lo novamente
        pacotes[i].id = i;
        pacotes[i].estado_atual = NAO_POSTADO;
        pacotes[i].caminho = BFS(&grafo, pacotes[i].origem, pacotes[i].destino);
    
        escalonador.insere(novoEventoChegada(tempoChegada, pacotes[i].id));

        if (tempoPrimeiroPacote > tempoChegada || tempoPrimeiroPacote < 0) {
            tempoPrimeiroPacote = tempoChegada;
        }
    }

    // A cada intervaloTransportes, é necessário que pacotes em armazéns comecem a ser transportados
    // É necessário guardar em que momento da simulação o pacote terá um novo transporte
    // Cada elemento do seguinte array terá o momento da iteração que o pacote poderá ter o início de um transporte
    int intervaloCaminhoes[numeroPacotes];
    for (int i = 0; i < numeroPacotes; i++) {
        intervaloCaminhoes[i] = intervaloTransportes + tempoPrimeiroPacote;
    }

    Pacote* pacote;
    int indiceArmazemAtual; // Utilizado para calcular o proximoArmazem
    int proximoArmazem; // Contém o próximo armazém na rota do pacote
    int armazemAtual;
    int secaoAtual;
    while(!escalonador.vazio()) {
        Evento eventoAtual = escalonador.retiraProximo();
        pacote = &pacotes[eventoAtual.pacote_id];

        if (eventoAtual.tipo == CHEGADA) {
            // Caso de canto: pacote é postado em seu destino
            // Necessário ter uma condicional a mais, pois eventoAtual.para ainda não existe nesse caso
            if (pacote->origem == pacote->destino) {
                pacote->armazemAtual = pacote->destino;
                pacote->estado_atual = ENTREGUE;
                imprimirEstatistica(eventoAtual.hora, pacote->id, ENTREGUE_EM, pacote->destino);
                continue;
            }

            // Pacote chegou ao destino
            if (pacote->armazemAtual == pacote->destino) {
                pacote->armazemAtual = pacote->destino;
                pacote->estado_atual = ENTREGUE;
                imprimirEstatistica(eventoAtual.hora, pacote->id, ENTREGUE_EM, pacote->destino);
                continue;
            }

            // Neste ponto, o pacote chegou em algum armazém, porém não foi seu destino.
            
            // Estou inicializando os pacotes com armazemAtual = -1
            // Logo, se o pacote foi apenas inicializado, significa que ele ainda não foi postado em nenhum armazém
            if (pacote->armazemAtual == -1) {
                pacote->armazemAtual = pacote->origem;
            }

            // Definindo o próximo armazém do pacote
            indiceArmazemAtual = pacote->caminho->IndiceDe(pacote->armazemAtual);
            proximoArmazem = pacote->caminho->operator[](indiceArmazemAtual + 1);

            // Armazenamento do pacote
            armazemAtual = pacote->armazemAtual;
            armazens[armazemAtual].ArmazenarPacote(pacote, proximoArmazem);
            pacote->estado_atual = ARMAZENADO;
            imprimirEstatistica(eventoAtual.hora, pacote->id, ARMAZENADO_EM, armazemAtual, proximoArmazem);
            
            
            escalonador.insere(novoEventoTransporte(
                intervaloCaminhoes[pacote->id],
                pacote->armazemAtual,
                proximoArmazem,
                pacote->id
            ));

            intervaloCaminhoes[pacote->id] += intervaloTransportes;

        } else {
            // Tipo do evento atual é TRANSPORTE

            // Revisitar essa condição:
            if (!armazens[eventoAtual.de].ContemPacoteNaSecao(eventoAtual.para, pacote)) {
                continue;
            }

            if (pacote->estado_atual == ARMAZENADO) {
                // Definindo o armazém e a seção que o pacote está
                armazemAtual = eventoAtual.de;
                secaoAtual = proximoArmazem = eventoAtual.para;

                // Quando chega o momento de transportar um pacote, é necessário remover todos os pacotes da seção atual
                // É necessário atualizar os estados dele, e agendar um evento para de fato transportá-los/rearmazená-los
                Armazem* armazen = &armazens[armazemAtual];
                int tempoDesempilhamento = armazen->CustoRemocaoTotal(secaoAtual, custoRemocao); // Utilizada no escalonador
                Pilha<Pacote*> removidos;
                int custoPorPacote = custoRemocao;
                while (!armazen->SecaoVazia(secaoAtual)) {
                    Pacote* pacoteRemovido = armazen->Desempilha(secaoAtual);
                    pacoteRemovido->estado_atual = REMOVIDO_PARA_TRANSPORTE;
                    escalonador.removeEventosDoPacote(pacoteRemovido->id);
                    imprimirEstatistica(eventoAtual.hora + custoPorPacote, pacoteRemovido->id, REMOVIDO_DE, armazemAtual, secaoAtual);
                    custoPorPacote += custoRemocao;
                    removidos.Empilha(pacoteRemovido);
                }

                // É necessário definir quais pacotes vão ser transportados e quais vão ser rearmazenados
                int foramTransportados = 0;
                Pacote* pacote_temp;
                while (!removidos.Vazia()) {
                    pacote_temp = removidos.Desempilha();
                    if (foramTransportados < capacidadeTransporte) {
                        escalonador.insere(novoEventoChegada(eventoAtual.hora + tempoDesempilhamento + latenciaTransporte, pacote_temp->id));
                        imprimirEstatistica(eventoAtual.hora + tempoDesempilhamento, pacote_temp->id, EM_TRANSITO, armazemAtual, proximoArmazem);
                        pacote_temp->estado_atual = CHEGADA_ESCALONADA;
                        pacote_temp->armazemAtual = proximoArmazem;
                    } else {
                        escalonador.insere(novoEventoTransporte(
                            intervaloCaminhoes[pacote_temp->id],
                            armazemAtual,
                            proximoArmazem,
                            pacote_temp->id
                        ));
                        intervaloCaminhoes[pacote_temp->id] += intervaloTransportes;
                        armazen->ArmazenarPacote(pacote_temp, secaoAtual);
                        pacote_temp->estado_atual = ARMAZENADO;
                        imprimirEstatistica(eventoAtual.hora + tempoDesempilhamento, pacote_temp->id, REARMAZENADO_EM, armazemAtual, secaoAtual);
                    }
                    foramTransportados++;
                }
            }
        }
    };

    delete[] pacotes;
    return EXIT_SUCCESS;
}