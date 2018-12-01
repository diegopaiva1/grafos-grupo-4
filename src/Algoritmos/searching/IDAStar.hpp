/**
 * @file    IDAStar.hpp
 * @author  Diego Paiva e Silva
 * @date    13/10/2018
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
    int bound = graph->getHeuristicValue(start, end);
    double estimate = 0;
    double c = 0;

    std::list<Node *> ancestors;
    ancestors.push_front(start);

    Node *node = start;
    Node *undesirable = nullptr;

    while (!failure && !success)
    {
      if (hasApplicableOperators(node, ancestors, undesirable))
      {
        Node* next = getFirstNonAncestralAdjacent(node, ancestors, undesirable);
        c += graph->getArcWeight(node, next);
        estimate = c + graph->getHeuristicValue(next, end);

        ancestors.push_front(next);

        if (estimate > bound)
        {
          c -= graph->getArcWeight(node, next);
          undesirable = ancestors.front();
          ancestors.remove(undesirable);
          node = ancestors.front();
        }
        else
        {
          node = next;
          undesirable = nullptr;
        }

        if (node == end)
          success = true;
      }
      else
      {
        if (node == start)
        {
          failure = true;
        }
        else
        {
          undesirable = ancestors.front();
          ancestors.remove(undesirable);
          node = ancestors.front();
        }
      }
    }

    cost = c;

    if (failure)
      throw "Não há solução possível entre os dois nós fornecidos.";

    return ancestors;
  }

 /* A estratégia para determinar se um nó tem operadores aplicáveis se baseia em verificar se os
  * seus adjacentes são ou não ancestrais
  */
  bool hasApplicableOperators(Node *node, std::list<Node *> ancestors, Node* undesirable)
  {
    int adjacentAncestors = 0;

    for (Node* adjacent : node->adjacents)
      for (Node* ancestor : ancestors)
        if (adjacent == ancestor && adjacent != undesirable)
          adjacentAncestors++;

    // Há operadores aplicáveis se pelo menos um dos nós adjacentes não é ancestral
    return adjacentAncestors != node->adjacents.size();
  }

  /* O terceiro parâmetro é passado para evitar a geração de um nó indesejável (útil no backtrack para
   * evitar que o nó gere um filho cujo retorno ao pai já foi realizado)
   */
  Node* getFirstNonAncestralAdjacent(Node *node, std::list<Node *> ancestors, Node *undesirable)
  {
    int nonAdjacentAncestors;

    for (Node* adjacent : node->adjacents)
    {
      nonAdjacentAncestors = 0;

      for (Node* ancestral : ancestors)
        if (adjacent != ancestral && adjacent != undesirable)
          nonAdjacentAncestors++;

      if (nonAdjacentAncestors == ancestors.size())
        return adjacent;
    }

    throw "Runtime error";
  }
};

#endif // IDASTAR_H_INCLUDED
