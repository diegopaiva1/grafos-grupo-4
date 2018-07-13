#include "./Componentes/Grafo/Grafo.h"
#include "./Componentes/Arquivo/Leitor/LeitorArquivoGrafo.h"
#include "./Componentes/Menu/Menu.h"

using namespace std;

int main(int argc, char* argv[])
{
  // Initialize random seed
  srand(time(NULL));

  // Arquivos passados por linha de comando
  string arquivoEntrada = argv[1];
  string arquivoSaida = argv[2];

  Menu *menu = new Menu();
  Grafo *grafo = new Grafo();
  char opcao;

  LeitorArquivoGrafo::atribuirDados(arquivoEntrada, *grafo);

  menu->exibir();

  cout << "\nEscolha uma opção: ";
  cin >> opcao;

  while(!menu->possuiOpcao(opcao))
  {
    cout << "Opção inválida! Escolha uma opção válida: ";
    cin >> opcao;
  }

  menu->acionarAcao(*grafo, opcao, arquivoSaida);

  return 0;
}
