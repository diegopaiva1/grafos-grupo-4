#include "../Headers/Grafo.h"

using namespace std;

int main()
{
    Grafo *grafo = new Grafo("grafo.txt");

    grafo->imprimirListaListaAdjacencias();
    cout << endl;
    grafo->imprimirArestas();
    cout << endl;
    grafo->imprimirSequenciaGrau();
    cout << endl;
    cout << grafo->ehCompleto() << endl;
}
