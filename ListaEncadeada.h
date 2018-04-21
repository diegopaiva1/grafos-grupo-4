#ifndef LISTAENCADEADA_H
#define LISTAENCADEADA_H

#include <iostream>

#include "No.h"

class ListaEncadeada
{
    private:
        No *raiz;
    public:
        ListaEncadeada();
        ~ListaEncadeada();
        void inserir(No *no);
        bool contem(No *no);
        void imprimir();
        ListaEncadeada* novaLista();
        No* getRaiz();
};

#endif // LISTAENCADEADA_H
