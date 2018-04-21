/* Referência da biblioteca <forward_list>: http://www.cplusplus.com/reference/forward_list/forward_list/
 *
 */

#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED

#include <iostream>
#include <fstream>
#include <forward_list>
#include <algorithm>

#include "Aresta.h"

class Grafo
{
    private:
        int ordem;
        std::forward_list<std::forward_list<No*>> listaAdjacencia;
        std::forward_list<Aresta*> arestas;
        void leArquivo(std::string nomeArquivo);
        bool listaContemNo(std::forward_list<No*> lista, No *no);
        void popularListaAdjacencia(std::forward_list<No*> *lista);
    public:
        Grafo(std::string nomeArquivo);
        Grafo();
        ~Grafo();
        int getOrdem();
        bool ehNulo();
        bool ehTrivial();
        void imprimeListaAdjacencia();
        void imprimirArestas();
        void incluirNo(No *no);
        void incluirAresta(Aresta *aresta);
};

#endif // GRAFO_H_INCLUDED
