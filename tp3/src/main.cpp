#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>

#include "../include/utils.hpp"
#include "../include/lista_encadeada.hpp"

int main(int argc, char* argv[])
{
    std::string linha;
    ListaEncadeada<Evento*> eventos;

    while(std::getline(std::cin, linha))
    {
        std::istringstream iss(linha);

        int dataHora;
        std::string acao;
        iss >> dataHora >> acao;

        if (acao == "EV")
        {
            Evento* novoEvento = new Evento;
            iss >> novoEvento->tipoEvento >> novoEvento->idPacote;
            if (novoEvento->tipoEvento == "RG")
            {
                iss >> novoEvento->remetente       >>
                       novoEvento->destinatario    >>
                       novoEvento->armazemOrigem   >>
                       novoEvento->armazemDestino;
            }
            else if (novoEvento->tipoEvento == "TR")
            {
                iss >> novoEvento->armazemOrigem   >>
                       novoEvento->armazemDestino;
            }
            else if (novoEvento->tipoEvento == "EN")
            {
                iss >> novoEvento->armazemDestino;
            }
            else
            {
                iss >> novoEvento->armazemDestino  >>
                       novoEvento->secaoDestino;
            }

            eventos.InsereFinal(novoEvento);
        }
        else if (acao == "CL")
        {

        }
        else if (acao == "PC")
        {

        }
        else
        {
            std::cout << "Ação não prevista: " << acao << std::endl;
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}