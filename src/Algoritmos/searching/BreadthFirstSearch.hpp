#ifndef BREADTHFIRSTSEARCH_H_INCLUDED
#define BREADTHFIRSTSEARCH_H_INCLUDED

#include "../../Node.hpp"
#include <queue>
#include <list>

class BreadthFirstSearch
{
public:
  BreadthFirstSearch() {};
  ~BreadthFirstSearch() {};

  void printPath(Node *start, Node *end)
  {
    auto path = getPath(start, end);

    std::cout << "BFS - Solução: ";
    for (auto i = path.rbegin(); i != path.rend(); i++)
    {
      Node *node = *i;
      std::cout << node->id << " ";
    }
    printf("\n");
  }

private:
  std::list<Node *> getPath(Node *start, Node *end)
  {
    std::queue<Node *> unvisited;
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
        node = unvisited.front();

        if (node == end)
        {
          success = true;
        }
        else
        {
          unvisited.pop();

          for (auto i = node->adjacentes.begin(); i != node->adjacentes.end(); i++)
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

#endif // BREADTHFIRSTSEARCH_H_INCLUDED
