/* Menu contendo as funcionalidades disponíveis da classe GrafoUtils
 * @author: Diego Paiva
 */

#ifndef MENU_H
#define MENU_H

#include <iostream>

#include "../../Utils/Grafo/GrafoUtils.h"

class Menu
{
public:
  Menu() {};
  ~Menu() {};
  void exibir();
  bool possuiOpcao(char opcao);
  void acionarAcao(Grafo &grafo, char opcao);
};

#endif // MENU_H
