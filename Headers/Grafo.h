/* Referência da biblioteca <list>: http://www.cplusplus.com/reference/list/list/
 *
 */

#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED

#include <iostream>
#include <list>

#include "GraphFileReader.h"
#include "Aresta.h"

class Grafo
{
private:
  std::string arquivo;
  int ordem;
  std::list<std::list<No *>> adjacencias;
  std::list<Aresta *> arestas;
  std::list<int> sequenciaGrau;
  bool possuiSelfLoop();
  bool possuiArestaMultipla();

public:
  Grafo(std::string arquivo);
  Grafo();
  ~Grafo();
  void setSequenciaGrau();
  int getOrdem();
  bool ehNulo();
  bool ehTrivial();
  bool ehCompleto();
  bool ehDigrafo();
  bool ehGrafoGeral();
  bool ehMultigrafo();
  bool ehBipartido();
  bool ehKRegular(int k);
  void imprimirAdjacencias();
  void imprimirArestas();
  void imprimirVizinhancaFechada(int id);
  void imprimirVizinhancaAberta(int id);
  void imprimirSequenciaGrau();
  void imprimirGrau(int id);
  void incluirAresta(Aresta *aresta);
  No *getNo(int id);
  void incluirNo(int id);
  void excluirNo(int id);
  bool possuiNo(int id);
};

#endif // GRAFO_H_INCLUDED
