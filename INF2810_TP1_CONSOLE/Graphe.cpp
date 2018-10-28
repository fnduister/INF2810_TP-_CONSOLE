#include "Graphe.h"



Graphe::Graphe()
{
}


Graphe::~Graphe()
{
}

void Graphe::ajouterSommet(Sommet* sommet)
{
	sommets.push_back(sommet);
}

Sommet* Graphe::GetSommetById(int sommetId){
	int i = 0;
	while (i<sommets.size() && sommets[i]->getId() != sommetId)
		i++;
	
	if (i == sommets.size()) return nullptr;
	return sommets[i];
}