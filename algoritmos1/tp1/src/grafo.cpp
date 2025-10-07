#include "../include/grafo.hpp"

#include <queue>
#include <iostream>

Grafo::Grafo(int n, int m) {
    // Inicializa número de vértices e arestas do grafo
    this->_n = n;
    this->_m = m;

    // Inicializa lista de adjacência
    this->_listaDeAdjacencia.resize(this->_n);

    // Aloca memória para matriz de adjacência
    this->_matrizDeAdjacencia = new int*[this->_n];
    for (int i = 0; i < this->_n; i++) {
        this->_matrizDeAdjacencia[i] = new int[this->_n];
        for (int j = 0; j < this->_n; j++) {
            this->_matrizDeAdjacencia[i][j] = 0;
        }
    }
}

void Grafo::LerStdIn() {
    int u, v, c;
    for (int i = 0; i < this->_m; i++) {
        std::cin >> u >> v >> c;
        this->_listaDeAdjacencia.at(u).push_back(v);
        this->_listaDeAdjacencia.at(v).push_back(u);
        this->_matrizDeAdjacencia[u][v] = c;
    }
}

int Grafo::MenorDistanciaEntre1eN() {
    
}

Grafo::~Grafo() {
    // Desaloca memória da matriz de adjacência
    for (int i = 0; i < this->_n; i++) {
        delete[] this->_matrizDeAdjacencia[i];
    }
    delete[] this->_matrizDeAdjacencia;
}