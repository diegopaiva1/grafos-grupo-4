#ifndef ARCO_H_INCLUDED
#define ARCO_H_INCLUDED

#include "../No/No.h"

class Arco
{
public:
  Arco(No *no1, No *no2, double peso);
  ~Arco();
  No *no1;
  No *no2;
  double peso;
  bool possuemMesmasExtremidades(Arco *aresta);
};

#endif // ARCO_H_INCLUDED
