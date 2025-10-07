#include "../include/grafo.hpp"

#include <queue>
#include <iostream>
#include <climits>
#include <algorithm>

Grafo::Grafo(long long int n, long long int m) {
    // Inicializa número de vértices e arestas do grafo
    this->_n = n;
    this->_m = m;

    // Inicializa lista de adjacência
    this->_listaDeAdjacencia.resize(this->_n);
}

void Grafo::LerStdIn() {
    long long int u, v, c;
    for (long long int i = 0; i < this->_m; i++) {
        std::cin >> u >> v >> c;
        u--; v--; // Ajuste de input 1-indexado
        this->_listaDeAdjacencia[u].push_back({v, c});
        this->_listaDeAdjacencia[v].push_back({u, c});
        // Armazenar a aresta original com seu índice (1-indexado para a saída)
        this->_arestas.push_back({u, v, c, i + 1});
    }
}

void Grafo::Dijkstra(long long int origem, std::vector<long long int>& distancias, std::vector<std::vector<long long int>>& predecessores) {
    // Inicializa distâncias e visitados
    distancias.assign(this->_n, INT_MAX);
    std::vector<bool> visitados(this->_n, false);
    predecessores.assign(this->_n, std::vector<long long int>());
    
    // Criação de um min heap para os custos
    std::priority_queue<
        std::pair<long long int, long long int>, 
        std::vector<std::pair<long long int, long long int>>, 
        std::greater<std::pair<long long int, long long int>>
    > minHeap;

    // Inicialização do heap com o vértice inicial
    distancias[origem] = 0;
    minHeap.push({0, origem});

    while (!minHeap.empty()) {
        // Pega o vértice com menor custo
        std::pair<long long int, long long int> v = minHeap.top();
        minHeap.pop();

        long long int distanciaV = v.first;
        long long int indiceV = v.second;

        // Verifica se ele já foi visitado
        if (visitados[indiceV]) continue;
        visitados[indiceV] = true;

        // Para cada vizinho dele, atualizamos, se necessário, o custo para chegar em outros vértices
        for (auto vizinho : _listaDeAdjacencia[indiceV]) {
            long long int u = vizinho.first;
            long long int peso = vizinho.second;
            
            if (distanciaV + peso < distancias[u]) {
                distancias[u] = distanciaV + peso;
                predecessores[u].clear();
                predecessores[u].push_back(indiceV);
                minHeap.push({distancias[u], u});
            } else if (distanciaV + peso == distancias[u]) {
                // Se encontrarmos outro caminho com a mesma distância mínima
                predecessores[u].push_back(indiceV);
            }
        }
    }
}

long long int Grafo::MenorCaminhoEntre1eN() {
    std::vector<long long int> distancias;
    std::vector<std::vector<long long int>> predecessores;
    Dijkstra(0, distancias, predecessores);
    return distancias[this->_n - 1];
}

void Grafo::EncontrarCaminhosMinimos(std::vector<std::vector<long long int>>& predecessores, long long int destino, long long int atual, std::vector<long long int>& caminho, std::set<long long int>& arestasEmCaminhoMinimo) {
    if (atual == 0) { // Chegamos à origem
        for (size_t i = 0; i < caminho.size() - 1; i++) {
            long long int u = caminho[i];
            long long int v = caminho[i + 1];
            
            // Encontrar o índice da aresta entre u e v
            for (const auto& aresta : _arestas) {
                if ((aresta.u == u && aresta.v == v) || (aresta.u == v && aresta.v == u)) {
                    arestasEmCaminhoMinimo.insert(aresta.indice);
                    break;
                }
            }
        }
        return;
    }
    
    for (long long int pred : predecessores[atual]) {
        caminho.push_back(pred);
        EncontrarCaminhosMinimos(predecessores, destino, pred, caminho, arestasEmCaminhoMinimo);
        caminho.pop_back();
    }
}

std::set<long long int> Grafo::RuasEmCaminhoMinimo() {
    std::vector<long long int> distancias;
    std::vector<std::vector<long long int>> predecessores;
    Dijkstra(0, distancias, predecessores);
    
    std::set<long long int> arestasEmCaminhoMinimo;
    std::vector<long long int> caminho = {this->_n - 1}; // Começamos do destino
    EncontrarCaminhosMinimos(predecessores, this->_n - 1, this->_n - 1, caminho, arestasEmCaminhoMinimo);
    
    return arestasEmCaminhoMinimo;
}

std::set<long long int> Grafo::RuasCriticas() {
    std::set<long long int> ruasCriticas;
    std::set<long long int> ruasEmCaminhoMinimo = RuasEmCaminhoMinimo();
    long long int distanciaOriginal = MenorCaminhoEntre1eN();
    
    // Para cada aresta em um caminho mínimo, verificamos se ela é crítica
    for (long long int indiceAresta : ruasEmCaminhoMinimo) {
        // Encontrar a aresta correspondente
        long long int u = -1, v = -1;
        for (size_t i = 0; i < _arestas.size(); i++) {
            if (_arestas[i].indice == indiceAresta) {
                u = _arestas[i].u;
                v = _arestas[i].v;
                break;
            }
        }
        
        if (u != -1 && v != -1) {
            // Remover temporariamente a aresta
            auto it_u = std::find_if(_listaDeAdjacencia[u].begin(), _listaDeAdjacencia[u].end(),
                [v](const auto& p) { return p.first == v; });
            auto it_v = std::find_if(_listaDeAdjacencia[v].begin(), _listaDeAdjacencia[v].end(),
                [u](const auto& p) { return p.first == u; });
            
            if (it_u != _listaDeAdjacencia[u].end() && it_v != _listaDeAdjacencia[v].end()) {
                long long int peso_u = it_u->second;
                long long int peso_v = it_v->second;
                
                _listaDeAdjacencia[u].erase(it_u);
                _listaDeAdjacencia[v].erase(it_v);
                
                // Calcular nova distância mínima
                std::vector<long long int> novasDistancias;
                std::vector<std::vector<long long int>> novosPredecessores;
                Dijkstra(0, novasDistancias, novosPredecessores);
                
                // Se a distância aumentou ou ficou infinita, a aresta é crítica
                if (novasDistancias[this->_n - 1] > distanciaOriginal || novasDistancias[this->_n - 1] == INT_MAX) {
                    ruasCriticas.insert(indiceAresta);
                }
                
                // Restaurar a aresta
                _listaDeAdjacencia[u].push_back({v, peso_u});
                _listaDeAdjacencia[v].push_back({u, peso_v});
            }
        }
    }
    
    return ruasCriticas;
}

Grafo::~Grafo() {}