#include "../include/Set.hpp"


StringSet::StringSet(int tamanho) {
    tamanhoOriginal = tamanho;
    tamanhoTabela = tamanho;
    tamanhoConjunto = 0;
    tabela = new ElementoTabela[tamanho];

    for (int i = 0; i < tamanho; i++) {
        tabela[i].dado = "";
        tabela[i].vazio = true;
        tabela[i].retirada = false;
    }
}


StringSet::~StringSet() {
    delete[] tabela;
}


void StringSet::Inserir(string s) {
    // Elementos devem ser únicos em um conjunto
    if (Pertence(s)) return;

    // Se a tabela estiver maior que uma constante arbitrária, é necessário recriá-la
    double K = 0.7;
    if (((double)tamanhoConjunto / tamanhoTabela) > K)
        Resize(2 * tamanhoTabela + 1);

    // Hash precisa vir após o possível Resize da tabela
    int indice_s = Hash(s);

    // Elementos com colisão são armazenados nas posições sequenciais ao índice do hash
    while (true) {
        if (tabela[indice_s].vazio) {
            tabela[indice_s].dado = s;
            tabela[indice_s].vazio = false;
            tabela[indice_s].retirada = false;
            tamanhoConjunto++;
            return;
        }
        indice_s = (indice_s + 1) % tamanhoTabela;
    }
}


void StringSet::Remover(string s) {
    // Se o elemento não estiver presente, não há nada a fazer
    if (!Pertence(s)) return;

    int indice_s = Hash(s);
    while(true) {
        if (!tabela[indice_s].vazio && tabela[indice_s].dado == s) {
            tabela[indice_s].dado = "";
            tabela[indice_s].vazio = true;
            tabela[indice_s].retirada = true;
            tamanhoConjunto--;
            return;
        }
        indice_s = (indice_s + 1) % tamanhoTabela;
    }
}


bool StringSet::Pertence(string s) {
    int indice_s = Hash(s);
    int indice_acesso;

    // Esse método, no pior caso, é uma busca em um array circular
    for (int i = 0; i < tamanhoTabela; i++) {
        indice_acesso = (i + indice_s) % tamanhoTabela;

        if (tabela[indice_acesso].vazio && !tabela[indice_acesso].retirada) { // Valor nunca utilizado
            return false;
        }

        if (!tabela[indice_acesso].vazio && tabela[indice_acesso].dado == s) { // Valor que queremos
            return true;
        }
    }

    // Loop percorreu mas não encontrou o dado
    return false;
}


StringSet* StringSet::Intersecao(StringSet *S) {
    StringSet* conjuntoIntersecao = new StringSet(tamanhoTabela);

    for (int i = 0; i < tamanhoTabela; i++) {
        if (S->Pertence(tabela[i].dado)) {
            conjuntoIntersecao->Inserir(tabela[i].dado);
        }
    }

    return conjuntoIntersecao;
}