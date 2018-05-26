#include "../Headers/No.h"

No::No(int id)
{
    this->id = id;
    this->bipartiteFlag = NULL;
}

No::No()
{

}

No::~No()
{
    // destructor
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

bool No::ehIgualA(No *no)
{
    return this->id == no->getId() ? true : false;
}

bool No::temBipartiteFlag()
{
  return this->bipartiteFlag != NULL ? true : false;
}
