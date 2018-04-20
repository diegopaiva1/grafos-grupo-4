#include "ListaEncadeada.h"

ListaEncadeada::ListaEncadeada()
{
    this->raiz = NULL;
}

ListaEncadeada::~ListaEncadeada()
{
    //dtor
}

void ListaEncadeada::inserirNoInicio(No *no)
{
    no->setProximoNo(this->raiz);
    this->raiz = no;
}

bool ListaEncadeada::contem(No *no)
{
    bool contem;
    if(raiz != NULL) {
        No *p = raiz;
        while(p != NULL) {
            if(p->getId() == no->getId()) {
                return true;
            }
            p = p->getProximoNo();
        }
    }
    return false;
}

void ListaEncadeada::imprimir()
{
    if(raiz != NULL) {
        No *percorre = raiz;
        while(percorre != NULL) {
            std::cout << percorre->getId() << " ";
            percorre = percorre->getProximoNo();
        }
    }
}

No* ListaEncadeada::getRaiz()
{
    return this->raiz;
}
