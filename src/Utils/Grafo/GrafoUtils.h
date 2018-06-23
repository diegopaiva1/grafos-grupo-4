/* Esta classe contém uma diversidade de operações interessantes para serem
 * efetuadas em um grafo de entrada a fim de explorar suas propriedades.
 */

#ifndef GRAFOUTILS_H_INCLUDED
#define GRAFOUTILS_H_INCLUDED

#include <iostream>
#include <list>
#include <algorithm> // std::find

#include "../../Componentes/Grafo/Grafo.h"
#include "../No/NoUtils.h"

class GrafoUtils
{
private:
  static void atualizarSequenciaGrau(Grafo& grafo);
  static void excluirArcosComIdIgualA(Grafo& grafo, int id);
public:
  static bool ehNulo(Grafo& grafo);
  static bool ehTrivial(Grafo& grafo);
  static bool ehCompleto(Grafo& grafo);
  static bool possuiArcoMultiplo(Grafo& grafo);
  static bool possuiSelfLoop(Grafo& grafo);
  static bool ehGrafoGeral(Grafo& grafo);
  static bool ehMultigrafo(Grafo& grafo);
  static bool ehBipartido(Grafo& grafo);
  static bool ehKRegular(Grafo& grafo, int k);
  static bool ehDigrafo(Grafo& grafo);
  static bool possuiNo(Grafo& grafo, int id);
  static bool possuiArco(Grafo& grafo, Arco *arco);
  static void incluirNo(Grafo& grafo, int id);
  static void incluirArco(Grafo& grafo, Arco *arco);
  static void excluirNo(Grafo& grafo, int id);
  static No* getNo(Grafo& grafo, int id);
  static void imprimirAdjacencias(Grafo& grafo);
  static void imprimirArcos(Grafo& grafo);
  static void imprimirVizinhancaFechada(Grafo& grafo, int id);
  static void imprimirVizinhancaAberta(Grafo& grafo, int id);
  static void imprimirSequenciaGrau(Grafo& grafo);
  static void imprimirGrau(Grafo& grafo, int id);
};

#endif // GRAFOUTILS_H_INCLUDED
