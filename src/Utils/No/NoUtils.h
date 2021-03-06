#ifndef NOUTILS_H_INCLUDED
#define NOUTILS_H_INCLUDED

#include <iostream>
#include <list>
#include <algorithm> // std::find

#include "../../Componentes/Grafo/No/No.h"

class NoUtils
{
public:
  static bool possuiAdjacenteComId(No *no, int id);
  static void imprimirAdjacentes(No *no);
};

#endif // NOUTILS_H_INCLUDED
