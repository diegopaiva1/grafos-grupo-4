#include "Graph.hpp"
#include "Algoritmos/searching/Backtracking.hpp"
#include "Algoritmos/searching/DepthFirstSearch.hpp"
#include "Algoritmos/searching/BreadthFirstSearch.hpp"
#include <fstream>

void read(std::string file, Graph &graph)
{
  int nodeAmount;
  int arcAmount;
  int id1;
  int id2;
  double weight;

  std::ifstream f(file);

  if (!f.is_open())
  {
    std::cout << "Erro na leitura do arquivo" << std::endl;
    exit(0);
  }
  else
  {
    // Eis a primeira linha
    f >> nodeAmount;
    f >> arcAmount;
    graph.order = nodeAmount;
    graph.nodes.resize(nodeAmount);
    graph.arcs.resize(arcAmount);

    // Demais linhas
    while (f >> id1 >> id2 >> weight)
    {
      if (!graph.hasNode(id1))
      {
        graph.addNode(id1);
      }

      if (!graph.hasNode(id2))
      {
        graph.addNode(id2);
      }

      graph.addArc(id1, id2, weight);
    }
  }
}

int main(int argc, char* argv[])
{
  std::string file = argv[1];
  int start = atoi(argv[2]);
  int end = atoi(argv[3]);

  Graph *graph = new Graph();

  read(file, *graph);

  Backtracking backtracking;
  DepthFirstSearch dfs;
  BreadthFirstSearch bfs;

  try
  {
    backtracking.printPath(graph, start, end);
    bfs.printPath(graph, start, end);
    dfs.printPath(graph, start, end);
  }
  catch (char const* exception)
  {
    std::cerr << exception << std::endl;
  }

  return 0;
}
