#include "../include/indice_pacote.hpp"

IndicePacote::IndicePacote() : raiz(nullptr) {}

IndicePacote::~IndicePacote()
{
    liberar(raiz);
}

void IndicePacote::InserirEvento(Evento *evento)
{
    raiz = inserir(raiz, evento);
}

ListaEncadeada<Evento *> *IndicePacote::BuscarEventos(const std::string &idPacote)
{
    NoPacote *no = buscar(raiz, idPacote);
    if (no)
        return &(no->eventos);
    return nullptr;
}

NoPacote *IndicePacote::inserir(NoPacote *no, Evento *evento)
{
    if (!no)
    {
        NoPacote *novo = new NoPacote(evento->idPacote);
        novo->eventos.InsereFinal(evento); // <-- insere o evento corretamente
        return novo;
    }

    if (evento->idPacote < no->idPacote)
        no->esq = inserir(no->esq, evento);
    else if (evento->idPacote > no->idPacote)
        no->dir = inserir(no->dir, evento);
    else
    {
        no->eventos.InsereFinal(evento);
        return no;
    }

    return balancear(no);
}

NoPacote *IndicePacote::buscar(NoPacote *no, const std::string &idPacote) const
{
    if (!no || no->idPacote == idPacote)
        return no;

    if (idPacote < no->idPacote)
        return buscar(no->esq, idPacote);
    else
        return buscar(no->dir, idPacote);
}

int IndicePacote::altura(NoPacote *no)
{
    return no ? no->altura : 0;
}

int IndicePacote::balanceamento(NoPacote *no)
{
    return no ? altura(no->esq) - altura(no->dir) : 0;
}

NoPacote *IndicePacote::rotacaoDireita(NoPacote *y)
{
    NoPacote *x = y->esq;
    y->esq = x->dir;
    x->dir = y;

    y->altura = std::max(altura(y->esq), altura(y->dir)) + 1;
    x->altura = std::max(altura(x->esq), altura(x->dir)) + 1;

    return x;
}

NoPacote *IndicePacote::rotacaoEsquerda(NoPacote *x)
{
    NoPacote *y = x->dir;
    x->dir = y->esq;
    y->esq = x;

    x->altura = std::max(altura(x->esq), altura(x->dir)) + 1;
    y->altura = std::max(altura(y->esq), altura(y->dir)) + 1;

    return y;
}

NoPacote *IndicePacote::balancear(NoPacote *no)
{
    no->altura = std::max(altura(no->esq), altura(no->dir)) + 1;
    int fb = balanceamento(no);

    if (fb > 1 && balanceamento(no->esq) >= 0)
        return rotacaoDireita(no);
    if (fb < -1 && balanceamento(no->dir) <= 0)
        return rotacaoEsquerda(no);
    if (fb > 1 && balanceamento(no->esq) < 0)
    {
        no->esq = rotacaoEsquerda(no->esq);
        return rotacaoDireita(no);
    }
    if (fb < -1 && balanceamento(no->dir) > 0)
    {
        no->dir = rotacaoDireita(no->dir);
        return rotacaoEsquerda(no);
    }

    return no;
}

void IndicePacote::liberar(NoPacote *no)
{
    if (!no)
        return;
    liberar(no->esq);
    liberar(no->dir);
    delete no;
}
