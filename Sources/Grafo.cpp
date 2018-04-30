#include "../Headers/Grafo.h"

Grafo::Grafo(std::string arquivo)
{
    this->arquivo = arquivo;
    this->leArquivo();
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

            if(!listaContemNo(adjacente[index1], no1)) {
                adjacente[index1].push_back(no1);
            }

            if(!listaContemNo(adjacente[index1], no2)) {
                adjacente[index1].push_back(no2);
            }
        }

        preencherListasVazias(adjacente);
        popularListaListaAdjacencias(adjacente);
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

void Grafo::preencherListasVazias(std::list<No*> *adjacente)
{
    for(int i = 0; i < ordem; i++) {
        if(adjacente[i].empty()) {
            No *no = new No(i+1);
            adjacente[i].push_back(no);
        }
    }
}

void Grafo::popularListaListaAdjacencias(std::list<No*> *adjacente)
{
    for(int i = 0; i < ordem; i++) {
        this->listaListaAdjacencias.push_back(adjacente[i]);
    }
}

void Grafo::setSequenciaGrau()
{
    std::list<std::list<No*>>::iterator i;
    for(i = listaListaAdjacencias.begin(); i != listaListaAdjacencias.end(); i++) {
        std::list<No*> lista = *i;
        // Quantidade de nos adjacentes para cada lista
        int grauNo = lista.size() - 1;
        sequenciaGrau.push_back(grauNo);
    }

    sequenciaGrau.sort();
    sequenciaGrau.reverse();
}

/*
 * ====================================== TODO =========================================
 *
void Grafo::incluirNo(No *no)
{
    bool noExiste = false;
    std::list<std::list<No*>>::iterator i;
    for(i = listaListaAdjacencias.begin(); i != listaListaAdjacencias.end(); i++) {
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
        this->listaListaAdjacencias.push_back(lista);

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

    for(i = listaListaAdjacencias.begin(); i != listaListaAdjacencias.end(); i++) {
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

    for(i = listaListaAdjacencias.begin(); i != listaListaAdjacencias.end(); i++) {
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
*/

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

bool Grafo::ehCompleto()
{
    if(ehDigrafo() || ehGrafoGeral()) {
        return false;
    }
    else {
        std::list<int>::iterator i;
        // Comparando as sequencias de grau dois a dois
        for(i = sequenciaGrau.begin(); i != sequenciaGrau.end(); i++) {
            std::list<int>::iterator j;
            for(j = std::next(i); j != sequenciaGrau.end(); j++) {
                if(*i != *j) {
                    return false;
                }
            }
        }
        return true;
    }
}

bool Grafo::ehGrafoGeral()
{
    return possuiSelfLoop() || possuiArestaMultipla();
}

bool Grafo::ehDigrafo()
{
    unsigned int arestasNaoDirecionadas = 0;
    std::list<Aresta*>::iterator i;
    for(i = arestas.begin(); i != arestas.end(); i++) {
        Aresta *aresta = *i;
        No *no1 = aresta->getPrimeiroNo();
        No *no2 = aresta->getSegundoNo();
        double pesoAresta = aresta->getPeso();
        std::list<Aresta*>::iterator j;
        for(j = std::next(i); j != arestas.end(); j++) {
            Aresta *arestaComparacao = *j;
            No *no3 = arestaComparacao->getPrimeiroNo();
            No *no4 = arestaComparacao->getSegundoNo();
            double pesoArestaComparacao = arestaComparacao->getPeso();
            if(no1->ehIgualA(no4) && no2->ehIgualA(no3) && pesoAresta == pesoArestaComparacao) {
                arestasNaoDirecionadas++;
            }
        }
    }
    if(arestasNaoDirecionadas == arestas.size()/2) {
        return false;
    }
    else {
        return true;
    }
}

bool Grafo::ehMultigrafo()
{
    return !possuiSelfLoop() && possuiArestaMultipla();
}

bool Grafo::possuiSelfLoop()
{
    std::list<Aresta*>::iterator i;
    for(i = arestas.begin(); i != arestas.end(); i++) {
        Aresta *aresta = *i;
        No *no1 = aresta->getPrimeiroNo();
        No *no2 = aresta->getSegundoNo();
        if(no1->ehIgualA(no2)) {
            return true;
        }
    }
    return false;
}

bool Grafo::possuiArestaMultipla()
{
    std::list<Aresta*>::iterator i;
    for(i = arestas.begin(); i != arestas.end(); i++) {
        Aresta *aresta = *i;
        std::list<Aresta*>::iterator k;
        for(k = std::next(i); k != arestas.end(); k++) {
            Aresta *arestaComparacao = *k;
            if(aresta->possuemMesmasExtremidades(arestaComparacao) && aresta->getPeso() != arestaComparacao->getPeso()) {
                return true;
            }
        }
    }
    return false;
}

bool Grafo::ehKRegular(int k)
{
    if(k != ordem) {
        return false;
    }
    else {
        if(k == ordem && ehCompleto()) {
            return true;
        }
        else {
            return false;
        }
    }
}

void Grafo::imprimirListaListaAdjacencias()
{
    std::list<std::list<No*>>::iterator i;
    // Itera por cada uma das listas de adjacencia
    for(i = listaListaAdjacencias.begin(); i != listaListaAdjacencias.end(); i++) {
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

void Grafo::imprimirVizinhancaFechada(int id)
{
    bool idExisteNoGrafo = false;
    std::list<std::list<No*>>::iterator i;
    for(i = listaListaAdjacencias.begin(); i != listaListaAdjacencias.end(); i++) {
        std::list<No*> lista = *i;
        No *primeiroNoLista = *lista.begin();
        if(primeiroNoLista->getId() == id) {
            idExisteNoGrafo = true;
            std::cout << "Vizinhança fechada do no " << id << " : ";
            std::list<No*>::iterator j;
            for(j = lista.begin(); j != lista.end(); j++) {
                No *no = *j;
                std::cout << no->getId() << " ";
            }
        }
    }

    if(!idExisteNoGrafo) {
        std::cout << "O no " << id << " não faz parte deste grafo" << std::endl;
    }
}

void Grafo::imprimirVizinhancaAberta(int id)
{
    bool idExisteNoGrafo = false;
    std::list<std::list<No*>>::iterator i;
    for(i = listaListaAdjacencias.begin(); i != listaListaAdjacencias.end(); i++) {
        std::list<No*> lista = *i;
        No *primeiroNoLista = *lista.begin();
        if(primeiroNoLista->getId() == id) {
            idExisteNoGrafo = true;
            std::cout << "Vizinhança aberta do no " << id << " : ";
            std::list<No*>::iterator j;
            for(j = std::next(lista.begin()); j != lista.end(); j++) {
                No *no = *j;
                std::cout << no->getId() << " ";
            }
        }
    }
    if(!idExisteNoGrafo) {
        std::cout << "O no " << id << " não faz parte deste grafo" << std::endl;
    }
}

void Grafo::imprimirSequenciaGrau()
{
    std::list<int>::iterator i;
    std::cout << "Sequencia de grau do grafo: ";
    for(i = sequenciaGrau.begin(); i != sequenciaGrau.end(); i++) {
        std::cout << *i << " ";
    }
}

void Grafo::imprimirGrau(int id)
{
    unsigned int grau = 0;
    unsigned int grauSaida = 0;
    unsigned int grauEntrada = 0;

    std::list<std::list<No*>>::iterator i;
    for(i = listaListaAdjacencias.begin(); i != listaListaAdjacencias.end(); i++) {
        std::list<No*> lista = *i;
        No *primeiroNo = *lista.begin();
        std::list<No*>::iterator j;

        if(primeiroNo->getId() == id) {
            grau = lista.size() - 1; // Lista de adjacencias do nó menos ele mesmo
            grauSaida = grau;
        }

        for(j = std::next(lista.begin()); j != lista.end(); j++) {
            No *no = *j;
            if(no->getId() == id) {
                grauEntrada++;
            }
        }
    }

    if(ehDigrafo()) {
        std::cout << "Grau de saida do no " << id << ": " << grauSaida << std::endl;
        std::cout << "Grau de entrada do no " << id << ": " << grauEntrada << std::endl;
    }
    else {
        std::cout << "Grau do no " << id << " :" << grau << std::endl;
    }
}

No* Grafo::getNo(int id)
{
    std::list<std::list<No*>>::iterator i;
    for(i = listaListaAdjacencias.begin(); i != listaListaAdjacencias.end(); i++) {
        std::list<No*> lista = *i;
        No *no = *lista.begin();
        if(no->getId() == id) {
            return no;
        }
    }
    // TODO - Exception para id inexistente
    return NULL;
}
