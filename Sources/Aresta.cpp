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

bool Aresta::possuemMesmasExtremidades(Aresta *aresta)
{
    No *no1 = this->getPrimeiroNo();
    No *no2 = this->getSegundoNo();

    No *no3 = aresta->getPrimeiroNo();
    No *no4 = aresta->getSegundoNo();

    return (no1->ehIgualA(no3) && no2->ehIgualA(no4)) || (no1->ehIgualA(no4) && no2->ehIgualA(no3));
}
