#include "../Headers/GraphFileReader.h"

void GraphFileReader::read(std::string file,
                           int &ordem,
                           std::list<Aresta *> &arestas,
                           std::list<std::list<No *>> &adjacencias)
{
  int id1, id2;
  double pesoAresta;
  std::ifstream arquivo(file);

  if (!arquivo.is_open())
  {
    std::cout << "Erro na leitura do arquivo" << std::endl;
    exit(0);
  }
  else
  {

    // Eis a primeira linha
    arquivo >> ordem;

    std::list<No *> adjacentes[ordem];

    // Array auxiliar
    No *nosLidos[ordem];

    // Inicialização do array com ponteiros nulos
    std::fill(nosLidos, nosLidos + ordem, nullptr);

    // Demais linhas
    while (arquivo >> id1 >> id2 >> pesoAresta)
    {

      if (!noJaFoiLido(nosLidos, id1))
      {
        nosLidos[id1 - 1] = new No(id1);
      }

      if (!noJaFoiLido(nosLidos, id2))
      {
        nosLidos[id2 - 1] = new No(id2);
      }

      if (!listaContemNo(adjacentes[id1 - 1], nosLidos[id1 - 1]))
      {
        adjacentes[id1 - 1].push_back(nosLidos[id1 - 1]);
      }

      if (!listaContemNo(adjacentes[id1 - 1], nosLidos[id2 - 1]))
      {
        adjacentes[id1 - 1].push_back(nosLidos[id2 - 1]);
      }

      Aresta *aresta = new Aresta(nosLidos[id1 - 1], nosLidos[id2 - 1], pesoAresta);
      arestas.push_back(aresta);
    }

    preencherListasVazias(adjacentes, ordem);
    popularAdjacencias(adjacencias, adjacentes, ordem);
  }
}

bool GraphFileReader::noJaFoiLido(No *nosLidos[], int id)
{
  return nosLidos[id - 1] != nullptr ? true : false;
}

bool GraphFileReader::listaContemNo(std::list<No *> lista, No *no)
{
  if (no != NULL)
  {
    std::list<No *>::iterator i;
    for (i = lista.begin(); i != lista.end(); i++)
    {
      No *noLista = *i;
      if (noLista->getId() == no->getId())
      {
        return true;
      }
    }
  }
  return false;
}

void GraphFileReader::preencherListasVazias(std::list<No *> *adjacentes, int ordem)
{
  for (int i = 0; i < ordem; i++)
  {
    if (adjacentes[i].empty())
    {
      No *no = new No(i + 1);
      adjacentes[i].push_back(no);
    }
  }
}

void GraphFileReader::popularAdjacencias(std::list<std::list<No *>> &adjacencias,
                                         std::list<No *> *adjacentes,
                                         int ordem)
{
  for (int i = 0; i < ordem; i++)
  {
    adjacencias.push_back(adjacentes[i]);
  }
}

void GraphFileReader::write(std::string file, int data, int posicaoEscrita)
{
  std::fstream arquivo(file, std::ios::in | std::ios::out);
  arquivo.seekp(posicaoEscrita);
  arquivo << data;
}
