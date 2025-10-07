#pragma once

#include <iostream>
#include <vector>
#include <set>
#include <tuple>

class Grafo {
    public:
        Grafo(int n, int m);
        ~Grafo();
        
        void LerStdIn();
        int MenorCaminhoEntre1eN();
        std::set<int> RuasEmCaminhoMinimo();
        std::set<int> RuasCriticas();
        
    private:
        // _n corresponde ao número de vértices e _m ao número de arestas
        int _n, _m;

        // Lista de adjacência será utilizada para caminhamento no grafo
        std::vector<std::vector<std::pair<int, int>>> _listaDeAdjacencia;
        
        // Armazenar as arestas originais
        struct Aresta {
            int u, v, peso, indice;
        };
        std::vector<Aresta> _arestas;

        // Funcionalidades para armazenar o caminhamento do grafo
        void Dijkstra(
            int origem,
            std::vector<int>& distancias,
            std::vector<std::vector<int>>& predecessores
        );
        void EncontrarCaminhosMinimos(
            std::vector<std::vector<int>>& predecessores,
            int destino,
            int atual,
            std::vector<int>& caminho,
            std::set<int>& arestasEmCaminhoMinimo
        );
};