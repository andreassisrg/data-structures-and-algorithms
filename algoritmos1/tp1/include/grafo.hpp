#pragma once

#include <iostream>
#include <vector>

class Grafo {
    public:
        Grafo(int n, int m);
        ~Grafo();
        
        void LerStdIn();
        int MenorDistanciaEntre1eN();

    private:
        // _n corresponde ao número de vértices e _m ao número de arestas
        int _n, _m;

        // Lista de adjacência será utilizada para caminhamento no grafo
        std::vector<std::vector<int>> _listaDeAdjacencia;

        // Matriz de adjacência será utilizada para consulta do custo de cada caminho
        int **_matrizDeAdjacencia;
};