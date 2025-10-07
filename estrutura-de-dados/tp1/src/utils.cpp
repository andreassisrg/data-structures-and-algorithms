#include <cstdlib>
#include <cmath>
#include "../include/utils.hpp"

int countBreaks(int *V, int size) {
    int breaks = 0;
    for (int i = 1; i < size; ++i) {
        if (V[i] < V[i - 1]) {
            breaks++;
        }
    }
    return breaks;
}

void shuffleVector(int *V, int size, int numShuffle) {
    int p1 = 0, p2 = 0, temp;
    for (int t = 0; t < numShuffle; t++) {
        /* Gera dois índices distintos no intervalo [0..size-1] */
        while (p1 == p2) {
            p1 = (int)(drand48() * size);
            p2 = (int)(drand48() * size);
        }
        /* Realiza a troca para introduzir uma quebra */
        temp = V[p1];
        V[p1] = V[p2];
        V[p2] = temp;
        p1 = p2 = 0;
    }
}

double cost(const sortperf_t *s, double a, double b, double c) {
    return a * s->cmp + b * s->move + c * s->calls;
}