#include "./GulosoRandomizadoReativo.h"

std::list<No *> GulosoRandomizadoReativo::subconjuntoIndependenteMaximo(Grafo *grafo,
                                                                        int tamanhoBlocoAtualizacao,
                                                                        int iteracoesMaximas)
{
  std::list<No *> solucao;
  std::list<No *> melhorSolucao = guloso->subconjuntoIndependenteMaximo(grafo);
  std::vector<No *> candidatos;

  float alpha[TAMANHO] = {0.05, 0.10, 0.15, 0.20, 0.25, 0.30, 0.35, 0.40, 0.45, 0.50};
  int quantidadeVezesAlphaFoiSelecionado[TAMANHO] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  int custo[TAMANHO] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  float media[TAMANHO];
  float probabilidade[TAMANHO] = {100, 100, 100, 100, 100, 100, 100, 100, 100, 100};
  float q[TAMANHO];
  float melhorAlpha;

  for (int i = 0; i < TAMANHO; i++)
  {
    media[i] = melhorSolucao.size();
    q[i] = 1.0f;
  }

  for (int i = 0; i < iteracoesMaximas; i++)
  {
    preencherCandidatos(candidatos, grafo);
    ordenarCandidatosPor(candidatos, grauCrescente);
    if(i % tamanhoBlocoAtualizacao == 0)
    {
      std::cout << "Probabilidade atualizada:" << std::endl;
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
      melhorAlpha = alpha[indiceAlpha];
    }
    // -------------------* Calculos a serem refatorados *---------- //
    custo[indiceAlpha] += solucao.size();
    media[indiceAlpha] = custo[indiceAlpha]/quantidadeVezesAlphaFoiSelecionado[indiceAlpha];
    q[indiceAlpha] = melhorSolucao.size()/media[indiceAlpha];
    // --------------------------*---------------------------------- //
    solucao.clear();
  }

  std::cout << "Melhor alpha = " << melhorAlpha << std::endl;
  return melhorSolucao;
}

void GulosoRandomizadoReativo::atualizarProbabilidades(float *probabilidade, float *q)
{
  for (int i = 0; i < TAMANHO; i++)
  {
    probabilidade[i] = q[i]/somatorio(q);
    probabilidade[i] *= 1000;
    std::cout << probabilidade[i] << std::endl;
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
    if(alphaAleatorio <= soma)
    {
      indiceEscolhido = i;
      break;
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
