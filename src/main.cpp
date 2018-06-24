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

  for (float i = 0.01; i <= 0.07; i += 0.01)
  {
    cout <<
    "Guloso randomizado subconjunto independente máximo (alpha = " << i << ", n = 1000):"
    << endl;
    cout << gulosoRandomizado->subconjuntoIndependenteMaximo(grafo, i, 1000).size() << endl;
  }
}
