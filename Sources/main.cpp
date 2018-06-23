#include "../Headers/Grafo.h"
#include "../Headers/LeitorArquivoGrafo.h"

using namespace std;

int main()
{
  Grafo *grafo = new Grafo();

  LeitorArquivoGrafo::atribuirDados("grafo.txt", *grafo);

  cout << "Ordem do grafo: " << grafo->ordem << endl;
  cout << endl;
  GrafoUtils::imprimirSequenciaGrau(*grafo);
  GrafoUtils::imprimirAdjacencias(*grafo);
  GrafoUtils::imprimirArcos(*grafo);
  GrafoUtils::imprimirVizinhancaAberta(*grafo, 1);
  GrafoUtils::imprimirVizinhancaFechada(*grafo, 1);
  GrafoUtils::imprimirGrau(*grafo, 1);
  GrafoUtils::ehNulo(*grafo) ? std::cout << "É nulo" << std::endl
                             : std::cout << "Não é nulo" << std::endl;
  GrafoUtils::ehTrivial(*grafo) ? std::cout << "É trivial" << std::endl
                                : std::cout << "Não é trivial" << std::endl;
  GrafoUtils::possuiSelfLoop(*grafo) ? std::cout << "Possui self-loop" << std::endl
                                     : std::cout << "Não possui self-loop" << std::endl;
  GrafoUtils::possuiArcoMultiplo(*grafo) ? std::cout << "Possui arco múltiplo" << std::endl
                                           : std::cout << "Não possui arco múltiplo" << std::endl;
  GrafoUtils::ehCompleto(*grafo) ? std::cout << "É completo" << std::endl
                                 : std::cout << "Não é completo" << std::endl;
  GrafoUtils::ehMultigrafo(*grafo) ? std::cout << "É multigrafo" << std::endl
                                   : std::cout << "Não é multigrafo" << std::endl;
  GrafoUtils::ehGrafoGeral(*grafo) ? std::cout << "É grafo geral" << std::endl
                                   : std::cout << "Não é grafo geral" << std::endl;
  GrafoUtils::ehBipartido(*grafo) ? std::cout << "É bipartido" << std::endl
                                  : std::cout << "Não é bipartido" << std::endl;
  GrafoUtils::ehKRegular(*grafo, 1) ? std::cout << "É 1-regular" << std::endl
                                    : std::cout << "Não é 1-regular" << std::endl;
  GrafoUtils::ehDigrafo(*grafo) ? std::cout << "É digrafo" << std::endl
                                : std::cout << "Não é digrafo" << std::endl;
}
