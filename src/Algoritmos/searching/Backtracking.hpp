#ifndef BACKTRACKING_H_INCLUDED
#define BACKTRACKING_H_INCLUDED

#include "../../Node.hpp"

class Backtracking
{
public:
  Backtracking() {};
  ~Backtracking() {};

  void printPath(Node *start, Node *end)
  {
    auto path = getPath(start, end);

    std::cout << "Backtracking - Solução: ";
    for (auto i = path.rbegin(); i != path.rend(); i++)
    {
      Node *node = *i;
      std::cout << node->id << " ";
    }
    printf("\n");
  }

private:
  /* A solução retornada está na ordem reversa, isto é, o caminho começa no fim
   * da lista e termina no início
   */
  std::list<Node *> getPath(Node *start, Node *end)
  {
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

    while (!failure && !success)
    {
      if (hasApplicableOperators(node, aux))
      {
        try
        {
          node = getFirstAdjacentThatIsNotAncestral(node, ancestors);
          ancestors.push_front(node);
          node->ancestral = true;

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

    if (failure)
    {
      throw "Não há solução possível entre os dois nós fornecidos.";
    }

    return ancestors;
  }


  /* A estratégia para determinar se um nó tem operadores aplicáveis se baseia
   * em verificar se os seus adjacentes são ancestrais
   */
  bool hasApplicableOperators(Node *node, Node *aux)
  {
    int adjacentAncestors = 0;

    // Não contabilizamos como adjacente o nó que ele gerou (evita loop infinito)
    node->adjacentes.remove(aux);

    for (auto adjacent : node->adjacentes)
    {
      if (adjacent->ancestral)
      {
        adjacentAncestors++;
      }
    }

    /* Isso significa que todos os adjacentes são ancestrais, portanto não há nenhum adjacente
     * que possa ser visitado (nenhum operador aplicável)
     */
    if (adjacentAncestors == node->adjacentes.size())
    {
      return false;
    }

    return true;
  }

  Node* getFirstAdjacentThatIsNotAncestral(Node *node, std::list<Node *> ancestors)
  {
    for (auto adjacent : node->adjacentes)
    {
      if (!adjacent->ancestral)
      {
        return adjacent;
      }
    }

    throw "Todos os adjacentes deste nó são ancestrais!";
  }
};

#endif // BACKTRACKING_H_INCLUDED
