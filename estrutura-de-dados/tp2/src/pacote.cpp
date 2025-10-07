#include "../include/pacote.hpp"

Pacote::Pacote() {
    caminho = nullptr;
    armazemAtual = -1;
}

Pacote::~Pacote() {
    delete caminho;
}