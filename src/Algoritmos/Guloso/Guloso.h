/* Esta classe implementa algoritmos gulosos para resolver alguns problemas pertencentes
 * à classe de problemas NP-completo.
 *
 * Problemas disponíveis:
 *  - Subconjunto independente máximo (https://pt.wikipedia.org/wiki/Conjunto_independente)
 */

#ifndef GULOSO_H_INCLUDED
#define GULOSO_H_INCLUDED

#include <iostream>
#include <vector>
#include <algorithm> // std::sort // std::remove

#include "../../Componentes/Grafo/Grafo.h"

class Guloso
{
protected:
  void preencherCandidatos(std::vector<No *> &candidatos, Grafo *grafo);
  void ordenarCandidatosPor(std::vector<No *> &candidatos, bool (*criterio)(No *no1, No *no2));
  static bool grauCrescente(No *no1, No *no2);
  virtual void atualizarCandidatos(No *no, std::vector<No *> &candidatos);
  void removerVizinhosDoNoEscolhidoDosCandidatos(No *no, std::vector<No *> &candidatos);
  void removerNoDosCandidatos(No *no, std::vector<No *> &candidatos);
public:
  Guloso() {};
  ~Guloso() {};
  virtual std::list<No *> subconjuntoIndependenteMaximo(Grafo *grafo, float alpha = 0,
                                                        int iteracoesMaximas = 1);
};

#endif // GULOSO_H_INCLUDED
