#include "./GulosoRandomizado.h"

std::list<No *> GulosoRandomizado::subconjuntoIndependenteMaximo(Grafo *grafo, float alpha,
                                                                 int iteracoesMaximas)
{
  std::list<No *> solucao;
  std::list<No *> melhorSolucao;
  std::vector<No *> candidatos;

  for (int i = 0; i < iteracoesMaximas; i++)
  {
    preencherCandidatos(candidatos, grafo);
    ordenarCandidatosPor(candidatos, grauCrescente);
    while(candidatos.size() > 0)
    {
      int posicao = gerarInteiroAleatorioEntre(0, ceil(candidatos.size() * alpha));
      No *noEscolhido = candidatos.at(posicao);
      solucao.push_back(noEscolhido);
      atualizarCandidatos(noEscolhido, candidatos);
    }
    if(solucao.size() > melhorSolucao.size())
    {
      melhorSolucao = solucao;
    }
    solucao.clear();
  }
  return melhorSolucao;
}

int GulosoRandomizado::gerarInteiroAleatorioEntre(int limiteInferior, int limiteSuperior)
{
  return rand() % limiteSuperior + limiteInferior;
}
