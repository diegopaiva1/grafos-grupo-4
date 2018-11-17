#include "Algoritmos/searching/AStar.hpp"
#include "Algoritmos/searching/Backtracking.hpp"
#include "Algoritmos/searching/DepthFirstSearch.hpp"
#include "Algoritmos/searching/BreadthFirstSearch.hpp"
#include "Algoritmos/searching/UniformCostSearch.hpp"
#include "Algoritmos/searching/GreedySearch.hpp"

#define EXPECTED_ARGUMENTS_AMOUNT 4

int main(int argc, char* argv[])
{
  if (argc != EXPECTED_ARGUMENTS_AMOUNT)
  {
    std::cout << "Número de argumentos inesperado! Saindo" << '\n';
    exit(1);
  }

  std::string instanceFile = argv[1];

  int start = atoi(argv[2]);
  int end = atoi(argv[3]);

  Graph *graph = new Graph(instanceFile);

  Backtracking backtracking;
  DepthFirstSearch depthFirstSearch;
  BreadthFirstSearch breadthFirstSearch;
  UniformCostSearch uniformCostSearch;
  GreedySearch greedySearch;
  AStar aStar;

  try
  {
    std::cout << "Backtracking - Solução: ";
    backtracking.printPath(graph, start, end);

    std::cout << "BFS - Solução: ";
    breadthFirstSearch.printPath(graph, start, end);

    std::cout << "DFS - Solução: ";
    depthFirstSearch.printPath(graph, start, end);

    std::cout << "Ordenada - Solução: ";
    uniformCostSearch.printPath(graph, start, end);

    std::cout << "Gulosa - Solução: ";
    greedySearch.printPath(graph, start, end);

    std::cout << "A* - Solução: ";
    aStar.printPath(graph, start, end);
  }
  catch (char const* exception)
  {
    std::cerr << exception << std::endl;
  }

  return 0;
}
