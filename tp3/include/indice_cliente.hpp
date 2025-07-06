#ifndef INDICE_CLIENTE_HPP
#define INDICE_CLIENTE_HPP

#include "evento.hpp"
#include "lista_encadeada.hpp"
#include <string>

struct PacoteDoCliente {
    std::string idPacote;
    Evento* inicio;
    Evento* fim;

    PacoteDoCliente(const std::string& id, Evento* ev)
        : idPacote(id), inicio(ev), fim(ev) {}
};

struct NoCliente {
    std::string nome;
    ListaEncadeada<PacoteDoCliente*> pacotes;
    NoCliente* esq;
    NoCliente* dir;
    int altura;

    NoCliente(const std::string& nomeCliente)
        : nome(nomeCliente), esq(nullptr), dir(nullptr), altura(1) {}
};

class IndiceCliente {
private:
    NoCliente* raiz;

    NoCliente* inserir(NoCliente* no, Evento* evento, const std::string& nomeCliente, const std::string& idPacote, bool isRG);
    NoCliente* buscar(NoCliente* no, const std::string& nome) const;
    NoCliente* rotacaoEsquerda(NoCliente* x);
    NoCliente* rotacaoDireita(NoCliente* y);
    int altura(NoCliente* no);
    int balanceamento(NoCliente* no);
    NoCliente* balancear(NoCliente* no);
    void liberar(NoCliente* no);

public:
    IndiceCliente();
    ~IndiceCliente();

    void InserirEvento(const std::string& nome, Evento* evento);
    ListaEncadeada<PacoteDoCliente*>* BuscarPacotes(const std::string& nomeCliente);
};

#endif
