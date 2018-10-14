#ifndef DEPTHFIRSTSEARCH_H_INCLUDED
#define DEPTHFIRSTSEARCH_H_INCLUDED

#include "../../Node.hpp"
#include <stack>
#include <vector>
#include <list>

class DepthFirstSearch
{
public:
  DepthFirstSearch() {};
  ~DepthFirstSearch() {};

  void printPath(Node *start, Node *end)
  {
    auto path = getPath(start, end);

    std::cout << "DFS - Solução: ";
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
    std::stack<Node *> unvisited;
    std::vector<Node *> visited;
    Node *node = start;
    bool failure = false;
    bool success = false;

    unvisited.push(node);

    // Nó para representar o pai do nó atual. Consideramos que o pai da raíz tem índice default -1
    Node *father = new Node(-1);
    node->father = father;

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
          visited.push_back(node);
          node->visited = true;
          success = true;
        }
        else
        {
          visited.push_back(node);
          node->visited = true;
          unvisited.pop();

          for (auto i = node->adjacentes.begin(); i != node->adjacentes.end(); i++)
          {
            Node *adjacent = *i;
            if (!adjacent->visited)
            {
              unvisited.push(adjacent);
              adjacent->father = node;
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
