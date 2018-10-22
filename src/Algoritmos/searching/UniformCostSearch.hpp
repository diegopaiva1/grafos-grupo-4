/**
 * @file    UniformCostSearch.hpp
 * @author  Diego Paiva e Silva
 * @date    16/10/2018
 *
 * O algoritmo Busca Ordenada é um algoritmo de busca que fornece, caso exista, o caminho ótimo
 * (menor custo) entre dois nós de entrada. Utiliza uma fila de prioridade para ir determinando
 * ao decorrer do processo qual o nó escolhido para expansão.
 */

#ifndef UNIFORMCOSTSEARCH_H_INCLUDED
#define UNIFORMCOSTSEARCH_H_INCLUDED

#include "../../Graph.hpp"
#include <queue>

/* Estrutura que permite com que a fila de prioridades armazene
 * os nós com seus respectivos custos acumulados
 */
struct NodeCost
{
  Node *node;
  double cost;
};

/* Estrutura utilizada como terceiro parâmetro em std::priority_queue para que possamos
 * construir uma fila de prioridade na qual o elemento mais prioritário é o de menor
 * custo (como uma min-heap)
 */
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

  double cost;

  void printPath(Graph *graph, int start, int end)
  {
    auto path = getPath(graph, graph->getNode(start), graph->getNode(end));

    std::cout << "Busca Ordenada - Solução: ";
    for (auto i = path.rbegin(); i != path.rend(); i++)
    {
      Node *node = *i;
      std::cout << node->id << " ";
    }
    std::cout << "(Custo = " << this->cost << ")";
    printf("\n");
  }

private:
  std::list<Node *> getPath(Graph *graph, Node *start, Node *end)
  {
    for (auto node : graph->nodes)
    {
      node->father = nullptr;
    }

    std::priority_queue<NodeCost, std::vector<NodeCost>, LessThanByCost> frontier;
    bool failure = false;
    bool success = false;
    std::list<NodeCost> explored;
    std::list<Node *> path;

    // Ponto de partida: origem com custo 0
    struct NodeCost nodeCost = {start, 0};

    frontier.push(nodeCost);
    explored.push_back(nodeCost);

    while (!failure && !success)
    {
      if (frontier.empty())
      {
        failure = true;
      }
      else
      {
        nodeCost = frontier.top();

        if (nodeCost.node == end)
        {
          success = true;
        }
        else
        {
          frontier.pop();

          for (auto arc : graph->getNodeArcs(nodeCost.node->id))
          {
            auto adjacent = arc->node2;
            struct NodeCost adjacentNodeCost = {adjacent, nodeCost.cost + arc->weight};

            if (!hasBeenExplored(adjacent, explored))
            {
              frontier.push(adjacentNodeCost);
              explored.push_back(adjacentNodeCost);
              adjacent->father = nodeCost.node;
            }
            else if (hasBeenExploredWithHigherCost(adjacentNodeCost, explored))
            {
              frontier.push(adjacentNodeCost);
              swapHighestCostWithLowerCost(adjacentNodeCost, explored);
              adjacent->father = nodeCost.node;
            }
          }
        }
      }
    }

    if (failure)
    {
      throw "Não há solução possível entre os dois nós fornecidos.";
    }

    // A partir do nó final conseguimos ir acessando os pais até o ponto de partida
    for (auto node = end; node != nullptr; node = node->father)
    {
      path.push_back(node);
    }

    this->cost = nodeCost.cost;

    return path;
  }

  bool hasBeenExplored(Node *node, std::list<NodeCost> explored)
  {
    for (auto nodeCost : explored)
    {
      if (nodeCost.node == node)
      {
        return true;
      }
    }

    return false;
  }

  bool hasBeenExploredWithHigherCost(struct NodeCost nodeCost, std::list<NodeCost> explored)
  {
    for (auto nc : explored)
    {
      if (nc.node == nodeCost.node && nc.cost > nodeCost.cost)
      {
        return true;
      }
    }

    return false;
  }

  void swapHighestCostWithLowerCost(struct NodeCost lowerNodeCost, std::list<NodeCost> &explored)
  {
    for (auto nodeCost = explored.begin(); nodeCost != explored.end(); nodeCost++)
    {
      struct NodeCost nc = *nodeCost;

      if (nc.node == lowerNodeCost.node && nc.cost > lowerNodeCost.cost)
      {
        *nodeCost = lowerNodeCost;
        return;
      }
    }
  }
};

#endif // UNIFORMCOSTSEARCH_H_INCLUDED
