#pragma once
#include <vector>
#include "Sommet.h"

class Graphe
{
public:
	Graphe();
	~Graphe();
	void ajouterSommet(Sommet* sommet);
	Sommet* GetSommetById(int sommetId);
private:
	std::vector<Sommet*> sommets;
};

