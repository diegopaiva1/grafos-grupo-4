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

        // Estrutura auxiliar
        No* nosLidos[ordem];

        // Demais linhas
        while(arquivo >> id1 >> id2 >> pesoAresta) {

            if(!noJaFoiLido(nosLidos, id1)) {
              No *no = new No(id1);
              nosLidos[id1-1] = no;
            }

            if(!noJaFoiLido(nosLidos, id2)) {
              No *no = new No(id2);
              nosLidos[id2-1] = no;
            }

            No *primeiroNoListaAdjacencia = *adjacente[id1-1].begin();

            if(!listaContemNo(adjacente[id1-1], nosLidos[id1-1])) {
                adjacente[id1-1].push_back(nosLidos[id1-1]);
            }

            if(!listaContemNo(adjacente[id1-1], nosLidos[id2-1])) {
                adjacente[id1-1].push_back(nosLidos[id2-1]);
            }

            Aresta *aresta = new Aresta(nosLidos[id1-1], nosLidos[id2-1], pesoAresta);
            arestas.push_back(aresta);

        }

        preencherListasVazias(adjacente, ordem);
        popularAdjacencias(adjacencias, adjacente, ordem);
    }
}

bool GraphFileReader::noJaFoiLido(No* nosLidos[], int id)
{
  return nosLidos[id-1]->getId() == id ? true : false;
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
