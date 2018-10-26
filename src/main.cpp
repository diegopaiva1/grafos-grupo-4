#include <fstream>
#include "Algoritmos/searching/AStar.hpp"
#include "Algoritmos/searching/Backtracking.hpp"
#include "Algoritmos/searching/DepthFirstSearch.hpp"
#include "Algoritmos/searching/BreadthFirstSearch.hpp"
#include "Algoritmos/searching/UniformCostSearch.hpp"
#include "Algoritmos/searching/GreedySearch.hpp"

void createGraphFromFile(std::string file, Graph &graph)
{
  int nodesAmount;
  int arcsAmount;
  int heuristicsAmount;
  std::string id1;
  std::string id2;
  std::string weight;
  std::string heuristic;
  std::ifstream f(file);
  std::streampos old;

  if (!f.is_open())
  {
    std::cout << "Erro na leitura do arquivo" << std::endl;
    exit(0);
  }
  else
  {
    // Eis a primeira linha
    f >> nodesAmount;
    f >> arcsAmount;
    f >> heuristicsAmount;
    graph.order = nodesAmount;
    graph.nodes.resize(nodesAmount + 1);
    graph.arcs.resize(arcsAmount + 1);
    graph.heuristics.resize(heuristicsAmount + 1);

    // Dummy node pois os nós começam a partir de 1
    graph.addNode(0);

    // Demais linhas
    while (f >> id1 >> id2 >> weight && id1 != "h")
    {
      if (!graph.hasNode(atoi(id1.c_str())))
      {
        graph.addNode(atoi(id1.c_str()));
        graph.heuristics.at(atoi(id1.c_str())).resize(heuristicsAmount + 1);
      }

      if (!graph.hasNode(atoi(id2.c_str())))
      {
        graph.addNode(atoi(id2.c_str()));
        graph.heuristics.at(atoi(id2.c_str())).resize(heuristicsAmount + 1);
      }

      graph.arcs.at(atoi(id1.c_str())).resize(nodesAmount + 1);
      graph.addArc(atoi(id1.c_str()), atoi(id2.c_str()), atof(weight.c_str()));

      // Salva posição da última linha lida
      old = f.tellg();
    }

    // Retoma na linha que encontrou "h"
    f.seekg(old);

    // Descarta o "h"
    f >> id1;

    while (f >> id1 >> id2 >> heuristic)
    {
      graph.addHeuristic(atoi(id1.c_str()), atoi(id2.c_str()), atof(heuristic.c_str()));
    }
  }
}

int main(int argc, char* argv[])
{
  std::string file = argv[1];
  int start = atoi(argv[2]);
  int end = atoi(argv[3]);

  Graph *graph = new Graph();

  createGraphFromFile(file, *graph);

  Backtracking backtracking;
  DepthFirstSearch dfs;
  BreadthFirstSearch bfs;
  UniformCostSearch ucs;
  GreedySearch gs;
  AStar as;

  try
  {
    std::cout << "Backtracking - Solução: ";
    backtracking.printPath(graph, start, end);
    std::cout << "BFS - Solução: ";
    bfs.printPath(graph, start, end);
    std::cout << "DFS - Solução: ";
    dfs.printPath(graph, start, end);
    std::cout << "Ordenada - Solução: ";
    ucs.printPath(graph, start, end);
    std::cout << "Gulosa - Solução: ";
    gs.printPath(graph, start, end);
    std::cout << "A* - Solução: ";
    as.printPath(graph, start, end);
  }
  catch (char const* exception)
  {
    std::cerr << exception << std::endl;
  }

  return 0;
}
