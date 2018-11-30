/**
 * @file    Graph.hpp
 * @author  Diego Paiva e Silva
 * @date    13/10/2018
 *
 * Esta classe representa um grafo na memória através de um vetor de nós em que cada nó ocupa
 * a posição correspondente ao seu id (como uma função de hash tal que h(k) = k).
 * As matrizes 'arcs' e 'heuristics' armazenam o valor do peso do arco e da heurística,
 * respectivamente, entre dois nós i e j pertencentes ao conjunto de nós do grafo.
 * Exemplo de arquivo de leitura de uma instância:
 *
 * x y z
 * 1 2 c1
 * 1 5 c2
 * ...
 * n 5 cn
 * heuristics
 * 1 2 h1
 * 1 5 h2
 * ...
 * 1 n hn
 *
 * x, y e z representam a quantidade de nós, arcos e heurísticas, respectivamente.
 * Todas as linhas abaixo de 'x y z' e acima de 'heuristics' representam todos os
 * arcos (cauda, cabeça e peso) da instância.
 * Todas as linhas abaixo de 'heuristics' definem o valor da heurística de um nó
 * i para um nó j pertencentes ao conjunto de nós do grafo.
 */

#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <fstream>
#include "Node.hpp"

class Graph
{
public:
  std::vector<Node *> nodes;
  std::vector<std::vector<double>> arcs;
  std::vector<std::vector<double>> heuristics;

  Graph(std::string instanceFile) { mount(instanceFile); }

  ~Graph() {}

 /* Constrói os nós, arcos e heuristicas do grafo através do arquivo da
  * instância passada como argumento no construtor
  */
  void mount(std::string instanceFile)
  {
    int nodesAmount;
    int arcsAmount;
    int heuristicsAmount;
    int id1;
    int id2;
    double weight;
    double heuristic;
    std::ifstream file(instanceFile);
    std::string heuristicLabel; // Utilizado para descartar o label 'heuristics' do arquivo de leitura

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
      file >> heuristicsAmount;

      nodes.resize(nodesAmount + 1);
      arcs.resize(arcsAmount + 1);
      heuristics.resize(heuristicsAmount + 1);

      // Dummy node '0' pois os nós começam a partir de 1
      addNode(0);

      // Lê todos os arcos definidos no arquivo
      for (int i = 0; i < arcsAmount; i++)
      {
        file >> id1;
        file >> id2;
        file >> weight;

        if (!hasNode(id1))
        {
          addNode(id1);
          heuristics.at(id1).resize(heuristicsAmount + 1);
        }

        if (!hasNode(id2))
        {
          addNode(id2);
          heuristics.at(id2).resize(heuristicsAmount + 1);
        }

        arcs.at(id1).resize(nodesAmount + 1);
        addArc(id1, id2, weight);
      }

      // Descarta o label 'heuristics' do arquivo
      file >> heuristicLabel;

      // Lê todas as heurísticas do arquivo
      for (int i = 0; i < heuristicsAmount; i++)
      {
        file >> id1;
        file >> id2;
        file >> heuristic;

        addHeuristic(id1, id2, heuristic);
      }
    }
  }

  void addNode(int id)
  {
    if (!hasNode(id))
      nodes.at(id) = new Node(id);
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

  void addHeuristic(int id1, int id2, double value)
  {
    if (hasNode(id1) && hasNode(id2))
      heuristics.at(id1).at(id2) = value;
    else
      throw "Impossível adicionar heurística - Nó(s) não existe(m) no grafo de entrada";
  }

  double getHeuristicValue(Node *node1, Node *node2)
  {
    if (hasNode(node1->id) && hasNode(node2->id))
      return heuristics.at(node1->id).at(node2->id);
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
};

#endif // GRAPH_H_INCLUDED
