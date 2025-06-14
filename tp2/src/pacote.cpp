#include "../include/pacote.hpp"

Pacote::Pacote() {
    caminho = nullptr;
}

Pacote::~Pacote() {
    delete caminho;
}