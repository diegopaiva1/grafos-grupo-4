/* Esta classe é responsável por realizar a leitura dos dados de um grafo a partir
 * de um arquivo texto. A passagem de parâmetros para o metodo "read" é feita por
 * referência.
 *
 * Dado um arquivo texto:
 * Leia a primeira linha do arquivo e atribua o valor a ordem do grafo;
 * Crie n listas de adjacências tal que n = ordem;
 * Leia as demais linhas e construa as arestas do grafo;
 * Salve todos os nós e seus adjacentes em uma estrutura de lista de adjacências.
 */

#ifndef GRAPHFILEREADER_H
#define GRAPHFILEREADER_H

#include <iostream>
#include <fstream>
#include <string>
#include <list>

#include "Aresta.h"

class GraphFileReader
{
    public:
        static void read(std::string file,
                         int &ordem,
                         std::list<Aresta*> &arestas,
                         std::list<std::list<No*>> &adjacencias);
    private:
        static void preencherListasVazias(std::list<No*> *lista, int ordem);

        static void popularAdjacencias(std::list<std::list<No*>> &adjacencias,
                                                 std::list<No*> *lista,
                                                 int ordem);

        static bool listaContemNo(std::list<No*> lista, No *no);

        static bool noJaFoiLido(No* nosLidos[], int id);
};

#endif // GRAPHFILEREADER_H
