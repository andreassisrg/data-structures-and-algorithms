#include "../include/pilha.hpp"

template <typename T>
Pilha<T>::Pilha() {
    topo = nullptr;
    tamanho = 0;
}

template <typename T>
Pilha<T>::~Pilha() {
    while (!Vazia()) {
        Desempilha();
    }
}

template <typename T>
void Pilha<T>::Empilha(T valor) {
    NodoPilha<T>* novo = new NodoPilha<T>(valor);
    novo->proximo = topo;
    topo = novo;
    tamanho++;
}

template <typename T>
T Pilha<T>::Desempilha() {
    if (Vazia()) {
        // Erro: pilha vazia. Ideal seria lançar exceção, mas vamos retornar lixo.
        return T();
    }

    NodoPilha<T>* aux = topo;
    T valor = aux->valor;
    topo = topo->proximo;
    delete aux;
    tamanho--;
    return valor;
}

template <typename T>
T Pilha<T>::Topo() {
    if (Vazia()) return T();
    return topo->valor;
}

template <typename T>
bool Pilha<T>::Vazia() {
    return topo == nullptr;
}

template <typename T>
int Pilha<T>::Tamanho() {
    return tamanho;
}
