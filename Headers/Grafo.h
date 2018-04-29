/* Referência da biblioteca <list>: http://www.cplusplus.com/reference/list/list/
 *
 */

#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED

#include <iostream>
#include <fstream>
#include <list>

#include "Aresta.h"

class Grafo
{
    private:
        int ordem;
        std::string arquivo;
        std::list<std::list<No*>> listaListaAdjacencias;
        std::list<Aresta*> arestas;
        std::list<int> sequenciaGrau;
        void leArquivo();
        bool listaContemNo(std::list<No*> lista, No *no);
        void popularlistaListaAdjacencias(std::list<No*> *lista);
    public:
        Grafo(std::string arquivo);
        Grafo();
        ~Grafo();
        int getOrdem();
        bool ehNulo();
        bool ehTrivial();
        bool ehMultigrafo();
        bool ehCompleto();
        void setSequenciaGrau();
        void imprimirListaListaAdjacencias();
        void imprimirArestas();
        void imprimirVizinhancaFechada(int id);
        void imprimirVizinhancaAberta(int id);
        void imprimirSequenciaGrau();
        void incluirNo(No *no);
        void excluirNo(int id);
        void incluirAresta(Aresta *aresta);
        No* getNo(int id);
};

#endif // GRAFO_H_INCLUDED
