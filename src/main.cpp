#include "Node.hpp"
#include "Algoritmos/searching/Backtracking.hpp"
#include "Algoritmos/searching/DepthFirstSearch.hpp"
#include "Algoritmos/searching/BreadthFirstSearch.hpp"
#include <fstream>

void read(std::string arquivo, std::vector<Node *> &nos)
{
  int id1;
  int id2;
  int size;

  std::ifstream arq(arquivo);

  if (!arq.is_open())
  {
    std::cout << "Erro na leitura do arquivo" << std::endl;
    exit(0);
  }
  else
  {
    // Eis a primeira linha
    arq >> size;
    nos.resize(size + 1);

    // Demais linhas
    while (arq >> id1 >> id2)
    {
      if (nos.at(id1) == NULL)
      {
        nos.at(id1) = new Node(id1);
      }

      if (nos.at(id2) == NULL)
      {
        nos.at(id2) = new Node(id2);
      }

      nos.at(id1)->adjacentes.push_back(nos.at(id2));
    }
  }
}

int main(int argc, char* argv[])
{
  std::string file = argv[1];
  int start = atoi(argv[2]);
  int end = atoi(argv[3]);

  std::vector<Node *> nos;

  read(file, nos);

  Backtracking *backtracking = new Backtracking();
  DepthFirstSearch *dfs = new DepthFirstSearch();
  BreadthFirstSearch *bfs = new BreadthFirstSearch();

  try
  {
    backtracking->printPath(nos.at(start), nos.at(end));
    bfs->printPath(nos.at(start), nos.at(end));
    //dfs->printPath(nos.at(start), nos.at(end));
  }
  catch (char const* exception)
  {
    std::cerr << exception << std::endl;
  }

  return 0;
}
