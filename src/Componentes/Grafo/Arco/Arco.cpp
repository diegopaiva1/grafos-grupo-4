#include "./Arco.h"

Arco::Arco(No *no1, No *no2, double peso)
{
  this->no1 = no1;
  this->no2 = no2;
  this->peso = peso;
  this->no1->adjacentes.push_back(no2);
}

Arco::~Arco()
{
  // destrutor
}

bool Arco::possuemMesmasExtremidades(Arco *arco)
{
  No *no3 = arco->no1;
  No *no4 = arco->no2;

  return (this->no1 == no3 && this->no2 == no4);
}
