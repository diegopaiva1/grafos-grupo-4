#include "./No.h"

No::No(int id)
{
  this->id = id;
  this->grauEntrada = 0;
  this->grauSaida = 0;
  this->bipartiteFlag = INT_MAX;
}

No::No()
{
  this->grauEntrada = 0;
  this->grauSaida = 0;
  this->bipartiteFlag = INT_MAX;
}

No::~No()
{
  // destructor
}

bool No::operator==(const No& no) const
{
  return id == no.id;
}

bool No::operator!=(const No& no) const
{
  return !(operator==(no));
}

