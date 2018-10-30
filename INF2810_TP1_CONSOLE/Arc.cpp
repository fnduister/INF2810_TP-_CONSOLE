#include "Arc.h"


Arc::Arc(Sommet* sommet1, Sommet* sommet2, int distance)
{
	this->sommet1 = sommet1;
	this->sommet2 = sommet2;
	this->distance = distance;
}


Arc::~Arc()
{
}

void Arc::ajouterSommet(Sommet* sommet1, Sommet* sommet2)
{
	this->sommet1 = sommet1;
	this->sommet2 = sommet2;
}

void Arc::afficher(Sommet* sommet)
{
	Sommet* sommetTemp = sommet;
	if (sommet->getId() != sommet1->getId()) {
		sommetTemp = sommet1;
	}

	std::cout << "([ id = " << sommetTemp->getId() << " , type = " << sommetTemp->getType() << "], Distance = " << distance << ")";
}
