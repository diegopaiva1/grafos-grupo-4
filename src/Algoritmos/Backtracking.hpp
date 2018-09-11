/**
 * @file    Backtracking.hpp
 * @author  Diego Paiva e Silva
 * @date    08/09/2018
 *
 * Implementação do algoritmo backtracking para busca não-informada.
 */

#ifndef BACKTRACKING_H_INCLUDED
#define BACKTRACKING_H_INCLUDED

#include <iostream>
#include <vector>

#include "../Componentes/Grafo/Grafo.h"

class Backtracking
{
public:
  Backtracking() {};
  ~Backtracking() {};

  void search(Grafo &grafo, No* inicial, No* objetivo)
  {
    auto S = inicial;
    auto N = S;
    bool fracasso = false;
    bool sucesso = false;

    // Nosso critério de seleção vai se dar por ordem crescente de id
    N->adjacentes.sort();

    while(!fracasso || !sucesso)
    {
      if(N->adjacentes.size() != 0)
      {
        N = N->adjacentes.front();
        if(N == objetivo)
        {
          sucesso = true;
        }
      }
      else
      {
        if(N == S)
        {
          fracasso = true;
        }
        else
        {

        }
      }
    }
  }
};

#endif // BACKTRACKING_H_INCLUDED
