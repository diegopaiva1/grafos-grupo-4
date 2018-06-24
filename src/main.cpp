#include "./Componentes/Grafo/Grafo.h"
#include "./Componentes/Arquivo/Leitor/LeitorArquivoGrafo.h"
#include "./Algoritmos/Guloso/Guloso.h"
#include "./Algoritmos/GulosoRandomizado/GulosoRandomizado.h"

using namespace std;

int main()
{
  // Initialize random seed
  srand(time(NULL));

  Grafo *grafo = new Grafo();

  LeitorArquivoGrafo::atribuirDados("grafo.txt", *grafo);

  Guloso *guloso = new Guloso();
  GulosoRandomizado *gulosoRandomizado = new GulosoRandomizado();

  cout << "Guloso subconjunto independente máximo:" << endl;
  cout << guloso->subconjuntoIndependenteMaximo(grafo).size() << endl;

  cout << "Guloso randomizado subconjunto independente máximo (alpha = 0.01, n = 1000):" << endl;
  cout << gulosoRandomizado->subconjuntoIndependenteMaximo(grafo, 0.01, 1000).size() << endl;

  cout << "Guloso randomizado subconjunto independente máximo (alpha = 0.02, n = 1000):" << endl;
  cout << gulosoRandomizado->subconjuntoIndependenteMaximo(grafo, 0.02, 1000).size() << endl;

  cout << "Guloso randomizado subconjunto independente máximo (alpha = 0.03, n = 1000):" << endl;
  cout << gulosoRandomizado->subconjuntoIndependenteMaximo(grafo, 0.03, 1000).size() << endl;

  cout << "Guloso randomizado subconjunto independente máximo (alpha = 0.04, n = 1000):" << endl;
  cout << gulosoRandomizado->subconjuntoIndependenteMaximo(grafo, 0.04, 1000).size() << endl;

  cout << "Guloso randomizado subconjunto independente máximo (alpha = 0.05, n = 1000):" << endl;
  cout << gulosoRandomizado->subconjuntoIndependenteMaximo(grafo, 0.05, 1000).size() << endl;

  cout << "Guloso randomizado subconjunto independente máximo (alpha = 0.06, n = 1000):" << endl;
  cout << gulosoRandomizado->subconjuntoIndependenteMaximo(grafo, 0.06, 1000).size() << endl;
}
