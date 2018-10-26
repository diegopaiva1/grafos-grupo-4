/**
 * @file    GreedySearch.hpp
 * @author  Diego Paiva e Silva
 * @date    24/10/2018
 */

#ifndef GREEDY_H_INCLUDED
#define GREEDY_H_INCLUDED

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

class GreedySearch
{
public:
  GreedySearch() {};
  ~GreedySearch() {};

  double cost = 0.0;

  void printPath(Graph *graph, int start, int end)
  {
    auto path = getPath(graph, graph->getNode(start), graph->getNode(end));

    std::cout << "Busca Gulosa - Solução: ";
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
    std::list<Node *> explored;
    std::list<Node *> path;

    // Ponto de partida: origem com custo da heurística do nó inicial ao final
    struct NodeCost nodeCost = {start, graph->getHeuristicValue(start, end)};

    frontier.push(nodeCost);
    explored.push_back(start);

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
            struct NodeCost adjacentNodeCost = {adjacent, graph->getHeuristicValue(adjacent, end)};

            if (!hasBeenExplored(adjacent, explored))
            {
              frontier.push(adjacentNodeCost);
              explored.push_back(adjacent);
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
      this->cost += graph->getHeuristicValue(node, end);
    }

    return path;
  }

  bool hasBeenExplored(Node *n, std::list<Node *> explored)
  {
    for (auto node : explored)
    {
      if (node == n)
      {
        return true;
      }
    }

    return false;
  }
};

#endif // GREEDY_H_INCLUDED
