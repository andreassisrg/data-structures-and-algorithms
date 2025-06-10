#ifndef LISTA_ADJACENCIA_HPP
#define LISTA_ADJACENCIA_HPP

#include "./lista_encadeada.hpp"

struct Vertice
{
    ListaEncadeada<int> vizinhos;
};

class ListaAdjacencia {
    public:
        ListaAdjacencia();
        ~ListaAdjacencia();

        void InsereVertice();
        void InsereAresta(int v, int w);

        int QuantidadeVertices();
        int QuantidadeArestas();

        int GrauMinimo();
        int GrauMaximo();

        void ImprimeVizinhos(int v);
        Vertice* getVertice(int indice);

    private:
        int tamanho;
        ListaEncadeada<Vertice>* listaVertices;
};

#endif