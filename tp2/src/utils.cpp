#include "../include/utils.hpp"
#include "../include/fila.hpp"

ListaEncadeada<int>* BFS(ListaAdjacencia* grafo, int origem, int destino) {
    int n = grafo->QuantidadeVertices();
    int* visitado = new int[n];        // bool simulada por int
    int* pai = new int[n];             // para reconstrução do caminho

    for (int i = 0; i < n; ++i) {
        visitado[i] = 0;
        pai[i] = -1;
    }

    Fila fila(n); // fila com capacidade máxima = número de vértices
    fila.Enfileira(origem);
    visitado[origem] = 1;

    while (!fila.Vazia()) {
        int atual = fila.Desenfileira();
        Vertice* V = grafo->getVertice(atual);
        Nodo<int>* viz = V->vizinhos.GetCabeca();

        while (viz != nullptr) {
            int v = viz->valor;
            if (!visitado[v]) {
                visitado[v] = 1;
                pai[v] = atual;
                fila.Enfileira(v);

                if (v == destino) break; // parada precoce
            }
            viz = viz->proximo;
        }
    }

    // Reconstruir caminho
    ListaEncadeada<int>* caminho = nullptr;
    if (visitado[destino]) {
        caminho = new ListaEncadeada<int>();
        int atual = destino;
        while (atual != -1) {
            caminho->InsereComeco(atual);
            atual = pai[atual];
        }
    }

    delete[] visitado;
    delete[] pai;

    return caminho; // pode ser nullptr se não houver caminho
}

Evento novoEventoChegada(double hora, int id_pacote) {
    Evento e;
    e.hora = hora;
    e.tipo = CHEGADA;
    e.de = -1;
    e.para = -1;
    e.pacote_id = id_pacote;
    return e;
}

Evento novoEventoTransporte(double hora, int armazem_de, int armazem_para, int id_pacote) {
    Evento e;
    e.hora = hora;
    e.tipo = TRANSPORTE;
    e.de = armazem_de;
    e.para = armazem_para;
    e.pacote_id = id_pacote;
    return e;
}