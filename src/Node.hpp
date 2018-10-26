#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

#include <iostream>
#include <list>
#include <vector>

class Node
{
public:
  int id;
  Node *father; // Utilizado para guardar o caminho em algumas buscas
  bool visited; // Utilizado para determinar se foi visitado em algumas buscas
  bool ancestral; // Utilizado no backtracking para verificar se é ancestral
  std::list<Node *> adjacents;

  Node(int id)
  {
    this->id = id;
    this->visited = false;
    this->ancestral = false;
    this->father = NULL;
  };

  ~Node() {};

  void addEdge(Node *node)
  {
    adjacents.push_back(node);
  }

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
