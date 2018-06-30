#include "./Componentes/Grafo/Grafo.h"
#include "./Componentes/Arquivo/Leitor/LeitorArquivoGrafo.h"
#include "./Algoritmos/Guloso/Guloso.h"
#include "./Algoritmos/GulosoRandomizado/GulosoRandomizado.h"
#include "./Algoritmos/GulosoRandomizadoReativo/GulosoRandomizadoReativo.h"

using namespace std;

int main()
{
  // Initialize random seed
  srand(time(NULL));

  Grafo *grafo = new Grafo();

  LeitorArquivoGrafo::atribuirDados("grafo.txt", *grafo);

  Guloso *guloso = new Guloso();
  GulosoRandomizado *gulosoRandomizado = new GulosoRandomizado();
  GulosoRandomizadoReativo *gulosoRandomizadoReativo = new GulosoRandomizadoReativo();

  cout << "Guloso subconjunto independente máximo:" << endl;
  cout << guloso->subconjuntoIndependenteMaximo(grafo).size() << endl;

  for (float i = 0.10; i < 0.40; i += 0.10)
  {
    std::list<No *> solucao = gulosoRandomizado->subconjuntoIndependenteMaximo(grafo, i, 1000);
    cout << "Guloso randomizado subconjunto independente máximo (alpha = " << i << ", n = 1000):\n";
    cout << solucao.size() << endl;
  }

  std::list<No *> solucao = gulosoRandomizadoReativo->subconjuntoIndependenteMaximo(grafo, 50, 1000);
  cout << "Guloso randomizado reativo (blocos = 100, n = 1000)\n";
  cout << solucao.size() << endl;
}
