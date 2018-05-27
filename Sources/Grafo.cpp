#include "../Headers/Grafo.h"

Grafo::Grafo(std::string arquivo)
{
  GraphFileReader::read(arquivo, ordem, arestas, adjacencias);
  this->arquivo = arquivo;
  this->setSequenciaGrau();
}

Grafo::Grafo()
{
  this->ordem = 0;
  this->setSequenciaGrau();
}

Grafo::~Grafo()
{
  // destructor
}

void Grafo::setSequenciaGrau()
{
  sequenciaGrau.clear();
  std::list<std::list<No *>>::iterator i;
  for (i = adjacencias.begin(); i != adjacencias.end(); i++)
  {
    std::list<No *> lista = *i;
    // Quantidade de nos adjacentes para cada lista
    int grauNo = lista.size() - 1;
    sequenciaGrau.push_back(grauNo);
  }
  sequenciaGrau.sort();
  sequenciaGrau.reverse();
}

int Grafo::getOrdem()
{
  return this->ordem;
}

bool Grafo::ehNulo()
{
  return this->ordem == 0 ? true : false;
}

bool Grafo::ehTrivial()
{
  if (this->ordem != 1)
  {
    return false;
  }
  else
  {
    if (arestas.size() == 0)
    {
      return true;
    }
    else
    {
      return false;
    }
  }
}

bool Grafo::ehCompleto()
{
  if (possuiArestaMultipla() || possuiSelfLoop())
  {
    return false;
  }
  else
  {
    std::list<int>::iterator i;
    // Comparando as sequencias de grau dois a dois
    for (i = sequenciaGrau.begin(); i != sequenciaGrau.end(); i++)
    {
      std::list<int>::iterator j;
      for (j = std::next(i); j != sequenciaGrau.end(); j++)
      {
        if (*i != *j || *i != ordem - 1 || *j != ordem - 1)
        {
          return false;
        }
      }
    }
    return true;
  }
}

bool Grafo::ehDigrafo()
{
  unsigned int arestasNaoDirecionadas = 0;
  std::list<Aresta *>::iterator i;
  for (i = arestas.begin(); i != arestas.end(); i++)
  {
    Aresta *aresta = *i;
    No *no1 = aresta->getPrimeiroNo();
    No *no2 = aresta->getSegundoNo();
    double pesoAresta = aresta->getPeso();
    std::list<Aresta *>::iterator j;
    for (j = std::next(i); j != arestas.end(); j++)
    {
      Aresta *arestaComparacao = *j;
      No *no3 = arestaComparacao->getPrimeiroNo();
      No *no4 = arestaComparacao->getSegundoNo();
      double pesoArestaComparacao = arestaComparacao->getPeso();
      if (no1 == (no4) && no2 == (no3) && pesoAresta == pesoArestaComparacao)
      {
        arestasNaoDirecionadas++;
      }
    }
  }
  if (arestasNaoDirecionadas == arestas.size() / 2)
  {
    return false;
  }
  else
  {
    return true;
  }
}

bool Grafo::ehGrafoGeral()
{
  return possuiSelfLoop() || possuiArestaMultipla();
}

bool Grafo::ehMultigrafo()
{
  return !possuiSelfLoop() && possuiArestaMultipla();
}

bool Grafo::possuiSelfLoop()
{
  std::list<Aresta *>::iterator i;
  for (i = arestas.begin(); i != arestas.end(); i++)
  {
    Aresta *aresta = *i;
    No *no1 = aresta->getPrimeiroNo();
    No *no2 = aresta->getSegundoNo();
    if (no1 == (no2))
    {
      return true;
    }
  }
  return false;
}

bool Grafo::possuiArestaMultipla()
{
  std::list<Aresta *>::iterator i;
  for (i = arestas.begin(); i != arestas.end(); i++)
  {
    Aresta *aresta = *i;
    std::list<Aresta *>::iterator k;
    for (k = std::next(i); k != arestas.end(); k++)
    {
      Aresta *arestaComparacao = *k;
      if (aresta->possuemMesmasExtremidades(arestaComparacao) && aresta->getPeso() != arestaComparacao->getPeso())
      {
        return true;
      }
    }
  }
  return false;
}

bool Grafo::ehBipartido()
{
  std::list<std::list<No *>>::iterator i;
  for (i = adjacencias.begin(); i != adjacencias.end(); i++)
  {
    std::list<No *> nos = *i;
    std::list<No *>::iterator j;
    No *primeiroNo = *nos.begin();
    if (!primeiroNo->temBipartiteFlag())
    {
      // Aqui é settada a flag, tanto faz se colocar true ou false inicialmente
      primeiroNo->setBipartiteFlag(false);
    }
    for (j = std::next(nos.begin()); j != nos.end(); j++)
    {
      No *no = *j;
      if (!no->temBipartiteFlag())
      {
        bool flag = !primeiroNo->getBipartiteFlag();
        no->setBipartiteFlag(flag);
      }
      else if (no->getBipartiteFlag() == primeiroNo->getBipartiteFlag())
      {
        return false;
      }
    }
  }
  return true;
}

bool Grafo::ehKRegular(int k)
{
  if (k != ordem)
  {
    return false;
  }
  else
  {
    if (k == ordem && ehCompleto())
    {
      return true;
    }
    else
    {
      return false;
    }
  }
}

void Grafo::imprimirAdjacencias()
{
  std::list<std::list<No *>>::iterator i;
  // Itera por cada uma das listas de adjacencia
  for (i = adjacencias.begin(); i != adjacencias.end(); i++)
  {
    std::list<No *> nos = *i;
    std::list<No *>::iterator j;
    // Itera por cada um dos nos de cada lista de adjacencia
    for (j = nos.begin(); j != nos.end(); j++)
    {
      No *no = *j;
      std::cout << no->getId() << " ";
    }
    std::cout << std::endl;
  }
}

void Grafo::imprimirArestas()
{
  int n = 1;
  std::list<Aresta *>::iterator i;
  for (i = arestas.begin(); i != arestas.end(); i++)
  {
    Aresta *aresta = *i;
    std::cout << "Aresta " << n << ": (" << aresta->getPrimeiroNo()->getId() << ", "
              << aresta->getSegundoNo()->getId() << ") com peso "
              << aresta->getPeso() << std::endl;
    n++;
  }
}

void Grafo::imprimirVizinhancaFechada(int id)
{
  bool idExisteNoGrafo = false;
  std::list<std::list<No *>>::iterator i;
  for (i = adjacencias.begin(); i != adjacencias.end(); i++)
  {
    std::list<No *> lista = *i;
    No *primeiroNoLista = *lista.begin();
    if (primeiroNoLista->getId() == id)
    {
      idExisteNoGrafo = true;
      std::cout << "Vizinhança fechada do no " << id << ": ";
      std::list<No *>::iterator j;
      for (j = lista.begin(); j != lista.end(); j++)
      {
        No *no = *j;
        std::cout << no->getId() << " ";
      }
    }
  }

  if (!idExisteNoGrafo)
  {
    std::cout << "O no " << id << " não faz parte deste grafo" << std::endl;
  }
}

void Grafo::imprimirVizinhancaAberta(int id)
{
  bool idExisteNoGrafo = false;
  std::list<std::list<No *>>::iterator i;
  for (i = adjacencias.begin(); i != adjacencias.end(); i++)
  {
    std::list<No *> lista = *i;
    No *primeiroNoLista = *lista.begin();
    if (primeiroNoLista->getId() == id)
    {
      idExisteNoGrafo = true;
      std::cout << "Vizinhança aberta do no " << id << ": ";
      std::list<No *>::iterator j;
      for (j = std::next(lista.begin()); j != lista.end(); j++)
      {
        No *no = *j;
        std::cout << no->getId() << " ";
      }
    }
  }
  if (!idExisteNoGrafo)
  {
    std::cout << "O no " << id << " não faz parte deste grafo" << std::endl;
  }
}

void Grafo::imprimirSequenciaGrau()
{
  std::list<int>::iterator i;
  std::cout << "Sequencia de grau do grafo: ";
  for (i = sequenciaGrau.begin(); i != sequenciaGrau.end(); i++)
  {
    std::cout << *i << " ";
  }
}

void Grafo::imprimirGrau(int id)
{
  unsigned int grau = 0;
  unsigned int grauSaida = 0;
  unsigned int grauEntrada = 0;

  std::list<std::list<No *>>::iterator i;
  for (i = adjacencias.begin(); i != adjacencias.end(); i++)
  {
    std::list<No *> lista = *i;
    No *primeiroNo = *lista.begin();
    std::list<No *>::iterator j;

    if (primeiroNo->getId() == id)
    {
      grau = lista.size() - 1; // Lista de adjacencias do nó menos ele mesmo
      grauSaida = grau;
    }

    for (j = std::next(lista.begin()); j != lista.end(); j++)
    {
      No *no = *j;
      if (no->getId() == id)
      {
        grauEntrada++;
      }
    }
  }

  if (ehDigrafo())
  {
    std::cout << "Grau de saida do no " << id << ": " << grauSaida << std::endl;
    std::cout << "Grau de entrada do no " << id << ": " << grauEntrada << std::endl;
  }
  else
  {
    std::cout << "Grau do no " << id << ": " << grau << std::endl;
  }
}

No *Grafo::getNo(int id)
{
  std::list<std::list<No *>>::iterator i;
  for (i = adjacencias.begin(); i != adjacencias.end(); i++)
  {
    std::list<No *> lista = *i;
    No *no = *lista.begin();
    if (no->getId() == id)
    {
      return no;
    }
  }
  // TODO - Exception para id inexistente
  return NULL;
}

void Grafo::incluirNo(int id)
{
  if (!this->possuiNo(id))
  {
    ordem++;
    No *no = new No(id);
    std::list<No *> adjacencia;
    adjacencia.push_back(no);
    adjacencias.push_back(adjacencia);
    setSequenciaGrau();
    GraphFileReader::write(arquivo, ordem, 0);
  }
  else
  {
    std::cout << "Erro: nó ja existe no grafo" << std::endl;
  }
}

void Grafo::excluirNo(int id)
{
  if (this->possuiNo(id))
  {
    ordem--;
    std::list<std::list<No *>>::iterator i;
    for (i = adjacencias.begin(); i != adjacencias.end(); i++)
    {
      std::list<No *> nos = *i;

      std::list<No *>::iterator j = nos.begin();
      while (j != nos.end())
      {
        No *no = *j;
        if (no->getId() == id)
        {
          j = nos.erase(j);
        }
        else
        {
          j++;
        }
      }
      /*
      No *primeiroNo = *nos.begin();

      if(primeiroNo->getId() == id) {
        i = adjacencias.erase(i);
      }
*/
    }
  }
  else
  {
    std::cout << "Não é possivel apagar o nó: nó não existente." << std::endl;
  }

  setSequenciaGrau();
}

bool Grafo::possuiNo(int id)
{
  std::list<std::list<No *>>::iterator i;
  for (i = adjacencias.begin(); i != adjacencias.end(); i++)
  {
    std::list<No *> nos = *i;
    std::list<No *>::iterator j;
    for (j = nos.begin(); j != nos.end(); j++)
    {
      No *no = *j;
      if (no->getId() == id)
      {
        return true;
      }
    }
  }
  return false;
}
