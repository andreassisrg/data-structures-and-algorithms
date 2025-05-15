#ifndef ORDENADORUNIVERSAL_HPP
#define ORDENADORUNIVERSAL_HPP

#include "algoritmos.hpp"
#include "utils.hpp"

void ordenadorUniversal(int *V, int tam, int minTamParticao, int limiarQuebras, sortperf_t *s);

class OrdenadorUniversal {
    public:
        OrdenadorUniversal(double limiarCusto, double a, double b, double c, int size, int seed, int *V_base);
        ~OrdenadorUniversal();
        void run();

    private:
        double limiarCusto, a, b, c;
        int size, seed;
        int limiarParticao;
        int limiarQuebras;
        int *V_base;

        int determinaLimiarParticao(int *V);
        int determinaLimiarQuebras(int *V);
        void calculaNovaFaixa(int idxMin, int &minVal, int &maxVal, int &step);
};

#endif