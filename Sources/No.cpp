#include "../Headers/No.h"

No::No(int id)
{
  this->id = id;
  this->bipartiteFlag = NULL;
}

No::No()
{
  this->bipartiteFlag = NULL;
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

int No::getId()
{
  return this->id;
}

bool No::getBipartiteFlag()
{
  return this->bipartiteFlag;
}

void No::setBipartiteFlag(bool bipartiteFlag)
{
  this->bipartiteFlag = bipartiteFlag;
}

void No::setId(int id)
{
  this->id = id;
}

bool No::temBipartiteFlag()
{
  return this->bipartiteFlag != NULL ? true : false;
}
