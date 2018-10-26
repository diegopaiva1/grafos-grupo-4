#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include "Node.hpp"

class Graph
{
public:
  int order;
  std::vector<Node *> nodes;
  std::vector<std::vector<double>> arcs;
  std::vector<std::vector<double>> heuristics;

  Graph() {};
  ~Graph() {};

  Node* getNode(int id)
  {
    return nodes.at(id);
  };

  void addNode(int id)
  {
    if (!hasNode(id))
    {
      nodes.at(id) = new Node(id);
    }
    else
    {
      throw "Nó já existe no grafo!";
    }
  };

  bool hasNode(int id)
  {
    return nodes.at(id) != NULL;
  };

  void addArc(int id1, int id2, double weight)
  {
    if (hasNode(id1) && hasNode(id2))
    {
      nodes.at(id1)->addEdge(nodes.at(id2));
      arcs.at(id1).at(id2) = weight;
    }
    else
    {
      throw "Impossível adicionar arco - Um dos nós não existe no grafo";
    }
  };

  double getArcWeight(Node *node1, Node *node2)
  {
    if (hasNode(node1->id) && hasNode(node2->id))
    {
      return arcs.at(node1->id).at(node2->id);
    }
    else
    {
      throw "O(s) nó(s) não existe(m) no grafo de entrada";
    }
  }

  void addHeuristic(int id1, int id2, double value)
  {
    if (hasNode(id1) && hasNode(id2))
    {
      heuristics.at(id1).at(id2) = value;
    }
    else
    {
      throw "Impossível adicionar heurística - Um dos nós não existe no grafo";
    }
  };

  double getHeuristicValue(Node *node1, Node *node2)
  {
    if (hasNode(node1->id) && hasNode(node2->id))
    {
      return heuristics.at(node1->id).at(node2->id);
    }
    else
    {
      throw "O(s) nó(s) não existe(m) no grafo de entrada";
    }
  }

  std::list<Node *> getAdjacents(int id)
  {
    std::list<Node *> adjacents;

    for (int i = 0; i < arcs.at(id).size(); i++)
    {
      if (arcs.at(id).at(i) != NULL)
      {
        adjacents.push_back(getNode(i));
      }
    }

    return adjacents;
  }
};

#endif // GRAPH_H_INCLUDED
