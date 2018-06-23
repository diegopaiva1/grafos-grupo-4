/* Esta classe realiza a implementação de heurísticas para solução do problema
 * do subconjunto independente máximo (https://pt.wikipedia.org/wiki/Conjunto_independente),
 * que é um problema pertencente à classe de problemas NP-completo.
 *
 * Técnicas utilizadas:
 * - Algoritmo guloso
 * - Algoritmo guloso randomizado
 * - Algoritmo guloso randomizado reativo
 */

#ifndef SUBCONJUNTOINDEPENDENTEMAXIMO_H_INCLUDED
#define SUBCONJUNTOINDEPENDENTEMAXIMO_H_INCLUDED

#include <iostream>
#include <list>

#include "../../Componentes/Grafo/Grafo.h"

class SubconjuntoIndependenteMaximo
{
private:
  static bool grauCrescente(No *no1, No *no2);
  static void atualizarCandidatos(std::list<No *> &candidatos);
public:
  static int guloso(Grafo *grafo);
};

#endif // SUBCONJUNTOINDEPENDENTEMAXIMO_H_INCLUDED
