#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include "Node.hpp"

class Graph
{
public:
  std::list<Node *> nodes;

  Graph() {}
  ~Graph() {};
};

#endif // GRAPH_H_INCLUDED
