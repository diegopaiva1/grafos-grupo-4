#ifndef BACKTRACKING_H_INCLUDED
#define BACKTRACKING_H_INCLUDED

#include "../../Node.hpp"

class Backtracking
{
public:
  Backtracking() {};
  ~Backtracking() {};

  /* A solução retornada está na ordem reversa, isto é, o caminho começa no fim
   * da lista e termina no início
   */
  std::list<Node *> getPath(Node *start, Node *end)
  {
    Node *node = start;

    /* Dummy node com id inicial -1 para evitar loops infinitos no processo.
     * Vai sendo atualizado para evitar que um filho que já foi
     * totalmente explorado gere o mesmo filho novamente na volta.
     */
    Node *aux = new Node(-1);

    bool failure = false;
    bool success = false;

    std::list<Node *> ancestors;
    ancestors.push_front(node);

    while (!failure && !success)
    {
      if (hasApplicableOperators(node, ancestors, aux))
      {
        try
        {
          node = getFirstAdjacentThatIsNotAncestral(node, ancestors);
          ancestors.push_front(node);

          if (node == end)
          {
            success = true;
          }
        }
        catch (char const* exception)
        {
          std::cerr << exception << std::endl;
        }
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

    if (ancestors.empty())
    {
      throw "Não há solução possível entre os dois nós fornecidos.";
    }

    return ancestors;
  }

private:
  /* A estratégia para determinar se um nó tem operadores aplicáveis se baseia
   * em comparar os seus adjacentes com a lista de ancestrais
   */
  bool hasApplicableOperators(Node *no, std::list<Node *> ancestors, Node *aux)
  {
    int adjacentAncestors = 0;

    // Não contabilizamos como adjacente o nó que ele gerou (evita loop infinito)
    no->adjacentes.remove(aux);

    for (auto adjacent : no->adjacentes)
    {
      for (auto ancestral : ancestors)
      {
        if (ancestral == adjacent)
        {
          adjacentAncestors++;
        }
      }
    }

    /* Isso significa que todos os adjacentes são ancestrais, portanto não há nenhum adjacente
     * que possa ser visitado (nenhum operador aplicável)
     */
    if (adjacentAncestors == no->adjacentes.size())
    {
      return false;
    }

    return true;
  }

  Node* getFirstAdjacentThatIsNotAncestral(Node *no, std::list<Node *> ancestors)
  {
    for (auto adjacent : no->adjacentes)
    {
      bool isDifferentFromAllAncestors = true;

      for (auto ancestral : ancestors)
      {
        if (adjacent == ancestral)
        {
          isDifferentFromAllAncestors = false;
        }
      }

      /* Retorna o primeiro nó que é diferente de todos os ancestrais. Deste modo, evita
       * computação desnecessária
       */
      if (isDifferentFromAllAncestors)
      {
        return adjacent;
      }
    }

    throw "Todos os adjacentes deste nó são ancestrais!";
  }
};

#endif // BACKTRACKING_H_INCLUDED
