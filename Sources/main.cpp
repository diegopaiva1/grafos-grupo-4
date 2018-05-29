#include "../Headers/Grafo.h"

using namespace std;

int main()
{
  Grafo *grafo = new Grafo("grafo.txt");
  int k = 4;
  grafo->incluirAresta(3, 2, 28);
  grafo->imprimirAdjacencias();
  cout << endl;
  grafo->imprimirArestas();
  cout << endl;
  cout << "Ordem: " << grafo->getOrdem() << endl;
  grafo->imprimirSequenciaGrau();
  cout << endl;
  grafo->ehNulo() ? cout << "È nulo\n" : cout << "Não é nulo\n";
  grafo->ehTrivial() ? cout << "È trivial\n" : cout << "Não é trivial\n";
  grafo->ehCompleto() ? cout << "È completo\n" : cout << "Não é completo\n";
  grafo->ehKRegular(k) ? cout << "È " << k << "-regular\n" : cout << "Não é " << k << "-regular\n";
  grafo->ehMultigrafo() ? cout << "È multigrafo\n" : cout << "Não é multigrafo\n";
  grafo->ehGrafoGeral() ? cout << "È grafo geral\n" : cout << "Não é grafo geral\n";
  grafo->ehBipartido() ? cout << "É bipartido\n" : cout << "Não é bipartido\n";
  grafo->imprimirVizinhancaAberta(1);
  cout << endl;
  grafo->imprimirVizinhancaFechada(2);
  cout << endl;
  grafo->imprimirGrau(2);
}
