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