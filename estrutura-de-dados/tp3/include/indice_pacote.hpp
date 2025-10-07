#ifndef INDICE_PACOTE_HPP
#define INDICE_PACOTE_HPP

#include <string>
#include "../include/lista_encadeada.hpp"
#include "../include/evento.hpp"

struct NoPacote {
    std::string idPacote;
    ListaEncadeada<Evento*> eventos;
    NoPacote* esq;
    NoPacote* dir;
    int altura;

    NoPacote(const std::string& id) : idPacote(id), esq(nullptr), dir(nullptr), altura(1) {}
};

class IndicePacote {
private:
    NoPacote* raiz;

    NoPacote* inserir(NoPacote* no, Evento* evento);
    NoPacote* buscar(NoPacote* no, const std::string& idPacote) const;
    int altura(NoPacote* no);
    int balanceamento(NoPacote* no);
    NoPacote* rotacaoDireita(NoPacote* y);
    NoPacote* rotacaoEsquerda(NoPacote* x);
    NoPacote* balancear(NoPacote* no);
    void liberar(NoPacote* no);

public:
    IndicePacote();
    ~IndicePacote();
    void InserirEvento(Evento* evento);
    ListaEncadeada<Evento*>* BuscarEventos(const std::string& idPacote);
};

#endif
