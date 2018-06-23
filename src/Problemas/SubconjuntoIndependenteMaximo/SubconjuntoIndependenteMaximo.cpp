#include "./SubconjuntoIndependenteMaximo.h"

int SubconjuntoIndependenteMaximo::guloso(Grafo *grafo)
{
  std::list<No *> solucao;
  std::list<No *> candidatos = grafo->nos;
  candidatos.sort(grauCrescente);

  while(candidatos.size() > 0)
  {
    solucao.push_back(candidatos.front());
    atualizarCandidatos(candidatos);
  }

  return solucao.size();
}

bool SubconjuntoIndependenteMaximo::grauCrescente(No *no1, No *no2)
{
  return no1->grauSaida < no2->grauSaida;
}

void SubconjuntoIndependenteMaximo::atualizarCandidatos(std::list<No *> &candidatos)
{
  No *noInseridoNaSolucao = candidatos.front();
  for (auto i = noInseridoNaSolucao->adjacentes.begin();
       i != noInseridoNaSolucao->adjacentes.end();
       i++)
  {
    No *no = *i;
    candidatos.remove(no);
  }
  candidatos.remove(noInseridoNaSolucao);
}

