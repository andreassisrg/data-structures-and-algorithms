#pragma once

#include <iostream>
#include <vector>
#include <set>
#include <tuple>

class Grafo {
    public:
        Grafo(long long int n, long long int m);
        ~Grafo();
        
        void LerStdIn();
        long long int MenorCaminhoEntre1eN();
        std::set<long long int> RuasEmCaminhoMinimo();
        std::set<long long int> RuasCriticas();
        
    private:
        // _n corresponde ao número de vértices e _m ao número de arestas
        long long int _n, _m;

        // Lista de adjacência será utilizada para caminhamento no grafo
        std::vector<std::vector<std::pair<long long int, long long int>>> _listaDeAdjacencia;
        
        // Armazenar as arestas originais
        struct Aresta {
            long long int u, v, peso, indice;
        };
        std::vector<Aresta> _arestas;

        // Funcionalidades para armazenar o caminhamento do grafo
        void Dijkstra(
            long long int origem,
            std::vector<long long int>& distancias,
            std::vector<std::vector<long long int>>& predecessores
        );
        void EncontrarCaminhosMinimos(
            std::vector<std::vector<long long int>>& predecessores,
            long long int destino,
            long long int atual,
            std::vector<long long int>& caminho,
            std::set<long long int>& arestasEmCaminhoMinimo
        );
};