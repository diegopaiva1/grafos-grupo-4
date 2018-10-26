/**
 * @file    Searching.hpp
 * @author  Diego Paiva e Silva
 * @date    26/10/2018
 *
 * A classe Searching tem o propósito de servir como uma interface para que os algoritmos de busca
 * (backtracking, dfs, bfs, etc) implementem seus próprios métodos para realizar a busca pela solução,
 * além de reunir os métodos comuns a todas as busca. Esta classe é abstrata e portanto não pode ser
 * instanciada. Qualquer tentativa de instaciá-la irá gerar erros de compilação.
 */

#ifndef SEARCHING_H_INCLUDED
#define SEARCHING_H_INCLUDED

#include "../../Graph.hpp"

/* Estrutura utilizada nas buscas: ordenada, gulosa, A* e IDA*. Permite com que
 * a fila de prioridades armazene os nós com seus respectivos custos acumulados
 */
struct NodeCost
{
  Node *node;
  double cost;
};

/* Estrutura utilizada nas buscas: ordenada, gulosa, A* e IDA*. É empregada como terceiro
 * parâmetro em std::priority_queue para que possamos construir uma fila de prioridade
 * na qual o elemento mais prioritário é o de menor custo (como uma min-heap)
 */
struct LessThanByCost
{
  bool operator()(const NodeCost& nodeCost1, const NodeCost& nodeCost2) const
  {
    return nodeCost1.cost > nodeCost2.cost;
  }
};

class Searching
{
public:
  Searching() {};
  ~Searching() {};

  void printPath(Graph *graph, int start, int end)
  {
    auto path = getPath(graph, graph->getNode(start), graph->getNode(end));

    for (auto i = path.rbegin(); i != path.rend(); i++)
    {
      Node *node = *i;
      std::cout << node->id << " ";
    }
  }

private:
  virtual std::list<Node *> getPath(Graph *graph, Node *start, Node *end) = 0;
};

#endif // SEARCHING_H_INCLUDED
