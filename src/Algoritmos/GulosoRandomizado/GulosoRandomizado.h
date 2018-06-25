/* Esta classe implementa algoritmos gulosos randomizados para resolver alguns problemas
 * pertencentes à classe de problemas NP-completo.
 *
 * Problemas disponíveis:
 *  - Subconjunto independente máximo (https://pt.wikipedia.org/wiki/Conjunto_independente)
 */

#ifndef GULOSORANDOMIZADO_H_INCLUDED
#define GULOSORANDOMIZADO_H_INCLUDED

#include <cmath> // ceil

#include "../Guloso/Guloso.h"

class GulosoRandomizado : public Guloso
{
protected:
  int gerarInteiroAleatorioEntre(int limiteInferior, int limiteSuperior);
public:
  GulosoRandomizado() {};
  ~GulosoRandomizado() {};
  virtual std::list<No *> subconjuntoIndependenteMaximo(Grafo *grafo, float alpha,
                                                        int iteracoesMaximas);
};

#endif // GULOSORANDOMIZADO_H_INCLUDED
