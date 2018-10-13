#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

#include <iostream>
#include <list>

class Node
{
public:
  int id;
  std::list<Node *> adjacentes;

  Node(int id)
  {
    this->id = id;
  };

  ~Node() {};

  bool operator==(const Node& no) const
  {
    return id == no.id;
  };

  bool operator!=(const Node& no) const
  {
    return !(operator==(no));
  };
};

#endif // NODE_H_INCLUDED
