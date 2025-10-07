#include "../include/lista_encadeada.hpp"

template <typename T>
ListaEncadeada<T>::ListaEncadeada() {
    tamanho = 0;
    cabeca = nullptr;
}

template <typename T>
void ListaEncadeada<T>::InsereComeco(T valor) {
    Nodo<T>* novoNodo = new Nodo<T>(valor);
    novoNodo->proximo = cabeca;
    cabeca = novoNodo;
    tamanho++;
}


template <typename T>
void ListaEncadeada<T>::InsereFinal(T valor) {
    Nodo<T>* novoNodo = new Nodo<T>(valor);
    if (!cabeca) {
        cabeca = novoNodo;
    }
    else {
        Nodo<T>* aux = cabeca;
        while (aux->proximo) {
            aux = aux->proximo;
        }
        aux->proximo = novoNodo;
    }
    tamanho++;
}


template <typename T>
void ListaEncadeada<T>::Remove(int indice) {
    if (indice >= tamanho || indice < 0) return;

    Nodo<T>* removido;

    if (indice == 0) {
        removido = cabeca;
        cabeca = cabeca->proximo;
    }
    else {
        Nodo<T>* aux = cabeca;
        for (int i = 0; i < indice - 1; i++) {
            aux = aux->proximo;
        }

        removido = aux->proximo;
        aux->proximo = removido ->proximo;
    }

    delete removido;
    tamanho--;
}


template <typename T>
int ListaEncadeada<T>::Tamanho() {
    return tamanho;
}


template <typename T>
T& ListaEncadeada<T>::operator[](int indice) {
    Nodo<T>* aux = cabeca;
    for (int i = 0; i < indice; ++i) aux = aux->proximo;
    return aux->valor;
}


template <typename T>
Nodo<T>* ListaEncadeada<T>::GetCabeca() {
    return cabeca;
}


template <typename T>
ListaEncadeada<T>::~ListaEncadeada() {
    Nodo<T>* atual = cabeca;
    while(atual) {
        Nodo<T>* proximo = atual->proximo;
        delete atual;
        atual = proximo;
    }
    tamanho = 0;
    cabeca = nullptr;
}


#include "../include/lista_encadeada.hpp"
#include "../include/lista_adjacencia.hpp"
template class ListaEncadeada<int>;
template class ListaEncadeada<Vertice>;