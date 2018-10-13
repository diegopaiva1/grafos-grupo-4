#include "Node.hpp"
#include "Algoritmos/searching/Backtracking.hpp"

int main(int argc, char* argv[])
{
  Node *nos[9];

  for (int i = 0; i < 9; i++)
  {
    nos[i] = new Node(i);
  }

  nos[0]->adjacentes.push_back(nos[7]);

  nos[1]->adjacentes.push_back(nos[2]);
  nos[1]->adjacentes.push_back(nos[7]);

  nos[2]->adjacentes.push_back(nos[1]);

  nos[3]->adjacentes.push_back(nos[7]);

  nos[4]->adjacentes.push_back(nos[5]);
  nos[4]->adjacentes.push_back(nos[7]);

  nos[5]->adjacentes.push_back(nos[4]);
  nos[5]->adjacentes.push_back(nos[6]);
  nos[5]->adjacentes.push_back(nos[8]);

  nos[6]->adjacentes.push_back(nos[5]);

  nos[7]->adjacentes.push_back(nos[0]);
  nos[7]->adjacentes.push_back(nos[1]);
  nos[7]->adjacentes.push_back(nos[3]);
  nos[7]->adjacentes.push_back(nos[4]);

  nos[8]->adjacentes.push_back(nos[5]);

  Backtracking *backtracking = new Backtracking();

  try
  {
    std::list<Node *> path = backtracking->getPath(nos[0], nos[8]);
    std::cout << "Solução: ";
    for (auto i = path.rbegin(); i != path.rend(); i++)
    {
      Node *node = *i;
      std::cout << node->id << " ";
    }
  }
  catch (char const* exception)
  {
    std::cerr << exception << std::endl;
  }

  return 0;
}
