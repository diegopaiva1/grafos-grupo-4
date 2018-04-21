#include "Grafo.h"

Grafo::Grafo(std::string nomeArquivo)
{
    this->leArquivo(nomeArquivo);
}

Grafo::Grafo()
{
    // construtor vazio
}

Grafo::~Grafo()
{
    // destructor
}

void Grafo::leArquivo(std::string nomeArquivo)
{
    int id1, id2;
    double pesoAresta;
    std::ifstream arquivo(nomeArquivo);

    if(!arquivo.is_open()) {
        std::cout << "Erro na leitura do arquivo" << std::endl;
    }
    else {
        // Le a primeira linha do arquivo e atribui o valor à ordem do grafo
        arquivo >> this->ordem;

        std::forward_list<No*> adjacente[ordem];

        // Le as demais linhas e insere os nos na lista de nos
        while(arquivo >> id1 >> id2 >> pesoAresta) {
            No *no1 = new No(id1);
            No *no2 = new No(id2);

            Aresta *aresta = new Aresta(no1, no2, pesoAresta);
            arestas.push_front(aresta);

            // Adaptar o id do nó ao index do array de listas
            int index1 = id1 - 1;
            int index2 = id2 - 1;

            if(!listaContemNo(adjacente[index1], no1)) {
                adjacente[index1].push_front(no1);
            }

            if(!listaContemNo(adjacente[index1], no2)) {
                adjacente[index1].push_front(no2);
            }

            if(!listaContemNo(adjacente[index2], no2)) {
                adjacente[index2].push_front(no2);
            }

            if(!listaContemNo(adjacente[index2], no1)) {
                adjacente[index2].push_front(no1);
            }
        }

        popularListaAdjacencia(adjacente);
    }
}

bool Grafo::listaContemNo(std::forward_list<No*> lista, No *no) {
    std::forward_list<No*>::iterator i;
    for(i = lista.begin(); i != lista.end(); i++) {
        No *noLista = *i;
        if(noLista->getId() == no->getId()) {
            return true;
        }
    }
    return false;
}

void Grafo::popularListaAdjacencia(std::forward_list<No*> *adjacente)
{
    for(int i = 0; i < ordem; i++) {
        this->listaAdjacencia.push_front(adjacente[i]);
    }
}

void Grafo::incluirNo(No *no)
{
    this->ordem++;

    std::forward_list<No*> lista;
    lista.push_front(no);

    // Adiciona nova lista a lista de adjacencia
    this->listaAdjacencia.push_front(lista);
}

void Grafo::incluirAresta(Aresta *aresta)
{
    this->arestas.push_front(aresta);

    std::forward_list<std::forward_list<No*>>::iterator i;

    for(i = listaAdjacencia.begin(); i != listaAdjacencia.end(); i++) {
        // TODO
    }
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
    if(this->ordem != 1) {
        return false;
    }
    else {
        // TODO
    }
}

void Grafo::imprimeListaAdjacencia()
{
    std::forward_list<std::forward_list<No*>>::iterator i;
    // Itera por cada uma das listas de adjacencia
    for(i = listaAdjacencia.begin(); i != listaAdjacencia.end(); i++) {
        std::forward_list<No*> listaNos = *i;
        std::forward_list<No*>::iterator j;
        // Itera por cada um dos nos de cada lista de adjacencia
        for(j = listaNos.begin(); j != listaNos.end(); j++) {
            No *no = *j;
            std::cout << no->getId() << " ";
        }
        std::cout << std::endl;
    }
}

void Grafo::imprimirArestas()
{
    int n = 1;
    std::forward_list<Aresta*>::iterator i;
    for(i = arestas.begin(); i != arestas.end(); i++) {
        Aresta *aresta = *i;
        std::cout << "Aresta " << n << ": (" << aresta->getPrimeiroNo()->getId() << ", "
                                             << aresta->getSegundoNo()->getId() << ") com peso "
                                             << aresta->getPeso() << std::endl;
        n++;
    }
}
