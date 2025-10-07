#include "../include/armazem.hpp"

Armazem::Armazem() {}

void Armazem::Inicializar(int total_armazens) {
    this->total_armazens = total_armazens;
    secoes = new Pilha<Pacote*>[total_armazens];
}

Armazem::~Armazem() {
    delete[] secoes;
}

void Armazem::ArmazenarPacote(Pacote* pacote) {
    int destino = pacote->destino;
    secoes[destino].Empilha(pacote);
}

void Armazem::ArmazenarPacote(Pacote* pacote, int destino_secao) {
    secoes[destino_secao].Empilha(pacote);
}

Pacote* Armazem::RemoverPacote(int destino, int custoRemocao, int& tempoRemocao) {
    // Remove o pacote do topo da pilha da seção "destino"
    Pilha<Pacote*>& pilha = secoes[destino];
    if (pilha.Vazia()) return nullptr;

    // Calcular custo de remoção: depende da posição
    int n = pilha.Tamanho();
    Pilha<Pacote*> auxiliar;
    for (int i = 0; i < n - 1; i++) {
        auxiliar.Empilha(pilha.Desempilha());
    }

    Pacote* pacoteRemovido = pilha.Desempilha();
    tempoRemocao = (n - 1) * custoRemocao;

    // Devolve os pacotes à pilha
    while (!auxiliar.Vazia()) {
        pilha.Empilha(auxiliar.Desempilha());
    }

    return pacoteRemovido;
}

bool Armazem::SecaoVazia(int destino) {
    return secoes[destino].Vazia();
}

Pilha<Pacote*>& Armazem::GetSecao(int destino) {
    return secoes[destino];
}

int Armazem::CustoRemocao(int secao, int id_pacote, int custoRemocao) {
    Pilha<Pacote*>& pilha = secoes[secao];
    if (pilha.Vazia()) return -1;

    Pilha<Pacote*> auxiliar;
    int custo = 0;
    bool encontrado = false;

    while (!pilha.Vazia()) {
        Pacote* topo = pilha.Desempilha();
        auxiliar.Empilha(topo);
        if (topo->id == id_pacote) {
            encontrado = true;
            break;
        }
        custo += custoRemocao;
    }

    // Restaura a pilha original
    while (!auxiliar.Vazia()) {
        pilha.Empilha(auxiliar.Desempilha());
    }

    return encontrado ? custo : -1;
}

Pacote* Armazem::Desempilha(int secao) {
    Pilha<Pacote*>& pilha = secoes[secao];
    if (pilha.Vazia()) return nullptr;
    return pilha.Desempilha();
}

int Armazem::CustoRemocaoTotal(int destino, int custoRemocao) {
    Pilha<Pacote*>& pilha = secoes[destino];
    return pilha.Tamanho() * custoRemocao;
}

bool Armazem::ContemPacoteNaSecao(int destino_secao, Pacote* pacote) {
    Pilha<Pacote*>& pilha = secoes[destino_secao];
    Pilha<Pacote*> auxiliar;
    bool encontrado = false;

    // Percorre a pilha procurando o pacote
    while (!pilha.Vazia()) {
        Pacote* topo = pilha.Desempilha();
        if (topo == pacote) {
            encontrado = true;
        }
        auxiliar.Empilha(topo);
    }

    // Restaura a pilha original
    while (!auxiliar.Vazia()) {
        pilha.Empilha(auxiliar.Desempilha());
    }

    return encontrado;
}
