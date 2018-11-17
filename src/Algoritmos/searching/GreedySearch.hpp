/**
 * @file    GreedySearch.hpp
 * @author  Diego Paiva e Silva
 * @date    24/10/2018
 */

#ifndef GREEDY_H_INCLUDED
#define GREEDY_H_INCLUDED

#include "Search.hpp"

class GreedySearch : public Search
{
public:
  GreedySearch() {};
  ~GreedySearch() {};

private:
  std::list<Node *> getPath(Graph *graph, Node *start, Node *end)
  {
    cost = 0.0;

    for (auto node : graph->nodes)
      node->father = nullptr;

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

          for (auto adjacent : nodeCost.node->adjacents)
          {
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
      throw "Não há solução possível entre os dois nós fornecidos.";

    // A partir do nó final conseguimos ir acessando os pais até o ponto de partida
    for (auto node = end; node != nullptr; node = node->father)
    {
      path.push_back(node);

      if (node->father != nullptr)
        this->cost += graph->getArcWeight(node->father, node);
    }

    return path;
  }

  bool hasBeenExplored(Node *n, std::list<Node *> explored)
  {
    for (auto node : explored)
    {
      if (node == n)
        return true;
    }

    return false;
  }
};

#endif // GREEDY_H_INCLUDED
