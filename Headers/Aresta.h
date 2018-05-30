#ifndef ARESTA_H_INCLUDED
#define ARESTA_H_INCLUDED

#include "No.h"

class Aresta
{
private:
  No *primeiraExtremidade;
  No *segundaExtremidade;
  double peso;

public:
  Aresta(No *primeiraExtremidade, No *segundaExtremidade, double peso);
  ~Aresta();
  No *getPrimeiraExtremidade();
  No *getSegundaExtremidade();
  double getPeso();
  bool possuemMesmasExtremidades(Aresta *aresta);
};

#endif // ARESTA_H_INCLUDED
