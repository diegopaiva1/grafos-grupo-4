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
  * instância passada como argumento
  */
  void mount(std::string instanceFile)
  {
    int nodesAmount;
    int arcsAmount;
    int heuristicsAmount;
    std::string id1;
    std::string id2;
    std::string weight;
    std::string heuristic;
    std::ifstream file(instanceFile);
    std::streampos old;

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

      // Demais linhas
      while (file >> id1 >> id2 >> weight && id1 != "heuristics")
      {
        if (!hasNode(atoi(id1.c_str())))
        {
          addNode(atoi(id1.c_str()));
          heuristics.at(atoi(id1.c_str())).resize(heuristicsAmount + 1);
        }

        if (!hasNode(atoi(id2.c_str())))
        {
          addNode(atoi(id2.c_str()));
          heuristics.at(atoi(id2.c_str())).resize(heuristicsAmount + 1);
        }

        arcs.at(atoi(id1.c_str())).resize(nodesAmount + 1);
        addArc(atoi(id1.c_str()), atoi(id2.c_str()), atof(weight.c_str()));

        // Salva posição da última linha lida
        old = file.tellg();
      }

      // Retoma na linha que encontrou "heuristics"
      file.seekg(old);

      // Descarta o "heuristics"
      file >> id1;

      // Retoma a leitura dos valores (começam as heurísticas)
      while (file >> id1 >> id2 >> heuristic)
        addHeuristic(atoi(id1.c_str()), atoi(id2.c_str()), atof(heuristic.c_str()));
    }
  }

  Node* getNode(int id) { return nodes.at(id); }

  void addNode(int id)
  {
    if (!hasNode(id))
      nodes.at(id) = new Node(id);
    else
      throw "Nó já existe no grafo!";
  }

  bool hasNode(int id) { return nodes.at(id) != NULL; }

  void addArc(int id1, int id2, double weight)
  {
    if (hasNode(id1) && hasNode(id2))
    {
      nodes.at(id1)->addEdge(nodes.at(id2));
      arcs.at(id1).at(id2) = weight;
    }
    else
    {
      throw "Impossível adicionar arco - Um dos nós não existe no grafo";
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
      throw "Impossível adicionar heurística - Um dos nós não existe no grafo";
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
