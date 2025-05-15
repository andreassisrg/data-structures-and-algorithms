#include <iostream>
#include <string>
#include <cstdlib>
#include "../include/graph.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Uso: " << argv[0] << " [-d | -n | -k]" << std::endl;
        return EXIT_FAILURE;
    }
    std::string opt = argv[1];
    if (opt != "-d" && opt != "-n" && opt != "-k") {
        std::cerr << "Opção inválida: " << opt << std::endl;
        return EXIT_FAILURE;
    }

    int n;
    if (!(std::cin >> n) || n < 0) {
        std::cerr << "Entrada inválida para número de vértices" << std::endl;
        return EXIT_FAILURE;
    }

    Grafo g;
    // Cria n vértices (índices de 0 a n-1)
    for (int i = 0; i < n; ++i) {
        g.InsereVertice();
    }

    // Lê vizinhanças e insere arestas
    for (int v = 0; v < n; ++v) {
        int m;
        std::cin >> m;
        for (int j = 0; j < m; ++j) {
            int w;
            std::cin >> w;
            g.InsereAresta(v, w);
        }
    }

    if (opt == "-d") {
        std::cout << g.QuantidadeVertices() << "\n";
        std::cout << g.QuantidadeArestas()  << "\n";
        std::cout << g.GrauMinimo()          << "\n";
        std::cout << g.GrauMaximo()          << "\n";
    }
    else if (opt == "-n") {
        // Imprime vizinhos de cada vértice, em ordem de entrada
        for (int v = 0; v < g.QuantidadeVertices(); ++v) {
            g.ImprimeVizinhos(v);
        }
    }
    else if (opt == "-k") {
        int nv = g.QuantidadeVertices();
        bool completo = (nv <= 1) || (g.GrauMinimo() == nv - 1);
        std::cout << (completo ? 1 : 0) << std::endl;
    }

    return EXIT_SUCCESS;
}