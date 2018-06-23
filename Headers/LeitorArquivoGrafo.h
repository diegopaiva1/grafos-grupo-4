/* Esta classe é responsável por realizar a leitura de um arquivo texto e atribuir
 * os dados lidos a um objeto do tipo 'Grafo'. O arquivo passado deve ser disposto da forma:
 *
 * n
 * v1 v2 c1
 * v3 v4 c2
 * ...
 * vn v2 cn
 *
 * 'n' representa a ordem do grafo (quantidade de nós) e todas as linhas abaixo de 'n'
 * representam os arcos formados pelos n nós e seus respectivos pesos (c).
 */

#ifndef LEITORARQUIVOGRAFO_H
#define LEITORARQUIVOGRAFO_H

#include <iostream>
#include <fstream>
#include <string>
#include <list>

#include "Grafo.h"
#include "Arco.h"
#include "GrafoUtils.h"
#include "NoUtils.h"

class LeitorArquivoGrafo
{
private:
  static void setSequenciaGrau(Grafo& grafo);
public:
  static void atribuirDados(std::string arquivo, Grafo& grafo);
};

#endif // LEITORARQUIVOGRAFO_H
