#include "../Headers/Aresta.h"

Aresta::Aresta(No *primeiraExtremidade, No *segundaExtremidade, double peso)
{
  this->primeiraExtremidade = primeiraExtremidade;
  this->segundaExtremidade = segundaExtremidade;
  this->peso = peso;
}

Aresta::~Aresta()
{
  // destrutor
}

No *Aresta::getPrimeiraExtremidade()
{
  return this->primeiraExtremidade;
}

No *Aresta::getSegundaExtremidade()
{
  return this->segundaExtremidade;
}

double Aresta::getPeso()
{
  return this->peso;
}

bool Aresta::possuemMesmasExtremidades(Aresta *aresta)
{
  No *no1 = this->getPrimeiraExtremidade();
  No *no2 = this->getSegundaExtremidade();

  No *no3 = aresta->getPrimeiraExtremidade();
  No *no4 = aresta->getSegundaExtremidade();

  return (no1 == no3 && no2 == no4);
}
