#ifndef ARMAZEM_HPP
#define ARMAZEM_HPP

#include "./pacote.hpp"
#include "./pilha.hpp"

class Armazem {
    public:
        // Como eu gostaria de criar um array com os armazéns, vou deixar o construtor padrão.
        Armazem();
        ~Armazem();

        // O método a seguir tem a função de substituir o construtor, mas permitindo flexibilidade
        // na hora da inicialização do array de armazéns.
        void Inicializar(int total_armazens);

        void ArmazenarPacote(Pacote* pacote);
        Pacote* RemoverPacote(int destino, int custoRemocao, int& tempoRemocao);
        bool SecaoVazia(int destino);

    private:
        Pilha<Pacote*>* secoes;
        int total_armazens;
};

#endif