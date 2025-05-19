#include <cmath>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <limits>
#include "../include/ordenadorUniversal.hpp"
#include "../include/utils.hpp"
#include "../include/algoritmos.hpp"

// Seleciona algoritmo com base no número de quebras e tamanho de partição
void ordenadorUniversal(int *V, int tam, int minTamParticao, int limiarQuebras, sortperf_t *s) {
    int numeroQuebras = countBreaks(V, tam);

    if (numeroQuebras > limiarQuebras) {
        insertionSort(V, 0, tam - 1, s);
    } else {
        if (tam > minTamParticao) {
            quickSort3Ins(V, 0, tam - 1, minTamParticao, s);
        } else {
            insertionSort(V, 0, tam - 1, s);
        }
    }
}

OrdenadorUniversal::OrdenadorUniversal(double limiarCusto, double a, double b, double c, int size, int seed, int *V_base)
    : limiarCusto(limiarCusto), a(a), b(b), c(c), size(size), seed(seed), V_base(V_base) {}

OrdenadorUniversal::~OrdenadorUniversal() {}

void OrdenadorUniversal::run() {
    int totalBreaks = countBreaks(V_base, size);
    std::cout << "size " << size << " seed " << seed << " breaks " << totalBreaks << "\n" << std::endl;
    
    limiarParticao = determinaLimiarParticao(V_base);

    sortperf_t s;
    quickSort3Ins(V_base, 0, size - 1, 50, &s);
    limiarQuebras = determinaLimiarQuebras(V_base);
}

int OrdenadorUniversal::determinaLimiarParticao(int *V) {
    // Inicializando variáveis que vão ser refinadas conforme as iterações
    int minMPS = 2;
    int maxMPS = size;
    int passoMPS = (int) (maxMPS - minMPS) / 5;
    int limParticao;
    int numMPS;
    float diffCusto;
    
    // Variáveis auxiliares para cada iteração
    sortperf_t s;
    int iter = 0;
    int indiceMinCusto, indiceMaxCusto;
    double custoMPS, minCusto, maxCusto;

    std::cout << std::fixed << std::setprecision(6);
    do {
        // Inicialização do bloco
        std::cout << "iter " << iter++ << std::endl;
        numMPS = 0;
        limParticao = minMPS;
        minCusto = std::numeric_limits<int>::max();
        maxCusto = std::numeric_limits<int>::min();
        indiceMinCusto = 0;
        indiceMaxCusto = 0;
        double custo[10];
        int mps[10];

        for (int t = minMPS; t <= maxMPS; t += passoMPS) {
            resetcounter(&s);
            mps[numMPS] = t;

            // Criar um vetor auxiliar para ser ordenado
            int *V_auxiliar = new int[size];
            memcpy(V_auxiliar, V, size * sizeof(int));

            // Calcular o custo de ordenação no vetor auxiliar e armazenar em sortperf_t
            ordenadorUniversal(V_auxiliar, size, t, size, &s);
            
            // Calcular estatísticas e imprimir linha
            custoMPS = cost(&s, a, b, c);
            custo[numMPS] = custoMPS;
            std::cout << "mps "    << t
                      << " cost "  << custoMPS
                      << " cmp "   << s.cmp
                      << " move "  << s.move
                      << " calls " << s.calls
                      << std::endl;

            // Armazenar o menor custo e o maior custo para ajustar diffCusto posteriormente
            if (custoMPS > maxCusto) {
                maxCusto = custoMPS;
                indiceMaxCusto = numMPS;
            }

            if (custoMPS < minCusto) {
                minCusto = custoMPS;
                indiceMinCusto = numMPS;
                limParticao = t;
            }

            delete[] V_auxiliar;
            numMPS++;
        }

        // Refinação com base nos índices
        if (indiceMinCusto == 0) {
            minMPS = mps[0];
            maxMPS = mps[2];
            diffCusto = fabs(custo[0] - custo[2]);
        } else if (indiceMinCusto == numMPS - 1) {
            minMPS = mps[numMPS - 3];
            maxMPS = mps[numMPS - 1];
            diffCusto = fabs(custo[numMPS - 3] - custo[numMPS -1]);
        } else {
            minMPS = mps[indiceMinCusto - 1];
            maxMPS = mps[indiceMinCusto + 1];
            diffCusto = fabs(custo[indiceMinCusto - 1] - custo[indiceMinCusto + 1]);
        }

        // Utiliza os novos máximos e mínimos para criar a nova faixa
        passoMPS = (int) (maxMPS - minMPS) / 5;
        if (passoMPS == 0) passoMPS++;

        std::cout << "nummps "       << numMPS 
                  << " limParticao " << limParticao
                  << " mpsdiff "     << diffCusto
                  << "\n"            << std::endl;
        
    } while (diffCusto > limiarCusto && numMPS >= 5);
    
    return limParticao;
}

int OrdenadorUniversal::determinaLimiarQuebras(int *V) {
    int minLQ = 1;
    int maxLQ = size / 2;
    int passoLQ = (int) (maxLQ - minLQ) / 5;
    int limQuebras;
    int lq;
    float diffCusto;

    int iter = 0;
    int numLQ;
    sortperf_t s;

    // Cria um valor controlado de quebras para o vetor
    srand48(seed);
    int numShuffle = rand() % size;
    shuffleVector(V_base, size, numShuffle);
    
    do {
        // Inicialização do bloco
        std::cout << "iter " << iter++ << std::endl; 
        limQuebras = minLQ;
        numLQ = 0;

        for (int t = minLQ; t <= maxLQ; t += passoLQ) {
            // Criar vetores auxiliares para chamada do QuickSort e InsertionSort
            int *Vq = new int[size];
            int *Vi = new int[size];
            memcpy(Vq, V_base, size * sizeof(int));
            memcpy(Vi, V_base, size * sizeof(int));

            resetcounter(&s);
            quickSort3Ins(Vq, );
            resetcounter(&s);
            insertionSort(Vi, );

            delete[] Vq, Vi;
            numLQ++;
        }

        // Refinação com base nos índices
        if (indiceMinCusto == 0) {
            minLQ = mps[0];
            maxLQ = mps[2];
            diffCusto = fabs(custo[0] - custo[2]);
        } else if (indiceMinCusto == numMPS - 1) {
            minMPS = mps[numMPS - 3];
            maxMPS = mps[numMPS - 1];
            diffCusto = fabs(custo[numMPS - 3] - custo[numMPS -1]);
        } else {
            minMPS = mps[indiceMinCusto - 1];
            maxMPS = mps[indiceMinCusto + 1];
            diffCusto = fabs(custo[indiceMinCusto - 1] - custo[indiceMinCusto + 1]);
        }

        // Utiliza os novos máximos e mínimos para criar a nova faixa
        passoMPS = (int) (maxMPS - minMPS) / 5;
        if (passoMPS == 0) passoMPS++;

    } while (diffCusto > limiarCusto && numlq >= 6);

    return limQuebras;
}