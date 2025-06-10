#ifndef PACOTE_HPP
#define PACOTE_HPP

#include "./lista_encadeada.hpp"

class Pacote {
    private:
        
    public:
        int id;
        int origem;
        int destino;
        ListaEncadeada<int> caminho;
        estado_atual;
        
};

#endif