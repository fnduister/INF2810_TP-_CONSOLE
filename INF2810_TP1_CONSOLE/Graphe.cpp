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

void Graphe::ajouterArc(Arc* arc)
{
	arcs.push_back(arc);
}

void Graphe::ajouterArc(Arc * arc)
{
}

Sommet* Graphe::GetSommetById(int sommetId){
	int i = 0;
	while (i<sommets.size() && sommets[i]->getId() != sommetId)
		i++;
	
	if (i == sommets.size()) return nullptr;
	return sommets[i];
}

void Graphe::Afficher(){
	for (int i = 0; i < sommets.size(); i++){
		sommets[i]->afficher();
	}
}