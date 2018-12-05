/**
 * @file    Search.hpp
 * @author  Diego Paiva e Silva
 * @date    26/10/2018
 *
 * A classe Search tem o propósito de servir como uma interface para que os algoritmos de busca
 * (backtracking, dfs, bfs, etc) implementem seus próprios métodos para realizar a busca pela solução,
 * além de reunir o(s) método(s) comun(s) a todas as buscas. Esta classe é abstrata e portanto não pode
 * ser instanciada. Qualquer tentativa de instanciá-la irá gerar erros de compilação.
 */

#ifndef SEARCH_H_INCLUDED
#define SEARCH_H_INCLUDED

#include "../../Graph.hpp"
#include <time.h>
#include <chrono>

typedef std::chrono::high_resolution_clock Time;

/* Estrutura utilizada nas buscas: ordenada, gulosa e A*. Permite com que a
 * fila de prioridades armazene os nós com seus respectivos custos acumulados
 */
struct NodeCost
{
  Node *node;
  double cost;
  double costWithoutHeuristic;

  bool operator==(const NodeCost& nodeCost) const
  {
    return node == nodeCost.node && cost == nodeCost.cost &&
           costWithoutHeuristic == nodeCost.costWithoutHeuristic;
  }

  bool operator!=(const NodeCost& nodeCost) const
  {
    return !(operator==(nodeCost));
  }
};

/* Estrutura utilizada nas buscas: ordenada, gulosa e A*. É empregada como terceiro
 * parâmetro em std::priority_queue para que se possa construir uma fila de prioridades
 * na qual o elemento mais prioritário é o de menor custo (como uma min-heap)
 */
struct LessThanByCost
{
  bool operator()(const NodeCost& nodeCost1, const NodeCost& nodeCost2) const
  {
    return nodeCost1.cost > nodeCost2.cost;
  }
};

class Search
{
public:
  Search() {};
  ~Search() {};

  void printPath(Graph *graph, int start, int end)
  {
    Time::time_point t1 = Time::now(); // Tempo inicial de execução
    auto path = getPath(graph, graph->getNode(start), graph->getNode(end));
    Time::time_point t2 = Time::now(); // Tempo final de execução

    // Aqui calcula-se o tempo total de execução para o algoritmo em milisegundos
    cpuTime = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();

    for (auto i = path.rbegin(); i != path.rend(); i++)
    {
      Node *node = *i;
      std::cout << node->id << " ";
    }

    std::cout << "(Custo = " << cost << ", " << "tempo CPU = " << cpuTime/1000 << " microsegundos)" << std::endl;
  }

protected:
  int depth;
  double cpuTime;
  double cost;
  virtual std::list<Node *> getPath(Graph *graph, Node *start, Node *end) = 0;
};

#endif // SEARCH_H_INCLUDED
