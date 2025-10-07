#include "../include/unionFind.hpp"

UnionFind::UnionFind(int quantidade_subconjuntos) {
    tamanho = quantidade_subconjuntos;
    subconjuntos = new Subconjunto[quantidade_subconjuntos];

    for (int i = 0; i < quantidade_subconjuntos; i++) {
        Make(i);
    }
}

UnionFind::~UnionFind() {
    delete[] subconjuntos;
}

void UnionFind::Make(int x) {
    Subconjunto s;
    s.representante = x;
    s.rank = 0;
    subconjuntos[x] = s;
}

int UnionFind::Find(int x) {
    int representante = subconjuntos[x].representante;
    return subconjuntos[x].representante = (representante == x ? x : Find(representante));
}

void UnionFind::Union(int x, int y) {
    x = Find(x);
    y = Find(y);

    if (subconjuntos[x].representante == subconjuntos[y].representante) return;
    if (subconjuntos[x].rank > subconjuntos[y].rank) {
        Subconjunto temp;
        temp = subconjuntos[x];
        subconjuntos[x] = subconjuntos[y];
        subconjuntos[y] = temp;

    }
    subconjuntos[x].representante = subconjuntos[y].representante;
    subconjuntos[y].rank += subconjuntos[x].rank;
}