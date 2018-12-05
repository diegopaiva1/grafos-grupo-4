/**
 * @file    AStar.hpp
 * @author  Diego Paiva e Silva
 * @date    26/10/2018
 *
 */

#ifndef ASTAR_H_INCLUDED
#define ASTAR_H_INCLUDED

#include "Search.hpp"
#include <queue>

class AStar : public Search
{
public:
  AStar() {};
  ~AStar() {};

private:
  std::list<Node *> getPath(Graph *graph, Node *start, Node *end)
  {
    depth = 0;
    cost = 0.0;

    for (auto node : graph->nodes)
      node->father = nullptr;

    std::priority_queue<NodeCost, std::vector<NodeCost>, LessThanByCost> frontier;
    bool failure = false;
    bool success = false;
    std::list<NodeCost> explored;
    std::list<Node *> path;

    struct NodeCost nodeCost = {start, graph->getHeuristicValue(start, end), 0};

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

          for (auto adjacent : nodeCost.node->adjacents)
          {
            struct NodeCost adjacentNodeCost = {
              adjacent,
              nodeCost.costWithoutHeuristic + graph->getArcWeight(adjacent, nodeCost.node)
                                            + graph->getHeuristicValue(adjacent, end),
              nodeCost.costWithoutHeuristic + graph->getArcWeight(adjacent, nodeCost.node)
            };

            if (!hasBeenExplored(adjacent, explored))
            {
              depth++;
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

  bool hasBeenExplored(Node *node, std::list<NodeCost> explored)
  {
    for (auto nodeCost : explored)
    {
      if (nodeCost.node == node)
        return true;
    }

    return false;
  }

  bool hasBeenExploredWithHigherCost(struct NodeCost nodeCost, std::list<NodeCost> explored)
  {
    for (auto nc : explored)
    {
      if (nc.node == nodeCost.node && nc.cost > nodeCost.cost)
        return true;
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

#endif // ASTAR_H_INCLUDED
