#include "../Headers/GrafoUtils.h"

bool GrafoUtils::ehNulo(Grafo& grafo)
{
  return grafo.ordem == 0 ? true : false;
}

bool GrafoUtils::ehTrivial(Grafo& grafo)
{
  if(grafo.ordem == 1 && grafo.arcos.size() == 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool GrafoUtils::ehCompleto(Grafo& grafo)
{
  if (possuiArcoMultiplo(grafo) || possuiSelfLoop(grafo))
  {
    return false;
  }
  else
  {
    for (auto i = grafo.sequenciaGrau.begin(); i != grafo.sequenciaGrau.end(); i++)
    {
      int grau = *i;
      if(grau != grafo.ordem - 1)
      {
        return false;
      }
    }
    return true;
  }
}

bool GrafoUtils::possuiArcoMultiplo(Grafo& grafo)
{
  for (auto i = grafo.arcos.begin(); i != grafo.arcos.end(); i++)
  {
    Arco *arco = *i;
    // Compara arcos duas a duas
    for (auto k = std::next(i); k != grafo.arcos.end(); k++)
    {
      Arco *arcoComparacao = *k;
      if (arco->possuemMesmasExtremidades(arcoComparacao) &&
          arco->peso != arcoComparacao->peso)
      {
        return true;
      }
    }
  }
  return false;
}

bool GrafoUtils::possuiSelfLoop(Grafo& grafo)
{
  for (auto i = grafo.arcos.begin(); i != grafo.arcos.end(); i++)
  {
    Arco *arco = *i;
    No *no1 = arco->no1;
    No *no2 = arco->no2;
    if (no1 == no2)
    {
      return true;
    }
  }
  return false;
}

bool GrafoUtils::ehGrafoGeral(Grafo& grafo)
{
  return possuiSelfLoop(grafo) || possuiArcoMultiplo(grafo);
}

bool GrafoUtils::ehMultigrafo(Grafo& grafo)
{
  return !possuiSelfLoop(grafo) && possuiArcoMultiplo(grafo);
}

bool GrafoUtils::ehBipartido(Grafo& grafo)
{
  for (auto i = grafo.nos.begin(); i != grafo.nos.end(); i++)
  {
    No *no = *i;
    if(no->bipartiteFlag == INT_MAX)
    {
      // Aqui é settada a flag inicial, tanto faz se colocar 0 ou 1 inicialmente
      no->bipartiteFlag = 0;
    }
    for(auto j = no->adjacentes.begin(); j != no->adjacentes.end(); j++)
    {
      No *adjacente = *j;
      if(adjacente->bipartiteFlag == INT_MAX)
      {
        no->bipartiteFlag == 0 ? adjacente->bipartiteFlag = 1
                               : adjacente->bipartiteFlag = 0;
      }
      else if(adjacente->bipartiteFlag == no->bipartiteFlag)
      {
        return false;
      }
    }
  }
  return true;
}

bool GrafoUtils::ehKRegular(Grafo& grafo, int k)
{
  int grau;
  for (auto i = grafo.sequenciaGrau.begin(); i != grafo.sequenciaGrau.end(); i++)
  {
    grau = *i;
    if(grau != k)
    {
      return false;
    }
  }
  return true;
}

bool GrafoUtils::ehDigrafo(Grafo &grafo)
{
  int arestas = 0;
  for (auto i = grafo.arcos.begin(); i != grafo.arcos.end(); i++)
  {
    Arco *arco = *i;
    No *no1 = arco->no1;
    No *no2 = arco->no2;
    double pesoArco = arco->peso;
    // Compara arcos dois a dois
    for (auto j = std::next(i); j != grafo.arcos.end(); j++)
    {
      Arco *arcoComparacao = *j;
      No *no3 = arcoComparacao->no1;
      No *no4 = arcoComparacao->no2;
      double pesoArcoComparacao = arcoComparacao->peso;
      if (no1 == no4 && no2 == no3 && pesoArco == pesoArcoComparacao)
      {
        arestas++;
      }
    }
  }
  if (arestas != grafo.arcos.size()/2)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool GrafoUtils::possuiNo(Grafo &grafo, int id)
{
  for(auto i = grafo.nos.begin(); i != grafo.nos.end(); i++)
  {
    No *no = *i;
    if(no->id == id)
    {
      return true;
    }
  }
  return false;
}

bool GrafoUtils::possuiArco(Grafo& grafo, Arco *arco)
{
  for (auto i = grafo.arcos.begin(); i != grafo.arcos.end(); i++)
  {
    Arco *arcoGrafo = *i;
    No *primeiraExtremidade = arcoGrafo->no1;
    No *segundaExtremidade = arcoGrafo->no2;
    double pesoArcoGrafo = arcoGrafo->peso;
    if (primeiraExtremidade->id == arco->no1->id &&
        segundaExtremidade->id == arco->no2->id &&
        pesoArcoGrafo == arco->peso)
    {
      return true;
    }
  }
  return false;
}

void GrafoUtils::incluirNo(Grafo& grafo, int id)
{
  if (!possuiNo(grafo, id))
  {
    grafo.ordem++;
    No *no = new No(id);
    grafo.nos.push_back(no);
    atualizarSequenciaGrau(grafo);
    // TODO - Incluir novo nó no arquivo texto
  }
  else
  {
    std::cout << "Erro: nó ja existe no grafo" << std::endl;
  }
}

void GrafoUtils::atualizarSequenciaGrau(Grafo& grafo)
{
  grafo.sequenciaGrau.clear();
  int grau;
  for (auto i = grafo.nos.begin(); i != grafo.nos.end(); i++)
  {
    No *no = *i;
    grau = no->adjacentes.size();
    grafo.sequenciaGrau.push_back(grau);
  }
  grafo.sequenciaGrau.sort();
  grafo.sequenciaGrau.reverse();
}

void GrafoUtils::incluirArco(Grafo& grafo, Arco *arco)
{
  if (possuiNo(grafo, arco->no1->id) &&
      possuiNo(grafo, arco->no2->id))
  {
    if (!possuiArco(grafo, arco))
    {
      grafo.arcos.push_back(arco);
      // TODO - Gravar no arquivo texto o novo arco
    }
    else
    {
      std::cout << "Erro: arco ja existente no grafo." << std::endl;
    }
  }
  else
  {
    std::cout << "Erro: pelo menos um dos nós não existe no grafo." << std::endl;
  }

  atualizarSequenciaGrau(grafo);
}

void GrafoUtils::excluirNo(Grafo &grafo, int id)
{
  // TODO - Reduzir a ordem em 1 e remover todas as arcos que contem o nó no arquivo texto
  if (possuiNo(grafo, id))
  {
    grafo.ordem--;
    for (auto i = grafo.nos.begin(); i != grafo.nos.end(); /* incrementação condicional */)
    {
      No *no = *i;
      if (no->id == id)
      {
        i = grafo.nos.erase(i);
      }
      else
      {
        for (auto j = no->adjacentes.begin(); j != no->adjacentes.end(); j++)
        {
          No *adjacente = *j;
          if (adjacente->id == id)
          {
            j = grafo.nos.erase(j);
          }
        }
        i++;
      }
    }
    excluirArcosComIdIgualA(grafo, id);
  }
  else
  {
    std::cout << "Não é possivel apagar o nó: nó não existente." << std::endl;
  }

  atualizarSequenciaGrau(grafo);
}

void GrafoUtils::excluirArcosComIdIgualA(Grafo& grafo, int id)
{
  for (auto i = grafo.arcos.begin(); i != grafo.arcos.end(); /* incrementação condicional */)
  {
    Arco *arco = *i;
    if (arco->no1->id == id || arco->no2->id == id)
    {
      i = grafo.arcos.erase(i);
    }
    else
    {
      i++;
    }
  }
}

No* GrafoUtils::getNo(Grafo& grafo, int id)
{
  for (auto i = grafo.nos.begin(); i != grafo.nos.end(); i++)
  {
    No *no = *i;
    if(no->id == id) {
      return no;
    }
  }
  // TODO - Exception para id inexistente
  return NULL;
}

void GrafoUtils::imprimirAdjacencias(Grafo& grafo)
{
  for(auto i = grafo.nos.begin(); i != grafo.nos.end(); i++)
  {
    No *no = *i;
    std::cout << no->id << " => ";
    for(auto j = no->adjacentes.begin(); j != no->adjacentes.end(); j++)
    {
      No *adjacente = *j;
      std::cout << adjacente->id << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

void GrafoUtils::imprimirArcos(Grafo& grafo)
{
  int n = 1;
  for (auto i = grafo.arcos.begin(); i != grafo.arcos.end(); i++)
  {
    Arco *arco = *i;
    std::cout << "Arco " << n << ": (" << arco->no1->id << ", "
              << arco->no2->id << ") com peso "
              << arco->peso << std::endl;
    n++;
  }
  std::cout << std::endl;
}

void GrafoUtils::imprimirVizinhancaFechada(Grafo &grafo, int id)
{
  bool noExisteNoGrafo = false;
  for(auto i = grafo.nos.begin(); i != grafo.nos.end(); i++)
  {
    No *no = *i;
    if(no->id == id)
    {
      noExisteNoGrafo = true;
      std::cout << "Vizinhança fechada do nó " << no->id << ": " << no->id << " ";
      NoUtils::imprimirAdjacentes(no);
    }
  }
  if (!noExisteNoGrafo)
  {
    std::cout << "O no " << id << " não faz parte deste grafo" << std::endl;
  }
  std::cout << std::endl;
}

void GrafoUtils::imprimirVizinhancaAberta(Grafo& grafo, int id)
{
  bool noExisteNoGrafo = false;
  for(auto i = grafo.nos.begin(); i != grafo.nos.end(); i++)
  {
    No *no = *i;
    if(no->id == id)
    {
      noExisteNoGrafo = true;
      std::cout << "Vizinhança aberta do nó " << no->id << ": ";
      NoUtils::imprimirAdjacentes(no);
    }
  }
  if (!noExisteNoGrafo)
  {
    std::cout << "O no " << id << " não faz parte deste grafo" << std::endl;
  }
  std::cout << std::endl;
}

void GrafoUtils::imprimirSequenciaGrau(Grafo& grafo)
{
  int grau;
  std::cout << "Sequência de grau do grafo: ";
  for (auto i = grafo.sequenciaGrau.begin(); i != grafo.sequenciaGrau.end(); i++)
  {
    grau = *i;
    std::cout << grau << " ";
  }
  std::cout << std::endl;
}

void GrafoUtils::imprimirGrau(Grafo& grafo, int id)
{
  int grau = 0;
  int grauSaida = 0;
  int grauEntrada = 0;
  bool noExisteNoGrafo = false;

  for (auto i = grafo.nos.begin(); i != grafo.nos.end(); i++)
  {
    No *no = *i;

    if (no->id == id)
    {
      grau = no->adjacentes.size();
      grauSaida = grau;
      noExisteNoGrafo = true;
    }

    for (auto j = no->adjacentes.begin(); j != no->adjacentes.end(); j++)
    {
      No *adjacente = *j;
      if (adjacente->id == id)
      {
        grauEntrada++;
      }
    }
  }

  if (noExisteNoGrafo && ehDigrafo(grafo))
  {
    std::cout << "Grau de saida do no " << id << ": " << grauSaida << std::endl;
    std::cout << "Grau de entrada do no " << id << ": " << grauEntrada << std::endl;
  }
  else if(noExisteNoGrafo && !ehDigrafo(grafo))
  {
    std::cout << "Grau do no " << id << ": " << grau << std::endl;
  }
  else
  {
    std:: cout << "O no " << id << " não existe no grafo de entrada" << std::endl;
  }
}

