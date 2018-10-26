#ifndef BREADTHFIRSTSEARCH_H_INCLUDED
#define BREADTHFIRSTSEARCH_H_INCLUDED

#include "Search.hpp"
#include <queue>

class BreadthFirstSearch : public Search
{
public:
  BreadthFirstSearch() {};
  ~BreadthFirstSearch() {};

private:
  std::list<Node *> getPath(Graph *graph, Node *start, Node *end)
  {
    for (auto node : graph->nodes)
    {
      node->visited = false;
      node->father = nullptr;
    }

    std::queue<Node *> unvisited;
    bool failure = false;
    bool success = false;
    Node *node = start;
    node->visited = true;

    unvisited.push(node);

    while (!failure && !success)
    {
      if (unvisited.empty())
      {
        failure = true;
      }
      else
      {
        node = unvisited.front();

        if (node == end)
        {
          success = true;
        }
        else
        {
          unvisited.pop();

          for (auto i = node->adjacents.begin(); i != node->adjacents.end(); i++)
          {
            Node *adjacent = *i;
            if (!adjacent->visited)
            {
              unvisited.push(adjacent);
              adjacent->father = node;
              adjacent->visited = true;
            }
          }
        }
      }
    }

    if (failure)
    {
      throw "Não há solução possível entre os dois nós fornecidos.";
    }

    // Criando a lista com a solução final para retornar ao fim do processo
    std::list<Node *> path;

    // A partir do nó final conseguimos ir acessando os pais até o ponto de partida
    Node *pathComponent = end;
    while (pathComponent != nullptr)
    {
      path.push_back(pathComponent);
      pathComponent = pathComponent->father;
    }

    return path;
  }
};

#endif // BREADTHFIRSTSEARCH_H_INCLUDED
