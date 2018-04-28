#ifndef ARESTA_H_INCLUDED
#define ARESTA_H_INCLUDED

#include "No.h"

class Aresta
{
    private:
        No *primeiroNo;
        No *segundoNo;
        double peso;
    public:
        Aresta(No *primeiroNo, No *segundoNo, double peso);
        ~Aresta();
        No* getPrimeiroNo();
        No* getSegundoNo();
        double getPeso();
};


#endif // ARESTA_H_INCLUDED
