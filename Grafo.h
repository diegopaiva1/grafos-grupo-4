/* Fonte consultada para estudo da lista encadeada: https://pt.wikibooks.org/wiki/Programar_em_C/Listas_encadeadas
 *
 */

#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED

#include <iostream>
#include <fstream>

#include "ListaEncadeada.h"
#include "Aresta.h"

class Grafo
{
    private:
        int ordem;
        ListaEncadeada *listaNos;
        Aresta *arestas;
        void leArquivo(std::string nomeArquivo);
    public:
        Grafo(std::string nomeArquivo);
        Grafo();
        ~Grafo();
        int getOrdem();
        bool ehNulo();
        ListaEncadeada* getListaNos();
};

#endif // GRAFO_H_INCLUDED
