#include "../Headers/No.h"

No::No(int id)
{
    this->id = id;
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

void No::setId(int id)
{
    this->id = id;
}

bool No::ehIgualA(No *no)
{
    return this->id == no->getId() ? true : false;
}
