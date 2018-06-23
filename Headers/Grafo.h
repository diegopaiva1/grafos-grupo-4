/* Esta classe representa simplismente a estrutura de dados do Grafo:
 * nós, arestas e sua sequência de grau.
 * Todos os atributos são públicos por se tratar de uma estrutura de dados.
 */

#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED

#include <iostream>
#include <list>

#include "Arco.h"
#include "No.h"

class Grafo
{
public:
  Grafo();
  ~Grafo();
  int ordem;
  std::list<No *> nos;
  std::list<Arco *> arcos;
  std::list<int> sequenciaGrau;
};

#endif // GRAFO_H_INCLUDED
