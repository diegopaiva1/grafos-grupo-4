#include "../Headers/Grafo.h"

Grafo::Grafo(std::string arquivo)
{
    this->arquivo = arquivo;
    this->leArquivo();
}

Grafo::Grafo()
{
    this->ordem = 0;
}

Grafo::~Grafo()
{
    // destructor
}

void Grafo::leArquivo()
{
    int id1, id2;
    double pesoAresta;
    std::ifstream arquivo(this->arquivo);

    if(!arquivo.is_open()) {
        std::cout << "Erro na leitura do arquivo" << std::endl;
    }
    else {
        // Le a primeira linha do arquivo e atribui o valor à ordem do grafo
        arquivo >> this->ordem;

        std::list<No*> adjacente[ordem];

        // Le as demais linhas e insere os nos na lista de nos
        while(arquivo >> id1 >> id2 >> pesoAresta) {
            No *no1 = new No(id1);
            No *no2 = new No(id2);

            Aresta *aresta = new Aresta(no1, no2, pesoAresta);
            arestas.push_back(aresta);

            // Adaptar o id do nó ao index do array de listas
            int index1 = id1 - 1;
            int index2 = id2 - 1;

            if(!listaContemNo(adjacente[index1], no1)) {
                adjacente[index1].push_back(no1);
            }

            if(!listaContemNo(adjacente[index1], no2)) {
                adjacente[index1].push_back(no2);
            }

            if(!listaContemNo(adjacente[index2], no2)) {
                adjacente[index2].push_back(no2);
            }

            if(!listaContemNo(adjacente[index2], no1)) {
                adjacente[index2].push_back(no1);
            }
        }

        popularListaAdjacencia(adjacente);
    }
}

bool Grafo::listaContemNo(std::list<No*> lista, No *no) {
    std::list<No*>::iterator i;
    for(i = lista.begin(); i != lista.end(); i++) {
        No *noLista = *i;
        if(noLista->getId() == no->getId()) {
            return true;
        }
    }
    return false;
}

void Grafo::popularListaAdjacencia(std::list<No*> *adjacente)
{
    for(int i = 0; i < ordem; i++) {
        this->listaAdjacencia.push_back(adjacente[i]);
    }
}

void Grafo::incluirNo(No *no)
{
    bool noExiste = false;
    std::list<std::list<No*>>::iterator i;
    for(i = listaAdjacencia.begin(); i != listaAdjacencia.end(); i++) {
        std::list<No*> lista = *i;
        No *primeiroNoLista = *lista.begin();
        if(primeiroNoLista->ehIgualA(no)) {
            noExiste = true;
        }
    }

    if(!noExiste) {
        this->ordem++;
        // Cria lista de adjacencia do no informado
        std::list<No*> lista;
        lista.push_back(no);
        // Adiciona nova lista à lista de adjecencias do grafo
        this->listaAdjacencia.push_back(lista);

        std::ofstream myfile;
        myfile.open(this->arquivo, std::ios_base::app);
        myfile << no->getId() << "\n";
    }
    else {
        std::cout << "No ja existe no grafo!" << std::endl;
    }

}

void Grafo::excluirNo(int id)
{
    this->ordem--;

    std::list<std::list<No*>>::iterator i;

    for(i = listaAdjacencia.begin(); i != listaAdjacencia.end(); i++) {
        std::list<No*> &lista = *i;
        std::list<No*>::iterator j;
        for(j = lista.begin(); j != lista.end(); j++) {
            No *no = *j;
            if(no->getId() == id) {
                // TODO
            }
        }
    }
}

void Grafo::incluirAresta(Aresta *aresta)
{
    this->arestas.push_back(aresta);

    std::list<std::list<No*>>::iterator i;

    for(i = listaAdjacencia.begin(); i != listaAdjacencia.end(); i++) {
        std::list<No*> &lista = *i;
        No *primeiroNoLista = *lista.begin();

        if(primeiroNoLista->ehIgualA(aresta->getPrimeiroNo())) {
            lista.push_back(aresta->getSegundoNo());
        }

        if(primeiroNoLista->ehIgualA(aresta->getSegundoNo())) {
            lista.push_back(aresta->getPrimeiroNo());
        }
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
        if(arestas.size() == 0) {
            return true;
        }
        else {
            return false;
        }
    }
}

bool Grafo::ehMultigrafo()
{
    bool possuiSelfLoop = false;
    bool possuiArestaMultipla = false;
    std::list<Aresta*>::iterator i;
    for(i = arestas.begin(); i != arestas.end(); i++) {
        Aresta *aresta = *i;
        No *no1 = aresta->getPrimeiroNo();
        No *no2 = aresta->getSegundoNo();
        // Caso 1: Self-loop
        if(no1->ehIgualA(no2)) {
            possuiSelfLoop = true;
        }
        // Caso 2: Aresta multipla
        std::list<Aresta*>::iterator k;
        for(k = std::next(i); k != arestas.end(); k++) {
            Aresta *arestaComparacao = *k;
            No *no3 = arestaComparacao->getPrimeiroNo();
            No *no4 = arestaComparacao->getSegundoNo();
            if( (no1->ehIgualA(no3) && no2->ehIgualA(no4)) || (no1->ehIgualA(no4) && no2->ehIgualA(no3)) ) {
                possuiArestaMultipla = true;
            }
        }
    }

    return (possuiSelfLoop || possuiArestaMultipla);
}

void Grafo::imprimeListaAdjacencia()
{
    std::list<std::list<No*>>::iterator i;
    // Itera por cada uma das listas de adjacencia
    for(i = listaAdjacencia.begin(); i != listaAdjacencia.end(); i++) {
        std::list<No*> listaNos = *i;
        std::list<No*>::iterator j;
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
    std::list<Aresta*>::iterator i;
    for(i = arestas.begin(); i != arestas.end(); i++) {
        Aresta *aresta = *i;
        std::cout << "Aresta " << n << ": (" << aresta->getPrimeiroNo()->getId() << ", "
                                             << aresta->getSegundoNo()->getId() << ") com peso "
                                             << aresta->getPeso() << std::endl;
        n++;
    }
}

No* Grafo::getNo(int id)
{
    std::list<std::list<No*>>::iterator i;
    for(i = listaAdjacencia.begin(); i != listaAdjacencia.end(); i++) {
        std::list<No*> lista = *i;
        No *no = *lista.begin();
        if(no->getId() == id) {
            return no;
        }
    }
    // TODO - Exception para id inexistente
    return NULL;
}
