#ifndef DEPTHFIRSTSEARCH_H_INCLUDED
#define DEPTHFIRSTSEARCH_H_INCLUDED

#include "../../Graph.hpp"
#include <stack>
#include <list>

class DepthFirstSearch
{
public:
  DepthFirstSearch() {};
  ~DepthFirstSearch() {};

  void printPath(Graph *graph, int start, int end)
  {
    auto path = getPath(graph, graph->getNode(start), graph->getNode(end));

    std::cout << "DFS - Solução: ";
    for (auto i = path.rbegin(); i != path.rend(); i++)
    {
      Node *node = *i;
      std::cout << node->id << " ";
    }
    printf("\n");
  }

private:
  std::list<Node *> getPath(Graph *graph, Node *start, Node *end)
  {
    for (auto node : graph->nodes)
    {
      node->visited = false;
    }

    std::stack<Node *> unvisited;
    Node *node = start;
    bool failure = false;
    bool success = false;

    // Nó para representar o pai do nó atual. Consideramos que o pai da raíz tem índice default -1
    Node *father = new Node(-1);
    node->father = father;
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
        node = unvisited.top();

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
    while (pathComponent->id != -1)
    {
      path.push_back(pathComponent);
      pathComponent = pathComponent->father;
    }

    return path;
  }
};

#endif // DEPTHFIRSTSEARCH_H_INCLUDED
