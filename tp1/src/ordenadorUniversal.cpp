#include <cmath>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <limits>
#include "../include/ordenadorUniversal.hpp"
#include "../include/utils.hpp"
#include "../include/algoritmos.hpp"

// Seleciona algoritmo com base no número de quebras e tamanho de partição
void ordenadorUniversal(int *V, int tam, int minTamParticao, int limiarQuebras, sortperf_t *s)
{
    int quebras = countBreaks(V, tam);

    if (quebras < limiarQuebras)
    {
        insertionSort(V, 0, tam - 1, s);
    }
    else
    {
        if (tam > minTamParticao)
        {
            quickSort3(V, 0, tam - 1, s);
        }
        else
        {
            insertionSort(V, 0, tam - 1, s);
        }
    }
}

OrdenadorUniversal::OrdenadorUniversal(double limiarCusto, double a, double b, double c, int size, int seed, int *V_base)
    : limiarCusto(limiarCusto), a(a), b(b), c(c), size(size), seed(seed), V_base(V_base) {}

OrdenadorUniversal::~OrdenadorUniversal() {}

void OrdenadorUniversal::run()
{
    int totalBreaks = countBreaks(V_base, size);
    std::cout << "size " << size << " seed " << seed << " breaks " << totalBreaks << "\n";

    limiarParticao = determinaLimiarParticao(V_base);
    std::cout << "\n";
    limiarQuebras = determinaLimiarQuebras(V_base);
}

int OrdenadorUniversal::determinaLimiarParticao(int *V)
{
    int minMPS = 2;
    int maxMPS = size;
    int passoMPS = (maxMPS - minMPS) / 5;
    double diffCusto = std::numeric_limits<double>::max();
    int iter = 0;
    int numMPS;
    int limParticao = minMPS;

    do
    {
        std::cout << '\n';
        std::cout << "iter " << iter++ << "\n";
        numMPS = 0;
        double custos[10];
        int mps_values[10];

        for (int t = minMPS; t <= maxMPS && numMPS < 6; t += passoMPS)
        {
            int *W = new int[size];
            memcpy(W, V, size * sizeof(int));
            sortperf_t s;
            resetcounter(&s);

            // Executar ordenação com o tamanho de partição específico
            ordenadorUniversal(W, size, t, size, &s);

            custos[numMPS] = cost(&s, a, b, c);
            mps_values[numMPS] = t;

            std::cout << "mps " << t
                      << " cost " << std::fixed << std::setprecision(9) << custos[numMPS]
                      << " cmp " << s.cmp
                      << " move " << s.move
                      << " calls " << s.calls << "\n";

            delete[] W;
            numMPS++;
        }

        // Encontrar o valor com menor custo
        int idxMin = 0;
        for (int i = 1; i < numMPS; i++)
        {
            if (custos[i] < custos[idxMin])
            {
                idxMin = i;
            }
        }

        limParticao = mps_values[idxMin];

        // Calcular nova faixa
        int oldMinMPS = minMPS;
        int oldMaxMPS = maxMPS;
        int oldPassoMPS = passoMPS;

        // Ajustar a faixa com base no índice do menor custo
        if (idxMin == 0)
        {
            minMPS = oldMinMPS;
            maxMPS = oldMinMPS + 2 * oldPassoMPS;
        }
        else if (idxMin == numMPS - 1)
        {
            minMPS = oldMaxMPS - 2 * oldPassoMPS;
            maxMPS = oldMaxMPS;
        }
        else
        {
            minMPS = mps_values[idxMin - 1];
            maxMPS = mps_values[idxMin + 1];
        }

        passoMPS = (maxMPS - minMPS) / 5;
        if (passoMPS == 0)
            passoMPS = 1;

        diffCusto = fabs(custos[0] - custos[numMPS - 1]);

        std::cout << "nummps " << numMPS
                  << " limParticao " << limParticao
                  << " mpsdiff " << std::fixed << std::setprecision(6) << diffCusto;

    } while (diffCusto > limiarCusto && numMPS >= 5);

    return limParticao;
}

int OrdenadorUniversal::determinaLimiarQuebras(int *V)
{
    int minLQ = 1;
    int maxLQ = size / 2;
    int passoLQ = (maxLQ - minLQ) / 5;
    if (passoLQ == 0)
        passoLQ = 1;

    double diffCusto = std::numeric_limits<double>::max();
    int iter = 0;
    int numLQ;
    int limQuebras = minLQ;

    do
    {
        std::cout << '\n';
        std::cout << "iter " << iter++ << "\n";
        numLQ = 0;
        double custosQS[10], custosIN[10];
        int lq_values[10];

        for (int lq = minLQ; lq <= maxLQ && numLQ < 6; lq += passoLQ)
        {
            // Criar vetor ordenado
            int *W = new int[size];
            for (int i = 0; i < size; i++)
            {
                W[i] = i; // Vetor ordenado
            }

            // Embaralhar com número controlado de quebras
            srand48(seed);
            shuffleVector(W, size, lq);

            // QuickSort
            int *Wq = new int[size];
            memcpy(Wq, W, size * sizeof(int));
            sortperf_t sq;
            resetcounter(&sq);
            quickSort3(Wq, 0, size - 1, &sq);
            double cQ = cost(&sq, a, b, c);

            std::cout << "qs lq " << lq
                      << " cost " << std::fixed << std::setprecision(9) << cQ
                      << " cmp " << sq.cmp
                      << " move " << sq.move
                      << " calls " << sq.calls << "\n";

            // InsertionSort
            int *Wi = new int[size];
            memcpy(Wi, W, size * sizeof(int));
            sortperf_t si;
            resetcounter(&si);
            insertionSort(Wi, 0, size - 1, &si);
            double cI = cost(&si, a, b, c);

            std::cout << "in lq " << lq
                      << " cost " << std::fixed << std::setprecision(9) << cI
                      << " cmp " << si.cmp
                      << " move " << si.move
                      << " calls " << si.calls << "\n";

            custosQS[numLQ] = cQ;
            custosIN[numLQ] = cI;
            lq_values[numLQ] = lq;

            delete[] Wq;
            delete[] Wi;
            delete[] W;
            numLQ++;
        }

        // Encontrar o maior valor onde insertion é melhor que quicksort
        int idxMin = 0;
        for (int i = 0; i < numLQ; i++)
        {
            if (custosIN[i] < custosQS[i])
            {
                idxMin = i;
            }
        }

        limQuebras = lq_values[idxMin];

        // Calcular nova faixa
        int oldMinLQ = minLQ;
        int oldMaxLQ = maxLQ;
        int oldPassoLQ = passoLQ;

        // Ajustar a faixa com base no índice do menor custo
        if (idxMin == 0)
        {
            minLQ = oldMinLQ;
            maxLQ = oldMinLQ + 2 * oldPassoLQ;
        }
        else if (idxMin == numLQ - 1)
        {
            minLQ = oldMaxLQ - 2 * oldPassoLQ;
            maxLQ = oldMaxLQ;
        }
        else
        {
            minLQ = lq_values[idxMin - 1];
            maxLQ = lq_values[idxMin + 1];
        }

        passoLQ = (maxLQ - minLQ) / 5;
        if (passoLQ == 0)
            passoLQ = 1;

        diffCusto = fabs(custosIN[0] - custosIN[numLQ - 1]);

        std::cout << "numlq " << numLQ
                  << " limQuebras " << limQuebras
                  << " lqdiff " << std::fixed << std::setprecision(6) << diffCusto
                  << "\n";

        if (numLQ <= 3)
        {
            break; // Sair do loop se tivermos menos de 3 pontos
        }

    } while (diffCusto > limiarCusto);

    return limQuebras;
}

void OrdenadorUniversal::calculaNovaFaixa(int idxMin, int &minVal, int &maxVal, int &step)
{
    int newMin, newMax;

    if (idxMin == 0)
    {
        newMin = 0;
        newMax = 2;
    }
    else if (idxMin == 5)
    { // Último índice (considerando 6 pontos)
        newMin = 3;
        newMax = 5;
    }
    else
    {
        newMin = idxMin - 1;
        newMax = idxMin + 1;
    }

    int oldMin = minVal;
    int oldStep = step;

    minVal = oldMin + newMin * oldStep;
    maxVal = oldMin + newMax * oldStep;
    step = (maxVal - minVal) / 5;
    if (step == 0)
        step = 1;
}