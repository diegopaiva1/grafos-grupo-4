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

    for (auto node : graph->nodes)
      node->ancestral = false;

    int bound = graph->getHeuristicValue(start, end);
    Node *node = start;

   /* Dummy node com id inicial -1 para evitar loops infinitos no processo.
    * Vai sendo atualizado para evitar que um filho que já foi
    * totalmente explorado gere o mesmo filho novamente na volta
    */
    Node *aux = new Node(-1);

    bool failure = false;
    bool success = false;

    std::list<Node *> ancestors;
    ancestors.push_front(node);
    node->ancestral = true;

    int i = 0;

    while (!failure && !success)
    {
      if (hasApplicableOperators(node, aux))
      {
        i += graph->getArcWeight(node, getFirstAdjacentThatIsNotAncestral(node, ancestors));
        // node = getFirstAdjacentThatIsNotAncestral(node, ancestors);
        int c = i + graph->getHeuristicValue(getFirstAdjacentThatIsNotAncestral(node, ancestors), end);

        node = getFirstAdjacentThatIsNotAncestral(node, ancestors);

        ancestors.push_front(node);
        node->ancestral = true;

        if (c > bound)
        {
          i -= graph->getArcWeight(node, getFirstAdjacentThatIsNotAncestral(node, ancestors));
          aux = ancestors.front();
          aux->ancestral = false;
          ancestors.remove(aux);
          node = ancestors.front();
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
          aux = ancestors.front();
          ancestors.remove(aux);
          node = ancestors.front();
        }
      }
    }

    if (failure)
      throw "Não há solução possível entre os dois nós fornecidos.";

    return ancestors;
  }

 /* A estratégia para determinar se um nó tem operadores aplicáveis se baseia
  * em verificar se os seus adjacentes são ancestrais
  */
  bool hasApplicableOperators(Node *node, Node *aux)
  {
    int adjacentAncestors = 0;

    // Não contabilizamos como adjacente o nó que ele gerou (evita loop infinito)
    node->adjacents.remove(aux);

    for (auto adjacent : node->adjacents)
      if (adjacent->ancestral)
        adjacentAncestors++;

   /* Isso significa que todos os adjacentes são ancestrais, portanto não há nenhum adjacente
    * que possa ser visitado (nenhum operador aplicável)
    */
    if (adjacentAncestors == node->adjacents.size())
      return false;

    return true;
  }

  Node* getFirstAdjacentThatIsNotAncestral(Node *node, std::list<Node *> ancestors)
  {
    for (auto adjacent : node->adjacents)
      if (!adjacent->ancestral)
        return adjacent;

    throw "Todos os adjacents deste nó são ancestrais!";
  }
};

#endif // IDASTAR_H_INCLUDED
