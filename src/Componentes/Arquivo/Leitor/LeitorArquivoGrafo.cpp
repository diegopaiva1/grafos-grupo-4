#include "./LeitorArquivoGrafo.h"

void LeitorArquivoGrafo::atribuirDados(std::string arquivo, Grafo& grafo)
{
  int id1;
  int id2;
  double pesoArco;
  std::ifstream arq(arquivo);

  if (!arq.is_open())
  {
    std::cout << "Erro na leitura do arquivo" << std::endl;
    exit(0);
  }
  else
  {
    // Eis a primeira linha
    arq >> grafo.ordem;

    // Demais linhas
    while (arq >> id1 >> id2 >> pesoArco)
    {
      if (!GrafoUtils::possuiNo(grafo, id1))
      {
        No *no1 = new No(id1);
        grafo.nos.push_back(no1);
      }

      if (!GrafoUtils::possuiNo(grafo, id2))
      {
        No *no2 = new No(id2);
        grafo.nos.push_back(no2);
      }

      No *no1 = GrafoUtils::getNo(grafo, id1);
      No *no2 = GrafoUtils::getNo(grafo, id2);

      no1->grauSaida++;
      no2->grauEntrada++;

      Arco *arco = new Arco(no1, no2, pesoArco);
      grafo.arcos.push_back(arco);
    }
    setSequenciaGrau(grafo);
  }
}

void LeitorArquivoGrafo::setSequenciaGrau(Grafo& grafo)
{
  for (auto i = grafo.nos.begin(); i != grafo.nos.end(); i++)
  {
    No *no = *i;
    grafo.sequenciaGrau.push_back(no->grauSaida);
  }
  grafo.sequenciaGrau.sort();
  grafo.sequenciaGrau.reverse();
}
