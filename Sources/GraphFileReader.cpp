#include "../Headers/GraphFileReader.h"

void GraphFileReader::read(std::string file,
                           int &ordem,
                           std::list<Aresta*> &arestas,
                           std::list<std::list<No*>> &adjacencias)
{
    int id1, id2;
    double pesoAresta;
    std::ifstream arquivo(file);

    if(!arquivo.is_open()) {
        std::cout << "Erro na leitura do arquivo" << std::endl;
    }
    else {

        // Eis a primeira linha
        arquivo >> ordem;

        std::list<No*> adjacente[ordem];

        // Demais linhas
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

        preencherListasVazias(adjacente, ordem);
        popularAdjacencias(adjacencias, adjacente, ordem);
    }
}

bool GraphFileReader::listaContemNo(std::list<No*> lista, No *no) {
    std::list<No*>::iterator i;
    for(i = lista.begin(); i != lista.end(); i++) {
        No *noLista = *i;
        if(noLista->getId() == no->getId()) {
            return true;
        }
    }
    return false;
}

void GraphFileReader::preencherListasVazias(std::list<No*> *adjacente, int ordem)
{
    for(int i = 0; i < ordem; i++) {
        if(adjacente[i].empty()) {
            No *no = new No(i+1);
            adjacente[i].push_back(no);
        }
    }
}

void GraphFileReader::popularAdjacencias(std::list<std::list<No*>> &adjacencias,
                                                   std::list<No*> *adjacente,
                                                   int ordem)
{
    for(int i = 0; i < ordem; i++) {
        adjacencias.push_back(adjacente[i]);
    }
}
