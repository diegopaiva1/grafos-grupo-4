#include "Grafo.h"

int main()
{
    Grafo *grafo = new Grafo("grafo.txt");

    grafo->getListaNos()->imprimir();

    std::cout << std::endl;
    std::cout << grafo->getOrdem() << std::endl;
    std::cout << grafo->ehNulo() << std::endl;

    delete grafo;

    return 0;
}
