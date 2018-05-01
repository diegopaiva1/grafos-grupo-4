/* Referência da biblioteca <list>: http://www.cplusplus.com/reference/list/list/
 *
 */

#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED

#include <iostream>
#include <fstream>
#include <list>

#include "GraphFileReader.h"
#include "Aresta.h"

class Grafo
{
    private:
        int ordem;
        std::string arquivo;
        std::list<std::list<No*>> listaListaAdjacencias;
        std::list<Aresta*> arestas;
        std::list<int> sequenciaGrau;
        bool possuiSelfLoop();
        bool possuiArestaMultipla();
    public:
        Grafo(std::string arquivo);
        Grafo();
        ~Grafo();
        int getOrdem();
        bool ehNulo();
        bool ehTrivial();
        bool ehMultigrafo();
        bool ehCompleto();
        bool ehKRegular(int k);
        bool ehDigrafo();
        bool ehGrafoGeral();
        void setSequenciaGrau();
        void imprimirListaListaAdjacencias();
        void imprimirArestas();
        void imprimirVizinhancaFechada(int id);
        void imprimirVizinhancaAberta(int id);
        void imprimirSequenciaGrau();
        void imprimirGrau(int id);
        void incluirNo(No *no);
        void excluirNo(int id);
        void incluirAresta(Aresta *aresta);
        No* getNo(int id);
};

#endif // GRAFO_H_INCLUDED
