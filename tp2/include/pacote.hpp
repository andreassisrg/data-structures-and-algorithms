#ifndef PACOTE_HPP
#define PACOTE_HPP

#include "./lista_encadeada.hpp"

enum EstadoPacote {
    NAO_POSTADO = 1,
    CHEGADA_ESCALONADA = 2,
    ARMAZENADO = 3,
    REMOVIDO_PARA_TRANSPORTE = 4,
    ENTREGUE = 5
};

class Pacote {
    public:
        int id;
        int origem;
        int destino;
        ListaEncadeada<int>* caminho;
        int estado_atual;

        Pacote();
        ~Pacote();
};

#endif