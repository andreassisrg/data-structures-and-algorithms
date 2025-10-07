#include <iostream> 
#include <algorithm>
#include "../include/unionFind.hpp"

int main() {
    int n, m; std::cin >> n >> m;
    
    int u, v, c;
    Aresta* arestas = new Aresta[m];
    for (int i = 0; i < m; i++) {
        std::cin >> u >> v >> c;
        arestas[i].u = u;
        arestas[i].v = v;
        arestas[i].custo = c;
    }

    std::sort(arestas, arestas + m, [](const Aresta &a, const Aresta &b) {
        return a.custo < b.custo;
    });

    UnionFind dsu(n);
    int total = 0;
    for (int j = 0; j < m; j++) {
        int u = arestas[j].u;
        int v = arestas[j].v;

        if (dsu.Find(u) != dsu.Find(v)) {
            dsu.Union(u, v);
            total += arestas[j].custo;
        }
    }

    std::cout << total << std::endl;

    delete arestas;
    return 0;
}