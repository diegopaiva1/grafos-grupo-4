#include "./Menu.h"

void Menu::exibir()
{
  std::cout << "================ MENU ================\n" << std::endl;
  std::cout << "A - Incluir nó" << std::endl;
  std::cout << "B - Incluir aresta" << std::endl;
  std::cout << "C - Obter grau de um nó" << std::endl;
  std::cout << "D - Verificar k-regularidade do grafo" << std::endl;
  std::cout << "E - Obter ordem do grafo" << std::endl;
  std::cout << "F - Grafo é trivial?" << std::endl;
  std::cout << "G - Grafo é nulo?" << std::endl;
  std::cout << "H - Obter vizinhança aberta de um nó" << std::endl;
  std::cout << "I - Obter vizinhança fechada de um nó" << std::endl;
  std::cout << "J - É multigrafo?" << std::endl;
  std::cout << "K - É completo?" << std::endl;
  std::cout << "L - É bipartido?" << std::endl;
  std::cout << "M - Apresentar sequência de graus" << std::endl;
  std::cout << "N - Obter quantidade de componentes conexas" << std::endl;
  std::cout << "O - É multigrafo?" << std::endl;
  std::cout << "P - É digrafo?" << std::endl;
  std::cout << "Q - Possui aresta múltipla?" << std::endl;
  std::cout << "R - É grafo geral?" << std::endl;
  std::cout << "S - Possui self-loop?" << std::endl;
}

bool Menu::possuiOpcao(char opcao)
{
  if(opcao < 'A' || opcao > 'S')
  {
    return false;
  }
  return true;
}

void Menu::acionarAcao(Grafo& grafo, char opcao)
{
  switch(opcao)
  {
    case 'A':
    break;
    case 'B':
    break;
    case 'C':
    {
      int id;
      std::cout << "Digite o id do nó: ";
      std::cin >> id;
      GrafoUtils::imprimirGrau(grafo, id);
    }
      break;
    case 'D':
      int k;
      std::cout << "Digite o valor de k: ";
      std::cin >> k;
      GrafoUtils::ehKRegular(grafo, k) ? std::cout << "Sim" << std::endl : std::cout << "Não" << std::endl;
      break;
    case 'E':
      std::cout << "Ordem do grafo: " << grafo.ordem << std::endl;
      break;
    case 'F':
      GrafoUtils::ehTrivial(grafo) ? std::cout << "Sim" << std::endl : std::cout << "Não" << std::endl;
      break;
    case 'G':
      GrafoUtils::ehNulo(grafo) ? std::cout << "Sim" << std::endl : std::cout << "Não" << std::endl;
      break;
    case 'H':
    {
      int id;
      std::cout << "Digite o id do nó: ";
      std::cin >> id;
      GrafoUtils::imprimirVizinhancaAberta(grafo, id);
      break;
    }
    case 'I':
    {
      int id;
      std::cout << "Digite o id do nó: ";
      std::cin >> id;
      GrafoUtils::imprimirVizinhancaFechada(grafo, id);
      break;
    }
    case 'J':
      GrafoUtils::ehMultigrafo(grafo) ? std::cout << "Sim" << std::endl : std::cout << "Não" << std::endl;
      break;
    case 'K':
      GrafoUtils::ehCompleto(grafo) ? std::cout << "Sim" << std::endl : std::cout << "Não" << std::endl;
      break;
    case 'L':
      GrafoUtils::ehBipartido(grafo) ? std::cout << "Sim" << std::endl : std::cout << "Não" << std::endl;
      break;
    case 'M':
      GrafoUtils::imprimirSequenciaGrau(grafo);
      break;
    case 'N':
      std::cout << "Quantidade de componentes conexas: " <<
              GrafoUtils::obterQuantidadeComponentesConexas(grafo) << std::endl;
      break;
    case 'O':
      GrafoUtils::ehMultigrafo(grafo) ? std::cout << "Sim" << std::endl : std::cout << "Não" << std::endl;
      break;
    case 'P':
      GrafoUtils::ehDigrafo(grafo) ? std::cout << "Sim" << std::endl : std::cout << "Não" << std::endl;
      break;
    case 'Q':
      GrafoUtils::possuiArcoMultiplo(grafo) ? std::cout << "Sim" << std::endl : std::cout << "Não" << std::endl;
      break;
    case 'R':
      GrafoUtils::ehGrafoGeral(grafo) ? std::cout << "Sim" << std::endl : std::cout << "Não" << std::endl;
      break;
    case 'S':
      GrafoUtils::possuiSelfLoop(grafo) ? std::cout << "Sim" << std::endl : std::cout << "Não" << std::endl;
      break;
  }
}
