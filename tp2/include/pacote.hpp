#ifndef PACOTE_HPP
#define PACOTE_HPP

#include "./lista_encadeada.hpp"

enum EstadoPacote {
    NAO_POSTADO = 1,
    CHEGADA_ESCALONADA = 2,
    ARMAZENADO = 3,
    REMOVIDO_PARA_TRANSPORTE = 4,
    ENTREGUE = 5,
    TRANSITO = 6
};

class Pacote {
    public:
        int id;
        int estado_atual;
        int origem;
        int destino;
        ListaEncadeada<int>* caminho;
        int armazemAtual;

        Pacote();
        ~Pacote();
};

#endif