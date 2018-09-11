#include "./Componentes/Grafo/Grafo.h"
#include "./Componentes/Arquivo/Leitor/LeitorArquivoGrafo.h"
#include "./Componentes/Menu/Menu.h"

using namespace std;

int main(int argc, char* argv[])
{
  // Arquivo passado por linha de comando
  string arquivoEntrada = argv[1];

  Grafo *grafo = new Grafo();

  LeitorArquivoGrafo::atribuirDados(arquivoEntrada, *grafo);

  return 0;
}
