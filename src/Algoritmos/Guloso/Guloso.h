/* Esta classe implementa algortimos gulosos para resolver alguns problemas pertencentes
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
private:
  static void preencherCandidatos(std::vector<No *> &candidatos, Grafo *grafo);
  static void ordenarCandidatosPor(std::vector<No *> &candidatos, bool (*criterio)(No *no1, No *no2));
  static bool grauCrescente(No *no1, No *no2);
  static void removerVizinhosDoNoEscolhidoDosCandidatos(No *no, std::vector<No *> &candidatos);
  static void removerNoDosCandidatos(No *no, std::vector<No *> &candidatos);
public:
  static int subconjuntoIndependenteMaximo(Grafo *grafo);
};

#endif // GULOSO_H_INCLUDED
