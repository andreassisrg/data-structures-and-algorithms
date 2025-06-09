#include <cmath>
#include "../include/heap.hpp"
#include <iostream>

Heap::Heap(int maxsize) {
    tamanho = 0;
    data = new int[maxsize];
}

int Heap::GetAncestral(int posicao) {
    return floor((posicao - 1) / 2);
}

int Heap::GetSucessorEsq(int posicao) {
    return ((posicao * 2) + 1);
}

int Heap::GetSucessorDir(int posicao) {
    return ((posicao * 2) + 2);
}

bool Heap::Vazio() {
    return tamanho <= 0;
}

void Heap::Inserir(int x) {
    data[tamanho] = x;
    HeapifyPorCima(tamanho);
    tamanho++;
    return;
}

void Heap::HeapifyPorCima(int posicao) {
    int indice_ancestral = GetAncestral(posicao);
    if (indice_ancestral < 0) return;
    
    int temp;
    if (data[posicao] < data[indice_ancestral]) {
        temp = data[indice_ancestral];
        data[indice_ancestral] = data[posicao];
        data[posicao] = temp;

        HeapifyPorCima(indice_ancestral);
    }

    return;
}

int Heap::Remover() {
    if (tamanho <= 0) return 0;

    int raiz = data[0];
    data[0] = data[tamanho - 1];
    tamanho--;
    HeapifyPorBaixo(0);

    return raiz;
}

void Heap::HeapifyPorBaixo(int posicao) {
    int indice_sucessor_esq = GetSucessorEsq(posicao);
    int indice_sucessor_dir = GetSucessorDir(posicao);

    int menor = posicao;
    if (indice_sucessor_esq < tamanho && data[menor] > data[indice_sucessor_esq]) {
        menor = indice_sucessor_esq; 
    }
    
    if (indice_sucessor_dir < tamanho && data[menor] > data[indice_sucessor_dir]) {
        menor = indice_sucessor_dir;
    }

    if (menor != posicao) {
        std::swap(data[posicao], data[menor]);
        HeapifyPorBaixo(menor);
    }

    return;
}

Heap::~Heap() {
    delete[] data;
}