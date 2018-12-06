/**
 * @file    Backtracking.hpp
 * @author  Diego Paiva e Silva
 * @date    13/10/2018
 *
 * O algoritmo Backtracking é um algoritmo de busca que fornece, caso exista, um caminho
 * (não necessariamente o mais curto) entre dois nós de entrada.
 *
 * Estratégia de controle utilizada: selecionar o primeiro adjacente que não é um ancestral.
 */

#ifndef BACKTRACKING_H_INCLUDED
#define BACKTRACKING_H_INCLUDED

#include "Search.hpp"

class Backtracking : public Search
{
public:
  Backtracking() {};
  ~Backtracking() {};

private:
  std::list<Node *> getPath(Graph *graph, Node *start, Node *end)
  {
    visitedNodes = 0;
    expandedNodes = 0;
    depth = 0;
    cost = 0.0;

    bool failure = false;
    bool success = false;

    std::list<Node *> ancestors;
    ancestors.push_front(start);

    Node *node = start;
    Node *undesirable = nullptr;

    while (!failure && !success)
    {
      if (hasApplicableOperators(node, ancestors, undesirable))
      {
        cost += graph->getArcWeight(node, getFirstNonAncestralAdjacent(node, ancestors, undesirable));
        node = getFirstNonAncestralAdjacent(node, ancestors, undesirable);
        expandedNodes++;
        ancestors.push_front(node);
        visitedNodes++;
        depth++;

        if (node == end)
          success = true;

        undesirable = nullptr;
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
          cost -= graph->getArcWeight(node, undesirable);
          depth--;
        }
      }
    }

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

#endif // BACKTRACKING_H_INCLUDED
