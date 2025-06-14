#ifndef UTILS_HPP
#define UTILS_HPP

#include "./lista_adjacencia.hpp"
#include "./escalonador.hpp"

ListaEncadeada<int>* BFS(ListaAdjacencia* grafo, int origem, int destino);

// Funções auxiliares para criar eventos de forma clara
Evento novoEventoChegada(double hora, int id_pacote);
Evento novoEventoTransporte(double hora, int armazem_de, int armazem_para, int id_pacote);

#endif