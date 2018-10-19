#ifndef ARC_H_INCLUDED
#define ARC_H_INCLUDED

#include "Node.hpp"

class Arc
{
public:
  Node *node1;
  Node *node2;
  double weight;

  Arc(Node *node1, Node *node2, double weight)
  {
    this->node1 = node1;
    this->node2 = node2;
    this->weight = weight;
  };

  ~Arc() {};
};

#endif // ARC_H_INCLUDED
