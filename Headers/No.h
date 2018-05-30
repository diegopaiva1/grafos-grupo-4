/* Esta classe representa os nós do grafo.
 *
 * Cada nó conta com um id único e dois nós são considerados iguais quando seus
 * ids são iguais. O operador '==' foi sobrecarregado para avaliar este critério.
 * O atributo 'bipartiteFlag' é utilizado para 'colorir' o nó, sendo util para
 * determinar se um grafo é ou não bipartido.
 */

#ifndef NO_H_INCLUDED
#define NO_H_INCLUDED

#include <iostream>

class No
{
private:
  int id;
  bool bipartiteFlag;

public:
  No(int id);
  No();
  ~No();
  bool operator==(const No &no) const;
  bool operator!=(const No &no) const;
  int getId();
  bool getBipartiteFlag();
  void setBipartiteFlag(bool bipartiteFlag);
  void setId(int id);
  bool temBipartiteFlag();
};

#endif // NO_H_INCLUDED
