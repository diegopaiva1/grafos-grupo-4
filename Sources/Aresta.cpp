#include "../Headers/Aresta.h"

Aresta::Aresta(No *primeiroNo, No *segundoNo, double peso)
{
    this->primeiroNo = primeiroNo;
    this->segundoNo = segundoNo;
    this->peso = peso;
}

Aresta::~Aresta()
{
    // destrutor
}

No* Aresta::getPrimeiroNo()
{
    return this->primeiroNo;
}

No* Aresta::getSegundoNo()
{
    return this->segundoNo;
}

double Aresta::getPeso()
{
    return this->peso;
}
