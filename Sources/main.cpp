#include "../Headers/Grafo.h"
#include <list>
#include <iterator>
#include <exception>

using namespace std;

int main()
{
    Grafo *grafo = new Grafo("grafo.txt");

    grafo->imprimeListaAdjacencia();
    cout << endl;
    grafo->imprimirArestas();
    cout << endl;
    cout << grafo->ehMultigrafo() << endl;
}
