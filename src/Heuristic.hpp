#ifndef HEURISTIC_H_INCLUDED
#define HEURISTIC_H_INCLUDED

#include "Node.hpp"

class Heuristic
{
public:
  Node *node1;
  Node *node2;
  double value;

  Heuristic(Node *node1, Node *node2, double value)
  {
    this->node1 = node1;
    this->node2 = node2;
    this->value = value;
  };

  ~Heuristic() {};
};

#endif // HEURISTIC_H_INCLUDED
