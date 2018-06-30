/* Esta classe implementa algoritmos gulosos randomizados reativos para resolver alguns
 * problemas pertencentes à classe de problemas NP-completo.
 *
 * Problemas disponíveis:
 *  - Subconjunto independente máximo (https://pt.wikipedia.org/wiki/Conjunto_independente)
 */

#ifndef GULOSORANDOMIZADOREATIVO_H_INCLUDED
#define GULOSORANDOMIZADOREATIVO_H_INCLUDED

#define TAMANHO 10

#include <cmath> // ceil

#include "../GulosoRandomizado/GulosoRandomizado.h"

class GulosoRandomizadoReativo : public GulosoRandomizado
{
private:
  Guloso *guloso;
protected:
  int escolherIndiceAlpha(float *probabilidade);
  void atualizarProbabilidades(float *probabilidade, float *q);
  float somatorio(float *arrayNumeros);
public:
  GulosoRandomizadoReativo() { this->guloso = new Guloso(); };
  ~GulosoRandomizadoReativo() {};
  virtual std::list<No *> subconjuntoIndependenteMaximo(Grafo *grafo, int tamanhoBlocoAtualizacao,
                                                        int iteracoesMaximas);
};

#endif // GULOSORANDOMIZADOREATIVO_H_INCLUDED
