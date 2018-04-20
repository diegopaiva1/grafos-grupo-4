#include "No.h"

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

void No::setProximoNo(No *no)
{
    this->proximoNo = no;
}

No* No::getProximoNo()
{
    return this->proximoNo;
}

void No::setId(int id)
{
    this->id = id;
}
