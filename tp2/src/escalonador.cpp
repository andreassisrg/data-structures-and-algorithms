#include <cstdio>
#include <cstdlib>

#include "../include/escalonador.hpp"

MinHeapEvento::MinHeapEvento(int capInicial) : tamanho(0), capacidade(capInicial) {
    heap = new Evento[capacidade];
}

MinHeapEvento::~MinHeapEvento() {
    delete[] heap;
}

void MinHeapEvento::insere(const Evento &ev) {
    // Redimensiona automaticamente se estiver cheio
    if (tamanho == capacidade) {
        redimensiona(capacidade * 2);
    }

    heap[tamanho] = ev;            // coloca no final
    siftUp(tamanho);              // corrige posição para manter propriedade
    ++tamanho;
}

Evento MinHeapEvento::retiraProximo() {
    Evento out = heap[0];
    heap[0] = heap[tamanho - 1];
    tamanho--;

    if (tamanho > 0) {
        siftDown(0);
    }
    
    return out;
}

bool MinHeapEvento::vazio() const {
    return tamanho == 0;
}

bool MinHeapEvento::ehAnterior(const Evento &a, const Evento &b) {
    if (a.hora != b.hora)            return a.hora < b.hora;
    if (a.tipo != b.tipo)            return a.tipo < b.tipo;
    if (a.de   != b.de)              return a.de < b.de;
    if (a.para != b.para)            return a.para < b.para;
    
    return a.pacote_id < b.pacote_id;
}

// Ajusta para cima desde o índice idx
void MinHeapEvento::siftUp(int idx) {
    while (idx > 0) {
        int pai = (idx - 1) / 2;
        if (ehAnterior(heap[idx], heap[pai])) {
            swap(heap[idx], heap[pai]);
            idx = pai;
        } else break;
    }
}

// Ajusta para baixo desde o índice idx
void MinHeapEvento::siftDown(int idx) {
    int n = tamanho;
    while (true) {
        int esq = 2 * idx + 1;
        int dir = 2 * idx + 2;
        int menor = idx;
        if (esq < n && ehAnterior(heap[esq], heap[menor])) {
            menor = esq;
        }
        if (dir < n && ehAnterior(heap[dir], heap[menor])) {
            menor = dir;
        }
        if (menor != idx) {
            swap(heap[idx], heap[menor]);
            idx = menor;
        } else break;
    }
}

// Redimensiona o array para nova capacidade
void MinHeapEvento::redimensiona(int novaCap) {
    Evento *novo = new Evento[novaCap];
    for (int i = 0; i < tamanho; ++i) {
        novo[i] = heap[i];
    }
    delete[] heap;
    heap = novo;
    capacidade = novaCap;
}

// Troca dois eventos de posição
void MinHeapEvento::swap(Evento &a, Evento &b) {
    Evento temp = a;
    a = b;
    b = temp;
}

void MinHeapEvento::removeEventosDoPacote(int pacote_id) {
    int i = 0;
    // Varre o heap inteiro, removendo entradas cujo heap[i].pacote_id == pacote_id
    while (i < tamanho) {
        if (heap[i].pacote_id == pacote_id) {
            // Substitui pelo último elemento
            heap[i] = heap[tamanho - 1];
            --tamanho;
            // Restaura propriedade de heap em i (se ainda houver elementos nessa posição)
            if (i < tamanho) {
                siftDown(i);
                siftUp(i);
            }
            // Não incrementa i, pois o novo heap[i] precisa ser rechecado
        } else {
            ++i;
        }
    }
}