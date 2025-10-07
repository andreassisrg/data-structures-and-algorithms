#include "../include/indice_cliente.hpp"

IndiceCliente::IndiceCliente() : raiz(nullptr) {}

IndiceCliente::~IndiceCliente() {
    liberar(raiz);
}

void IndiceCliente::InserirEvento(const std::string& nome, Evento* evento) {
    bool isRG = (evento->tipoEvento == "RG");
    raiz = inserir(raiz, evento, nome, evento->idPacote, isRG);
}

ListaEncadeada<PacoteDoCliente*>* IndiceCliente::BuscarPacotes(const std::string& nomeCliente) {
    NoCliente* no = buscar(raiz, nomeCliente);
    if (no) return &(no->pacotes);
    return nullptr;
}

NoCliente* IndiceCliente::inserir(NoCliente* no, Evento* evento, const std::string& nomeCliente, const std::string& idPacote, bool isRG) {
    if (!no) {
        NoCliente* novo = new NoCliente(nomeCliente);
        novo->pacotes.InsereFinal(new PacoteDoCliente(idPacote, evento));
        return novo;
    }

    if (nomeCliente < no->nome)
        no->esq = inserir(no->esq, evento, nomeCliente, idPacote, isRG);
    else if (nomeCliente > no->nome)
        no->dir = inserir(no->dir, evento, nomeCliente, idPacote, isRG);
    else {
        Nodo<PacoteDoCliente*>* atual = no->pacotes.GetCabeca();
        while (atual) {
            if (atual->valor->idPacote == idPacote) {
                if (isRG) atual->valor->inicio = evento;
                atual->valor->fim = evento;
                return no;
            }
            atual = atual->proximo;
        }
        no->pacotes.InsereFinal(new PacoteDoCliente(idPacote, evento));
    }

    return balancear(no);
}

NoCliente* IndiceCliente::buscar(NoCliente* no, const std::string& nome) const {
    if (!no || no->nome == nome)
        return no;
    if (nome < no->nome)
        return buscar(no->esq, nome);
    return buscar(no->dir, nome);
}

int IndiceCliente::altura(NoCliente* no) {
    return no ? no->altura : 0;
}

int IndiceCliente::balanceamento(NoCliente* no) {
    return no ? altura(no->esq) - altura(no->dir) : 0;
}

NoCliente* IndiceCliente::rotacaoDireita(NoCliente* y) {
    NoCliente* x = y->esq;
    y->esq = x->dir;
    x->dir = y;

    y->altura = std::max(altura(y->esq), altura(y->dir)) + 1;
    x->altura = std::max(altura(x->esq), altura(x->dir)) + 1;

    return x;
}

NoCliente* IndiceCliente::rotacaoEsquerda(NoCliente* x) {
    NoCliente* y = x->dir;
    x->dir = y->esq;
    y->esq = x;

    x->altura = std::max(altura(x->esq), altura(x->dir)) + 1;
    y->altura = std::max(altura(y->esq), altura(y->dir)) + 1;

    return y;
}

NoCliente* IndiceCliente::balancear(NoCliente* no) {
    no->altura = std::max(altura(no->esq), altura(no->dir)) + 1;
    int fb = balanceamento(no);

    if (fb > 1 && balanceamento(no->esq) >= 0)
        return rotacaoDireita(no);
    if (fb < -1 && balanceamento(no->dir) <= 0)
        return rotacaoEsquerda(no);
    if (fb > 1 && balanceamento(no->esq) < 0) {
        no->esq = rotacaoEsquerda(no->esq);
        return rotacaoDireita(no);
    }
    if (fb < -1 && balanceamento(no->dir) > 0) {
        no->dir = rotacaoDireita(no->dir);
        return rotacaoEsquerda(no);
    }

    return no;
}

void IndiceCliente::liberar(NoCliente* no) {
    if (!no) return;
    liberar(no->esq);
    liberar(no->dir);
    Nodo<PacoteDoCliente*>* p = no->pacotes.GetCabeca();
    while (p) {
        delete p->valor;
        p = p->proximo;
    }
    delete no;
}
