#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include "Arc.hpp"
#include <vector>

class Graph
{
public:
  int order;
  std::vector<Node *> nodes;
  std::vector<std::list<Arc *>> arcs;

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
    nodes.at(id1)->addEdge(nodes.at(id2));

    Arc *arc = new Arc(nodes.at(id1), nodes.at(id2), weight);

    arcs.at(id1).push_back(arc);
  };

  std::list<Arc *> getNodeArcs(int id)
  {
    if (hasNode(id))
    {
      return arcs.at(id);
    }
    else
    {
      throw "Nó não existente no grafo!";
    }
  }
};

#endif // GRAPH_H_INCLUDED
