#include "./Guloso.h"

std::list<No *> Guloso::subconjuntoIndependenteMaximo(Grafo *grafo, float alpha, int iteracoesMaximas)
{
  std::list<No *> solucao;
  std::vector<No *> candidatos;

  preencherCandidatos(candidatos, grafo);
  ordenarCandidatosPor(candidatos, grauCrescente);

  while(candidatos.size() > 0)
  {
    No *noEscolhido = candidatos.at(0);
    solucao.push_back(noEscolhido);
    // Critério de atualização dos candidatos
    removerVizinhosDoNoEscolhidoDosCandidatos(noEscolhido, candidatos);
    removerNoDosCandidatos(noEscolhido, candidatos);
  }

  return solucao;
}

void Guloso::preencherCandidatos(std::vector<No *> &candidatos, Grafo *grafo)
{
  for (auto i = grafo->nos.begin(); i != grafo->nos.end(); i++)
  {
    No *no = *i;
    candidatos.push_back(no);
  }
}

void Guloso::ordenarCandidatosPor(std::vector<No *> &candidatos, bool (*criterio)(No *no1, No *no2))
{
  std::sort(candidatos.begin(), candidatos.end(), criterio);
}

bool Guloso::grauCrescente(No *no1, No *no2)
{
  return no1->grauSaida < no2->grauSaida;
}

void Guloso::removerVizinhosDoNoEscolhidoDosCandidatos(No *no, std::vector<No *> &candidatos)
{
  for (auto i = no->adjacentes.begin(); i != no->adjacentes.end(); i++)
  {
    No *no = *i;
    removerNoDosCandidatos(no, candidatos);
  }
}

void Guloso::removerNoDosCandidatos(No *no, std::vector<No *> &candidatos)
{
  candidatos.erase(std::remove(candidatos.begin(), candidatos.end(), no), candidatos.end());
}
