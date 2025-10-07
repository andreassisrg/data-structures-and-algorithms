#ifndef UTILS_H
#define UTILS_H

#include "algoritmos.hpp"

// Conta o número de quebras (inversões adjacentes) no vetor V[0..size-1]
int countBreaks(int *V, int size);

// Embaralha o vetor V trocando pares de posições numShuffle vezes
void shuffleVector(int *V, int size, int numShuffle);

// Calcula o custo da ordenação: acmp + bmove + c*calls
double cost(const sortperf_t *s, double a, double b, double c);

#endif