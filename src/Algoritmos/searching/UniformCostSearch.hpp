/**
 * @file    UniformCostSearch.hpp
 * @author  Diego Paiva e Silva
 * @date    16/10/2018
 *
 * O algoritmo Busca Ordenada é um algoritmo de busca que fornece, caso exista, o caminho ótimo
 * (menor custo) entre dois nós de entrada. Utiliza uma fila de prioridade para ir determinando,
 * ao decorrer do processo, qual o nó escolhido para integrar a solução.
 */

#ifndef UNIFORMCOSTSEARCH_H_INCLUDED
#define UNIFORMCOSTSEARCH_H_INCLUDED

#include "../../Graph.hpp"
#include <queue>
#include <list>

struct NodeCost
{
  Node *node;
  Node *father;
  double cost;
};

struct LessThanByCost
{
  bool operator()(const NodeCost& nodeCost1, const NodeCost& nodeCost2) const
  {
    return nodeCost1.cost > nodeCost2.cost;
  }
};

class UniformCostSearch
{
public:
  UniformCostSearch() {};
  ~UniformCostSearch() {};

  void printPath(Graph *graph, int start, int end)
  {
    auto path = getPath(graph, graph->getNode(start), graph->getNode(end));

    std::cout << "Busca Ordenada - Solução: ";
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
      node->father = nullptr;
    }

    std::priority_queue<NodeCost, std::vector<NodeCost>, LessThanByCost> unvisited;
    Node *node = start;
    bool failure = false;
    bool success = false;

    struct NodeCost nodeCost = {node, nullptr, 0};

    unvisited.push(nodeCost);

    while (!failure && !success)
    {
      if (unvisited.empty())
      {
        failure = true;
      }
      else
      {
        nodeCost = unvisited.top();
        std::cout << nodeCost.node->id << " " << nodeCost.cost << std::endl;

        if (nodeCost.node == end)
        {
          success = true;
        }
        else
        {
          unvisited.pop();

          for (auto arc : graph->arcs.at(nodeCost.node->id))
          {
            bool different = true;
            NodeCost p = nodeCost;
            while (p.node != nullptr)
            {
              if (arc->node2 == p.node)
              {
                different = false;
                break;
              }
              p.node = p.node->father;
            }
            if (different)
            {
              arc->node2->father = nodeCost.node;
              unvisited.push({arc->node2, nodeCost.node, nodeCost.cost + arc->weight});
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
    std::cout << "Custo da solução = " << nodeCost.father->id << std::endl;
    Node *node = nodeCost.node;
    while (node != nullptr)
    {
      path.push_back(node);
      node = nodeCost.father;
    }

    return path;
  }
};

#endif // UNIFORMCOSTSEARCH_H_INCLUDED
