#ifndef UTILS_HPP
#define UTILS_HPP

// Macros para impressão de estatísticas
#define ARMAZENADO_EM    " armazenado em "
#define REMOVIDO_DE      " removido de "
#define REARMAZENADO_EM  " rearmazenado em "
#define EM_TRANSITO      " em transito de "
#define ENTREGUE_EM      " entregue em "

#include <string>

#include "./lista_adjacencia.hpp"
#include "./escalonador.hpp"

ListaEncadeada<int>* BFS(ListaAdjacencia* grafo, int origem, int destino);

// Funções auxiliares para criar eventos de forma clara
Evento novoEventoChegada(double hora, int id_pacote);
Evento novoEventoTransporte(double hora, int armazem_de, int armazem_para, int id_pacote);

// Função para impressão das estatísticas
void imprimirEstatistica(int hora, int id_pacote, std::string operacao, int armazem);
void imprimirEstatistica(int hora, int id_pacote, std::string operacao, int armazem, int secao);

#endif