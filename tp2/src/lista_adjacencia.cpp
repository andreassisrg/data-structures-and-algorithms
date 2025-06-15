#include "../include/lista_adjacencia.hpp"
#include <iostream>

ListaAdjacencia::ListaAdjacencia() {
    tamanho = 0;
    listaVertices = new ListaEncadeada<Vertice>();
}


void ListaAdjacencia::InsereVertice() {
    Vertice v;
    listaVertices->InsereFinal(v);
    tamanho++;
}


Vertice* ListaAdjacencia::getVertice(int indice) {
    if (indice < 0 || indice >= tamanho) return nullptr;
    return &((*listaVertices)[indice]);
}


void ListaAdjacencia::InsereAresta(int v, int w) {
    Vertice* V = getVertice(v);
    Vertice* W = getVertice(w);
    if (!V || !W) return;
    V->vizinhos.InsereFinal(w);
    W->vizinhos.InsereFinal(v);
}


int ListaAdjacencia::QuantidadeVertices() {
    return tamanho;
}


int ListaAdjacencia::QuantidadeArestas() {
    int soma = 0;
    for (int i = 0; i < tamanho; ++i) {
        Vertice* V = getVertice(i);
        soma += V->vizinhos.Tamanho();
    }
    return soma / 2;
}


int ListaAdjacencia::GrauMinimo() {
    if (tamanho == 0) return 0;
    int minG = getVertice(0)->vizinhos.Tamanho();
    for (int i = 1; i < tamanho; ++i) {
        int g = getVertice(i)->vizinhos.Tamanho();
        if (g < minG) minG = g;
    }
    return minG;
}


int ListaAdjacencia::GrauMaximo() {
    int maxG = 0;
    for (int i = 0; i < tamanho; ++i) {
        int g = getVertice(i)->vizinhos.Tamanho();
        if (g > maxG) maxG = g;
    }
    return maxG;
}


void ListaAdjacencia::ImprimeVizinhos(int v) {
    Vertice* V = getVertice(v);
    if (!V) {
        std::cout << "Vértice inválido\n";
        return;
    }
    Nodo<int>* aux = V->vizinhos.GetCabeca();
    while (aux) {
        std::cout << aux->valor << " ";
        aux = aux->proximo;
    }
    std::cout << "\n";
}


ListaAdjacencia::~ListaAdjacencia() {
    delete listaVertices;
}

bool ListaAdjacencia::TemAresta(int v, int w) {
    Vertice* V = getVertice(v);
    if (!V) return false;

    Nodo<int>* atual = V->vizinhos.GetCabeca();
    while (atual) {
        if (atual->valor == w) return true;
        atual = atual->proximo;
    }

    return false;
}
