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
  std::cout << "T - Obter soluções do subconjunto independente máximo (guloso)" << std::endl;
}

bool Menu::possuiOpcao(char opcao)
{
  if(opcao < 'A' || opcao > 'T')
  {
    return false;
  }
  return true;
}

void Menu::acionarAcao(Grafo& grafo, char opcao, std::string arquivoSaida)
{
  switch(opcao)
  {
    case 'A':
    {
      int id;
      std::cout << "Digite o id do nó: ";
      std::cin >> id;
      GrafoUtils::incluirNo(grafo, id);
    }
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
      GrafoUtils::ehKRegular(grafo, k) ? std::cout << "Sim" << std::endl : std::cout << "Não é " << k << "-regular" << std::endl;
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
    case 'T':
      // Abertura do arquivo de saída para escrita
      std::ofstream saidatxt;
      saidatxt.open(arquivoSaida, std::ifstream::out | std::ifstream::trunc);

      std::cout << "Processando..." << std::endl;
      // Instanciando os algoritmos
      Guloso *guloso = new Guloso();
      GulosoRandomizado *gulosoRandomizado = new GulosoRandomizado();
      GulosoRandomizadoReativo *gulosoRandomizadoReativo = new GulosoRandomizadoReativo();

      saidatxt << "Guloso - subconjunto independente máximo:" << std::endl;
      saidatxt << guloso->subconjuntoIndependenteMaximo(&grafo).size() << std::endl;

      // Rodando o guloso randomizado para 0.10 <= alfa <= 0.30
      for (float i = 0.10; i < 0.40; i += 0.10)
      {
        std::list<No *> solucao = gulosoRandomizado->subconjuntoIndependenteMaximo(&grafo, i, 1000);
        saidatxt << "Guloso randomizado subconjunto independente máximo (alpha = " << i << ", n = 1000):\n";
        saidatxt << solucao.size() << std::endl;
      }

      std::list<No *> solucao = gulosoRandomizadoReativo->subconjuntoIndependenteMaximo(&grafo, 100, 1000);
      saidatxt << "Guloso randomizado reativo (blocos = 100, n = 1000)\n";
      saidatxt << solucao.size() << std::endl;

      // Imprime ao final os dados escritos no arquivo de saida
      std::cout << std::ifstream(arquivoSaida).rdbuf() << '\n';
      break;
  }
}
