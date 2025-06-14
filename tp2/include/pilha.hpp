#ifndef PILHA_HPP
#define PILHA_HPP

template <typename T>
struct NodoPilha {
    T valor;
    NodoPilha* proximo;

    NodoPilha(T v) : valor(v), proximo(nullptr) {}
};

template <typename T>
class Pilha {
private:
    NodoPilha<T>* topo;
    int tamanho;

public:
    Pilha();
    ~Pilha();

    void Empilha(T valor);
    T Desempilha();
    T Topo();
    bool Vazia();
    int Tamanho();
};

#include "../src/pilha.tpp"
#endif