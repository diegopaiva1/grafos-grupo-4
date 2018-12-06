/**
 * @file    Graph.hpp
 * @author  Diego Paiva e Silva
 * @date    13/10/2018
 *
 * Esta classe representa um grafo na memória através de um vetor de nós em que cada nó ocupa
 * a posição correspondente ao seu id (como uma função de hash tal que h(k) = k).
 * A matriz 'arcs' armazena o valor do peso do arco entre dois nós i e j pertencentes ao
 * conjunto de nós do grafo. Exemplo de arquivo de leitura de uma instância:
 *
 * x y
 * 1 2 c1
 * 1 5 c2
 * ...
 * n 5 cn
 *
 * x e y representam a quantidade de nós e arcos, respectivamente.
 * Todas as linhas abaixo de 'x y' representam todos os arcos (cauda, cabeça e peso) da instância.
 */

#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <fstream>
#include "Node.hpp"
#include <cmath>

class Graph
{
public:
  std::vector<Node *> nodes;
  std::vector<std::vector<double>> arcs;

  Graph(std::string instanceFile) { mount(instanceFile); }

  ~Graph() {}

 /* Constrói os nós, arcos e heuristicas do grafo através do arquivo da
  * instância passada como argumento no construtor
  */
  void mount(std::string instanceFile)
  {
    int nodesAmount;
    int arcsAmount;
    double x1;
    double y1;
    double x2;
    double y2;
    int id1;
    int id2;
    double weight;
    std::ifstream file(instanceFile);

    if (!file.is_open())
    {
      std::cout << "Erro na leitura do arquivo" << std::endl;
      exit(0);
    }
    else
    {
      // Eis a primeira linha
      file >> nodesAmount;
      file >> arcsAmount;

      nodes.resize(nodesAmount + 1);
      arcs.resize(arcsAmount + 1);

      // Dummy node '0' pois os nós começam a partir de 1
      addNode(0, 0, 0);

      // Lê todos os arcos definidos no arquivo
      for (int i = 0; i < arcsAmount; i++)
      {
        file >> id1;
        file >> x1;
        file >> y1;
        file >> id2;
        file >> x2;
        file >> y2;
        file >> weight;

        if (!hasNode(id1))
          addNode(x1, y1, id1);

        if (!hasNode(id2))
          addNode(x2, y2, id2);

        arcs.at(id1).resize(nodesAmount + 1);
        addArc(id1, id2, weight);
      }
    }
  }

  void addNode(double x, double y, int id)
  {
    if (!hasNode(id))
      nodes.at(id) = new Node(x, y, id);
    else
      throw "Nó já existe no grafo!";
  }

  bool hasNode(int id) { return nodes.at(id) != NULL; }

  Node* getNode(int id) { return nodes.at(id); }

  void addArc(int id1, int id2, double weight)
  {
    if (hasNode(id1) && hasNode(id2))
    {
      nodes.at(id1)->addEdge(nodes.at(id2));
      arcs.at(id1).at(id2) = weight;
    }
    else
    {
      throw "Impossível adicionar arco - Nó(s) não existe(m) no grafo de entrada";
    }
  }

  double getArcWeight(Node *node1, Node *node2)
  {
    if (hasNode(node1->id) && hasNode(node2->id))
      return arcs.at(node1->id).at(node2->id);
    else
      throw "O(s) nó(s) não existe(m) no grafo de entrada";
  }

  std::list<Node *> getAdjacents(int id)
  {
    std::list<Node *> adjacents;

    for (int i = 0; i < arcs.at(id).size(); i++)
    {
      if (arcs.at(id).at(i) != NULL)
        adjacents.push_back(getNode(i));
    }

    return adjacents;
  }

  double getEuclidianDistance(Node *node1, Node *node2)
  {
    if (hasNode(node1->id) && hasNode(node2->id))
      return sqrt(pow(node2->x - node1->x, 2) + pow(node2->y - node1->y, 2));
    else
      throw "O(s) nó(s) não existe(m) no grafo de entrada";
  }
};

#endif // GRAPH_H_INCLUDED
