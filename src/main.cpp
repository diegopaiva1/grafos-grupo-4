#include "./Utils/Grafo/GrafoUtils.h"
#include "./Componentes/Grafo/Grafo.h"
#include "./Componentes/Arquivo/Leitor/LeitorArquivoGrafo.h"
#include "./Algoritmos/Guloso/Guloso.h"
#include "./Algoritmos/GulosoRandomizado/GulosoRandomizado.h"
#include "./Algoritmos/GulosoRandomizadoReativo/GulosoRandomizadoReativo.h"
#include "./Componentes/Menu/Menu.h"

using namespace std;

int main()
{
  // Initialize random seed
  srand(time(NULL));

  Menu *menu = new Menu();
  Grafo *grafo = new Grafo();
  char opcao;

  LeitorArquivoGrafo::atribuirDados("Instancias/450/frb30-15-mis/frb30-15-1.mis", *grafo);

  menu->exibir();

  cout << "\nEscolha uma opção: ";
  cin >> opcao;

  while(!menu->possuiOpcao(opcao))
  {
    cout << "Opção inválida! Escolha uma opção válida: ";
    cin >> opcao;
  }

  menu->acionarAcao(*grafo, opcao);

  // // Instanciando os algoritmos
  // Guloso *guloso = new Guloso();
  // GulosoRandomizado *gulosoRandomizado = new GulosoRandomizado();
  // GulosoRandomizadoReativo *gulosoRandomizadoReativo = new GulosoRandomizadoReativo();

  // cout << "Guloso - subconjunto independente máximo:" << endl;
  // cout << guloso->subconjuntoIndependenteMaximo(grafo).size() << endl;

  // for (float i = 0.10; i < 0.40; i += 0.10)
  // {
  //   list<No *> solucao = gulosoRandomizado->subconjuntoIndependenteMaximo(grafo, i, 1000);
  //   cout << "Guloso randomizado subconjunto independente máximo (alpha = " << i << ", n = 1000):\n";
  //   cout << solucao.size() << endl;
  // }

  // std::list<No *> solucao = gulosoRandomizadoReativo->subconjuntoIndependenteMaximo(grafo, 100, 1000);
  // cout << "Guloso randomizado reativo (blocos = 100, n = 1000)\n";
  // cout << solucao.size() << endl;
}
