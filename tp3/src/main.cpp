#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>

#include "../include/evento.hpp"
#include "../include/lista_encadeada.hpp"
#include "../include/indice_pacote.hpp"
#include "../include/indice_cliente.hpp"
#include "../include/utils.hpp"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Uso: " << argv[0] << " <arquivo_de_entrada>\n";
        return 1;
    }

    std::ifstream arquivo(argv[1]);
    if (!arquivo.is_open())
    {
        std::cerr << "Erro ao abrir o arquivo: " << argv[1] << "\n";
        return 1;
    }

    IndicePacote indicePacote;
    IndiceCliente indiceCliente;

    std::string linha;
    while (std::getline(arquivo, linha))
    {
        if (linha.empty())
            continue;

        std::istringstream iss(linha);
        int tempo;
        std::string tipoComando;
        iss >> tempo >> tipoComando;

        if (tipoComando == "EV")
        {
            std::string tipoEvento, idPacote;
            iss >> tipoEvento >> idPacote;

            Evento *evento = new Evento(tempo, tipoEvento, idPacote);

            if (tipoEvento == "RG")
            {
                iss >> evento->remetente >> evento->destinatario >> evento->armazemOrigem >> evento->armazemDestino;
            }
            else if (tipoEvento == "TR")
            {
                iss >> evento->armazemOrigem >> evento->armazemDestino;
            }
            else if (tipoEvento == "EN")
            {
                iss >> evento->armazemDestino;
            }
            else if (tipoEvento == "AR" || tipoEvento == "RM" || tipoEvento == "UR")
            {
                iss >> evento->armazemDestino >> evento->secaoDestino;
            }

            // Armazena evento
            indicePacote.InserirEvento(evento);

            if (tipoEvento == "RG")
            {
                indiceCliente.InserirEvento(evento->remetente, evento); // início = evento
                indiceCliente.InserirEvento(evento->destinatario, evento);
            }
            else
            {
                ListaEncadeada<Evento *> *eventos = indicePacote.BuscarEventos(idPacote);
                if (eventos)
                {
                    for (int i = 0; i < eventos->Tamanho(); ++i)
                    {
                        Evento *ev = (*eventos)[i];
                        if (ev->tipoEvento == "RG")
                        {
                            indiceCliente.InserirEvento(ev->remetente, evento); // fim = evento
                            indiceCliente.InserirEvento(ev->destinatario, evento);
                            break;
                        }
                    }
                }
            }
        }
        else if (tipoComando == "CL")
        {
            std::string nomeCliente;
            iss >> nomeCliente;

            std::cout << std::setw(6) << std::setfill('0') << tempo
                      << " CL " << nomeCliente << "\n";

            ListaEncadeada<PacoteDoCliente *> *pacotes = indiceCliente.BuscarPacotes(nomeCliente);
            if (!pacotes || pacotes->Tamanho() == 0)
            {
                std::cout << "0\n";
                continue;
            }

            // Vetor para armazenar eventos a serem exibidos
            ListaEncadeada<Evento *> eventosParaExibir;

            // Para cada pacote do cliente
            Nodo<PacoteDoCliente *> *atual = pacotes->GetCabeca();
            while (atual)
            {
                PacoteDoCliente *pacote = atual->valor;
                ListaEncadeada<Evento *> *eventos = indicePacote.BuscarEventos(pacote->idPacote);

                if (eventos)
                {
                    // Encontrar o evento de registro (RG)
                    Evento *eventoRG = nullptr;
                    for (int i = 0; i < eventos->Tamanho(); i++)
                    {
                        Evento *ev = (*eventos)[i];
                        if (ev->tipoEvento == "RG" && ev->dataHora <= tempo)
                        {
                            eventoRG = ev;
                            break;
                        }
                    }

                    // Encontrar o último evento válido até o tempo da consulta
                    Evento *ultimoEvento = nullptr;
                    for (int i = 0; i < eventos->Tamanho(); i++)
                    {
                        Evento *ev = (*eventos)[i];
                        if (ev->dataHora <= tempo)
                        {
                            ultimoEvento = ev;
                        }
                        else
                        {
                            break; // Eventos estão ordenados por tempo
                        }
                    }

                    // Adicionar eventos à lista para exibição
                    if (eventoRG)
                    {
                        eventosParaExibir.InsereFinal(eventoRG);
                    }

                    if (ultimoEvento && ultimoEvento != eventoRG)
                    {
                        eventosParaExibir.InsereFinal(ultimoEvento);
                    }
                }

                atual = atual->proximo;
            }

            // Ordenar eventos por tempo e ID do pacote
            // Implementação simples de insertion sort
            for (int i = 1; i < eventosParaExibir.Tamanho(); i++)
            {
                Evento *chave = eventosParaExibir[i];
                int j = i - 1;

                while (j >= 0 && (eventosParaExibir[j]->dataHora > chave->dataHora ||
                                  (eventosParaExibir[j]->dataHora == chave->dataHora &&
                                   std::stoi(eventosParaExibir[j]->idPacote) > std::stoi(chave->idPacote))))
                {
                    eventosParaExibir[j + 1] = eventosParaExibir[j];
                    j--;
                }
                eventosParaExibir[j + 1] = chave;
            }

            std::cout << eventosParaExibir.Tamanho() << "\n";
            for (int i = 0; i < eventosParaExibir.Tamanho(); i++)
            {
                printEvento(eventosParaExibir[i]);
            }
        }
        else if (tipoComando == "PC")
        {
            std::string idPacote;
            iss >> idPacote;

            std::cout << std::setw(6) << std::setfill('0') << tempo
                      << " PC " << idPacote << "\n";

            ListaEncadeada<Evento *> *eventos = indicePacote.BuscarEventos(idPacote);
            if (!eventos)
            {
                std::cout << "0\n";
                continue;
            }

            int count = 0;
            for (int i = 0; i < eventos->Tamanho(); ++i)
            {
                if ((*eventos)[i]->dataHora <= tempo)
                {
                    count++;
                }
                else
                {
                    break; // Eventos estão ordenados por tempo
                }
            }

            std::cout << count << "\n";
            for (int i = 0; i < eventos->Tamanho(); ++i)
            {
                Evento *ev = (*eventos)[i];
                if (ev->dataHora <= tempo)
                {
                    printEvento(ev);
                }
                else
                {
                    break; // Eventos estão ordenados por tempo
                }
            }
        }
    }

    return 0;
}
