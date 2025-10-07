#ifndef FILA_HPP
#define FILA_HPP

class Fila {
    private:
        int* dados;
        int capacidade;
        int inicio;
        int fim;
        int tamanho;

    public:
        Fila(int cap);
        ~Fila();

        bool Vazia();

        void Enfileira(int valor);
        int Desenfileira();
};

#endif