#include "Grafo.h"

Grafo::Grafo(std::string nomeArquivo)
{
    this->listaNos = new ListaEncadeada();
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
    double id1, id2, pesoAresta;
    std::ifstream arquivo(nomeArquivo);

    if(!arquivo.is_open()) {
        std::cout << "Erro na leitura do arquivo" << std::endl;
    }
    else {
        // Le a primeira linha do arquivo e atribui o valor à ordem do grafo
        arquivo >> this->ordem;

        // Le as demais linhas e insere os nos na lista de nos
        while(arquivo >> id1 >> id2 >> pesoAresta) {
            No *no1 = new No(id1);
            No *no2 = new No(id2);

            if(!this->listaNos->contem(no1)) {
                this->listaNos->inserirNoInicio(no1);
            }

            if(!this->listaNos->contem(no2)) {
                this->listaNos->inserirNoInicio(no2);
            }
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

ListaEncadeada* Grafo::getListaNos()
{
    return this->listaNos;
}
