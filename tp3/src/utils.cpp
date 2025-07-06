#include <iostream>
#include <iomanip>

#include "../include/utils.hpp"

void printEvento(const Evento *e)
{
    std::cout << std::setw(7) << std::setfill('0') << e->dataHora << " EV " << e->tipoEvento << " "
              << std::setw(3) << std::setfill('0') << e->idPacote;

    if (e->tipoEvento == "RG")
    {
        std::cout << " " << e->remetente
                  << " " << e->destinatario
                  << " " << std::setw(3) << std::setfill('0') << e->armazemOrigem
                  << " " << std::setw(3) << std::setfill('0') << e->armazemDestino;
    }
    else if (e->tipoEvento == "TR")
    {
        std::cout << " " << std::setw(3) << std::setfill('0') << e->armazemOrigem
                  << " " << std::setw(3) << std::setfill('0') << e->armazemDestino;
    }
    else if (e->tipoEvento == "EN")
    {
        std::cout << " " << std::setw(3) << std::setfill('0') << e->armazemDestino;
    }
    else
    { // AR, RM, UR
        std::cout << " " << std::setw(3) << std::setfill('0') << e->armazemDestino
                  << " " << std::setw(3) << std::setfill('0') << e->secaoDestino;
    }

    std::cout << "\n";
}