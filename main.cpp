#include "Grafo.h"
#include <forward_list>

using namespace std;

int main()
{
    Grafo *grafo = new Grafo("grafo.txt");

    No *no1 = new No(6);
    No *no2 = new No(7);

    grafo->incluirNo(no1);
    grafo->incluirNo(no2);

    Aresta *aresta = new Aresta(no1, no2, 120);

    grafo->incluirAresta(aresta);

    grafo->imprimeListaAdjacencia();
    cout << endl;
    grafo->imprimirArestas();

    return 0;
}
