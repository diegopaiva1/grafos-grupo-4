#include "../Headers/No.h"

No::No(int id)
{
  this->id = id;
  this->bipartiteFlag = INT_MAX;
}

No::No()
{
  this->bipartiteFlag = INT_MAX;
}

No::~No()
{
  // destructor
}

bool No::operator==(const No &no) const
{
  return id == no.id;
}

bool No::operator!=(const No &no) const
{
  return !(operator==(no));
}
