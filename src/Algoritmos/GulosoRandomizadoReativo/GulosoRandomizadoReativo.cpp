#include "./GulosoRandomizadoReativo.h"

std::list<No *> GulosoRandomizadoReativo::subconjuntoIndependenteMaximo(Grafo *grafo,
                                                                        int tamanhoBlocoAtualizacao,
                                                                        int iteracoesMaximas)
{
  float alpha[TAMANHO] = {0.05, 0.10, 0.15, 0.20, 0.25, 0.30, 0.35, 0.40, 0.45, 0.50};
  int quantidadeVezesAlphaFoiSelecionado[TAMANHO] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  int custo[TAMANHO];
  float media[TAMANHO];
  float probabilidade[TAMANHO] = {0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10};
  float q[TAMANHO];

  std::list<No *> solucao;
  std::list<No *> melhorSolucao = guloso->subconjuntoIndependenteMaximo(grafo);
  std::vector<No *> candidatos;

  for (int i = 0; i < iteracoesMaximas; i++)
  {
    preencherCandidatos(candidatos, grafo);
    ordenarCandidatosPor(candidatos, grauCrescente);
    if(i % tamanhoBlocoAtualizacao == 0)
    {
      atualizarProbabilidades(probabilidade, q);
    }
    int indiceAlpha = escolherIndiceAlpha(probabilidade);
    quantidadeVezesAlphaFoiSelecionado[indiceAlpha]++;
    while(candidatos.size() > 0)
    {
      int posicao = gerarInteiroAleatorioEntre(0, ceil(candidatos.size() * alpha[indiceAlpha]));
      No *noEscolhido = candidatos.at(posicao);
      solucao.push_back(noEscolhido);
      atualizarCandidatos(noEscolhido, candidatos);
    }
    if(solucao.size() > melhorSolucao.size())
    {
      melhorSolucao = solucao;
    }
    // -------------------* Calculos a serem refatorados *---------- //
    custo[indiceAlpha] += solucao.size();
    media[indiceAlpha] = custo[indiceAlpha]/quantidadeVezesAlphaFoiSelecionado[indiceAlpha];
    q[indiceAlpha] = melhorSolucao.size()/media[indiceAlpha];
    // --------------------------*---------------------------------- //
    solucao.clear();
  }
  return melhorSolucao;
}

void GulosoRandomizadoReativo::atualizarProbabilidades(float *probabilidade, float *q)
{
  for (int i = 0; i < TAMANHO; i++)
  {
    probabilidade[i] = pow(q[i]/somatorio(q), 1000);
    probabilidade[i] *= 1000;
  }
}

int GulosoRandomizadoReativo::escolherIndiceAlpha(float *probabilidade)
{
  int alphaAleatorio = gerarInteiroAleatorioEntre(0, 1000);
  int indiceEscolhido = 0;
  float soma = 0;
  for (int i = 0; i < TAMANHO; i++)
  {
    soma += probabilidade[i];
    if(soma >= alphaAleatorio)
    {
      indiceEscolhido = i;
    }
  }
  return indiceEscolhido;
}

float GulosoRandomizadoReativo::somatorio(float *arrayNumeros)
{
  float soma = 0;
  for (int i = 0; i < TAMANHO; i++)
  {
    soma += arrayNumeros[i];
  }
  return soma;
}
