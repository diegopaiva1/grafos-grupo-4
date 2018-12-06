/**
 * @file    IDAStar.hpp
 * @author  Diego Paiva e Silva
 * @date    01/12/2018
 */

#ifndef IDASTAR_H_INCLUDED
#define IDASTAR_H_INCLUDED

#include "Search.hpp"

class IDAStar : public Search
{
public:
  IDAStar() {};
  ~IDAStar() {};

private:
  std::list<Node *> getPath(Graph *graph, Node *start, Node *end)
  {
    cost = 0.0;

    bool failure = false;
    bool success = false;
    double bound = graph->getEuclidianDistance(start, end);
    double oldBound = -1;
    double estimate = 0.0;

    std::list<Node *> ancestors;
    ancestors.push_front(start);

    Node *node = start;
    Node *undesirable = nullptr;

    std::list<NodeCost> discarded;

    while (!failure && !success)
    {
      if (oldBound == bound)
      {
        failure = true;
      }
      else
      {
        if (node == end && f(graph, node, end, estimate) <= bound)
        {
          success = true;
        }
        else
        {
          if (f(graph, node, end, estimate) > bound)
          {
            discarded.push_back({node, f(graph, node, end, estimate)});

            undesirable = ancestors.front();
            ancestors.remove(undesirable);
            node = ancestors.front();
            estimate -= graph->getArcWeight(node, undesirable);
          }

          if (hasApplicableOperators(node, ancestors, discarded, undesirable))
          {
            estimate += graph->getArcWeight(node, getFirstNonAncestralAdjacent(node, ancestors, discarded, undesirable));
            node = getFirstNonAncestralAdjacent(node, ancestors, discarded, undesirable);
            ancestors.push_front(node);
            undesirable = nullptr;
          }
          else
          {
            if (node == start)
            {
              oldBound = bound;

              if (!discarded.empty())
                bound = discarded.front().cost;

              for (auto d : discarded)
                if (d.cost < bound)
                  bound = d.cost;

              discarded.clear();
              undesirable = nullptr;
            }
            else
            {
              undesirable = ancestors.front();
              ancestors.remove(undesirable);
              node = ancestors.front();
            }
          }
        }
      }
    }

    cost = estimate;

    if (failure)
      throw "Não há solução possível entre os dois nós fornecidos.";

    return ancestors;
  }

  double f(Graph *graph, Node *node, Node *end, double estimate)
  {
    return estimate + graph->getEuclidianDistance(node, end);
  }

 /* A estratégia para determinar se um nó tem operadores aplicáveis se baseia em verificar se os
  * seus adjacentes são ou não ancestrais
  */
  bool hasApplicableOperators(Node *node, std::list<Node *> ancestors, std::list<NodeCost> discarded, Node* undesirable)
  {
    int adjacentAncestors = 0;
    int discardedAdjacents = 0;

    for (Node* adjacent : node->adjacents)
    {
      for (Node* ancestral : ancestors)
        if (adjacent == ancestral && adjacent != undesirable)
          adjacentAncestors++;

      for (NodeCost d : discarded)
        if (adjacent == d.node)
          discardedAdjacents++;
    }

    /* Há operadores aplicáveis se pelo menos um dos nós adjacentes não é ancestral
     * e não está na lista de descartados
     */
    return (adjacentAncestors != node->adjacents.size() && discardedAdjacents != node->adjacents.size());
  }

  /* O terceiro parâmetro é passado para evitar a geração de um nó indesejável (útil no backtrack para
   * evitar que o nó gere um filho cujo retorno ao pai já foi realizado)
   */
  Node* getFirstNonAncestralAdjacent(Node *node, std::list<Node *> ancestors, std::list<NodeCost> discarded, Node *undesirable)
  {
    int nonAdjacentAncestors;
    int nonDiscardedAdjacents;

    for (Node* adjacent : node->adjacents)
    {
      nonAdjacentAncestors = 0;
      nonDiscardedAdjacents = 0;

      for (Node* ancestral : ancestors)
        if (adjacent != ancestral && adjacent != undesirable)
          nonAdjacentAncestors++;

      for (NodeCost d : discarded)
        if (adjacent != d.node && adjacent != undesirable)
          nonDiscardedAdjacents++;

      if (nonAdjacentAncestors == ancestors.size() && nonDiscardedAdjacents == discarded.size())
        return adjacent;
    }

    throw "Runtime error";
  }
};

#endif // IDASTAR_H_INCLUDED
