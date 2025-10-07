#include "../include/fila.hpp"

Fila::Fila(int cap) {
    capacidade = cap;
    dados = new int[capacidade];
    inicio = 0;
    fim = 0;
    tamanho = 0;
}

Fila::~Fila() {
    delete[] dados;
}

bool Fila::Vazia() {
    return tamanho == 0;
}

void Fila::Enfileira(int valor) {
    if (tamanho == capacidade) return; // ignorar se cheia
    dados[fim] = valor;
    fim = (fim + 1) % capacidade;
    tamanho++;
}

int Fila::Desenfileira() {
    if (Vazia()) return -1;
    int valor = dados[inicio];
    inicio = (inicio + 1) % capacidade;
    tamanho--;
    return valor;
}