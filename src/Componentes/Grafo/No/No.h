/* Esta classe representa os nós de um grafo.
 *
 * Cada nó conta com um id único e dois nós são considerados iguais quando seus
 * ids são iguais.
 *
 * O atributo 'bipartiteFlag' é utilizado para 'colorir' o nó com 0 ou 1, sendo util
 * para determinar se um grafo é ou não bipartido.
 */

#ifndef NO_H_INCLUDED
#define NO_H_INCLUDED

#include <iostream>
#include <list>
#include <climits> // INT_MAX

class No
{
public:
  No(int id);
  No();
  ~No();
  int id;
  int grauSaida;
  int grauEntrada;
  std::list<No *> adjacentes;
  int bipartiteFlag;
  bool operator==(const No& no) const;
  bool operator!=(const No& no) const;
};

#endif // NO_H_INCLUDED
