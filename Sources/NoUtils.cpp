#include "../Headers/NoUtils.h"

bool NoUtils::possuiAdjacenteComId(No *no, int id)
{
  for (auto i = no->adjacentes.begin(); i != no->adjacentes.end(); i++)
  {
    No *noAdjacente = *i;
    if(noAdjacente->id == id)
    {
      return true;
    }
  }
  return false;
}

void NoUtils::imprimirAdjacentes(No *no)
{
  for(auto j = no->adjacentes.begin(); j != no->adjacentes.end(); j++)
  {
    No *adjacente = *j;
    std::cout << adjacente->id << " ";
  }
}
