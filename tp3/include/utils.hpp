#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>

struct Evento
{
    std::string dataHora;
    std::string tipoEvento;
    std::string idPacote;
    std::string remetente;
    std::string destinatario;
    int armazemOrigem;
    int armazemDestino;
    int secaoDestino;
};

#endif