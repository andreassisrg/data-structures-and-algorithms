#ifndef LISTA_ENCADEADA_HPP
#define LISTA_ENCADEADA_HPP

template <typename T>
struct Nodo
{
    T valor;
    Nodo* proximo;

    Nodo(T valor) : valor(valor), proximo(nullptr) {}
};


template <typename T>
class ListaEncadeada {
    private:
        int tamanho;
        Nodo<T>* cabeca;
    
    public:
        ListaEncadeada();
        ~ListaEncadeada();

        void InsereComeco(T valor);
        void InsereFinal(T valor);
        
        void Remove(int indice);

        int Tamanho();
        T& operator[](int indice);
        int IndiceDe(T valor);
        Nodo<T>* GetCabeca();
};

#endif