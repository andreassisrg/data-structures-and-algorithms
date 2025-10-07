#ifndef EVENTO_HPP
#define EVENTO_HPP

#include <string>

struct Evento {
    int dataHora;
    std::string tipoEvento;
    std::string idPacote;
    std::string remetente;
    std::string destinatario;
    int armazemOrigem;
    int armazemDestino;
    int secaoDestino;
    Evento* prox;

    Evento(int tempo, const std::string& tipo, const std::string& id)
        : dataHora(tempo), tipoEvento(tipo), idPacote(id),
          armazemOrigem(0), armazemDestino(0), secaoDestino(0),
          prox(nullptr) {}
};

#endif
