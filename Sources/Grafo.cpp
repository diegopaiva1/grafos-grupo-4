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
  for (auto i = adjacencias.begin(); i != adjacencias.end(); i++)
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
    // Comparando as sequencias de grau dois a dois
    for (auto i = sequenciaGrau.begin(); i != sequenciaGrau.end(); i++)
    {
      for (auto j = std::next(i); j != sequenciaGrau.end(); j++)
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
  for (auto i = arestas.begin(); i != arestas.end(); i++)
  {
    Aresta *aresta = *i;
    No *no1 = aresta->getPrimeiraExtremidade();
    No *no2 = aresta->getSegundaExtremidade();
    double pesoAresta = aresta->getPeso();
    for (auto j = std::next(i); j != arestas.end(); j++)
    {
      Aresta *arestaComparacao = *j;
      No *no3 = arestaComparacao->getPrimeiraExtremidade();
      No *no4 = arestaComparacao->getSegundaExtremidade();
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
  for (auto i = arestas.begin(); i != arestas.end(); i++)
  {
    Aresta *aresta = *i;
    No *no1 = aresta->getPrimeiraExtremidade();
    No *no2 = aresta->getSegundaExtremidade();
    if (no1 == no2)
    {
      return true;
    }
  }
  return false;
}

bool Grafo::possuiArestaMultipla()
{
  for (auto i = arestas.begin(); i != arestas.end(); i++)
  {
    Aresta *aresta = *i;
    // Compara arestas duas a duas
    for (auto k = std::next(i); k != arestas.end(); k++)
    {
      Aresta *arestaComparacao = *k;
      if (aresta->possuemMesmasExtremidades(arestaComparacao) &&
          aresta->getPeso() != arestaComparacao->getPeso())
      {
        return true;
      }
    }
  }
  return false;
}

bool Grafo::ehBipartido()
{
  for (auto i = adjacencias.begin(); i != adjacencias.end(); i++)
  {
    std::list<No *> nos = *i;
    No *primeiroNo = *nos.begin();
    if (!primeiroNo->temBipartiteFlag())
    {
      // Aqui é settada a flag, tanto faz se colocar true ou false inicialmente
      primeiroNo->setBipartiteFlag(false);
    }
    for (auto j = std::next(nos.begin()); j != nos.end(); j++)
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
  // Itera por cada uma das listas de adjacencia
  for (auto i = adjacencias.begin(); i != adjacencias.end(); i++)
  {
    std::list<No *> nos = *i;
    // Itera por cada um dos nos de cada lista de adjacencia
    for (auto j = nos.begin(); j != nos.end(); j++)
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
  for (auto i = arestas.begin(); i != arestas.end(); i++)
  {
    Aresta *aresta = *i;
    std::cout << "Aresta " << n << ": (" << aresta->getPrimeiraExtremidade()->getId() << ", "
              << aresta->getSegundaExtremidade()->getId() << ") com peso "
              << aresta->getPeso() << std::endl;
    n++;
  }
}

void Grafo::imprimirVizinhancaFechada(int id)
{
  bool idExisteNoGrafo = false;
  for (auto i = adjacencias.begin(); i != adjacencias.end(); i++)
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
  for (auto i = adjacencias.begin(); i != adjacencias.end(); i++)
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
  std::cout << "Sequencia de grau do grafo: ";
  for (auto i = sequenciaGrau.begin(); i != sequenciaGrau.end(); i++)
  {
    std::cout << *i << " ";
  }
}

void Grafo::imprimirGrau(int id)
{
  unsigned int grau = 0;
  unsigned int grauSaida = 0;
  unsigned int grauEntrada = 0;

  for (auto i = adjacencias.begin(); i != adjacencias.end(); i++)
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
  for (auto i = adjacencias.begin(); i != adjacencias.end(); i++)
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
  // TODO - Reduzir a ordem em 1 e remover todas as arestas que contem o nó no arquivo texto
  if (this->possuiNo(id))
  {
    ordem--;
    for (auto i = adjacencias.begin(); i != adjacencias.end(); /* incrementação condicional */)
    {
      std::list<No *> &nos = *i;
      No *primeiroNo = *nos.begin();
      if (primeiroNo->getId() == id)
      {
        i = adjacencias.erase(i);
      }
      else
      {
        for (auto j = nos.begin(); j != nos.end(); j++)
        {
          No *no = *j;
          if (no->getId() == id)
          {
            j = nos.erase(j);
          }
        }
        i++;
      }
    }
    excluirArestasOndeExtremidade(id);
  }
  else
  {
    std::cout << "Não é possivel apagar o nó: nó não existente." << std::endl;
  }

  setSequenciaGrau();
}

void Grafo::excluirArestasOndeExtremidade(int id)
{
  for (auto i = arestas.begin(); i != arestas.end(); /* incrementação condicional */)
  {
    Aresta *aresta = *i;
    No *primeiraExtremidade = aresta->getPrimeiraExtremidade();
    No *segundaExtremidade = aresta->getSegundaExtremidade();
    if (primeiraExtremidade->getId() == id || segundaExtremidade->getId() == id)
    {
      i = arestas.erase(i);
    }
    else
    {
      i++;
    }
  }
}

bool Grafo::possuiNo(int id)
{
  for (auto i = adjacencias.begin(); i != adjacencias.end(); i++)
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

void Grafo::incluirAresta(int idPrimeiraExtremidade, int idSegundaExtremidade, double peso)
{
  if (this->possuiNo(idPrimeiraExtremidade) && this->possuiNo(idSegundaExtremidade))
  {
    No *primeiraExtremidade = inicializarExtremidade(primeiraExtremidade, idPrimeiraExtremidade);
    No *segundaExtremidade = inicializarExtremidade(segundaExtremidade, idSegundaExtremidade);

    if (!this->possuiAresta(idPrimeiraExtremidade, idSegundaExtremidade, peso))
    {
      adicionarNaListaAdjacenciaDoNo(primeiraExtremidade, segundaExtremidade);
      adicionarNaListaAdjacenciaDoNo(segundaExtremidade, primeiraExtremidade);

      Aresta *aresta = new Aresta(primeiraExtremidade, segundaExtremidade, peso);
      arestas.push_back(aresta);
      // TODO - Gravar no arquivo texto a nova aresta
    }
    else
    {
      std::cout << "Erro: aresta ja existente no grafo." << std::endl;
    }
  }
  else
  {
    std::cout << "Erro: pelo menos um dos nós não existe no grafo." << std::endl;
  }

  setSequenciaGrau();
}

No* Grafo::inicializarExtremidade(No *extremidade, int idExtremidade)
{
  for (auto i = adjacencias.begin(); i != adjacencias.end(); i++)
  {
    std::list<No *> nos = *i;
    for (auto j = nos.begin(); j != nos.end(); j++)
    {
      No *no = *j;
      if (no->getId() == idExtremidade)
      {
        extremidade = no;
      }
    }
  }
  return extremidade;
}

void Grafo::adicionarNaListaAdjacenciaDoNo(No *no, No *noParaAdicionar)
{
  for (auto i = adjacencias.begin(); i != adjacencias.end(); i++)
  {
    std::list<No *> &nos = *i;
    No *primeiroNo = *nos.begin();
    bool nosContemNoParaAdicionar = (std::find(nos.begin(), nos.end(), noParaAdicionar) != nos.end());
    if (primeiroNo == no && !nosContemNoParaAdicionar)
    {
      nos.push_back(noParaAdicionar);
    }
  }
}

bool Grafo::possuiAresta(int idPrimeiraExtremidade, int idSegundaExtremidade, double peso)
{
  for (auto i = arestas.begin(); i != arestas.end(); i++)
  {
    Aresta *aresta = *i;
    No *primeiraExtremidade = aresta->getPrimeiraExtremidade();
    No *segundaExtremidade = aresta->getSegundaExtremidade();
    double pesoAresta = aresta->getPeso();
    if (primeiraExtremidade->getId() == idPrimeiraExtremidade &&
        segundaExtremidade->getId() == idSegundaExtremidade &&
        pesoAresta == peso)
    {
      return true;
    }
  }
  return false;
}
