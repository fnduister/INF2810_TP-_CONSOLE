#include "Arc.h"

class Sommet;


Arc::Arc(Sommet* sommet1, Sommet* sommet2, int temps)
{
	this->sommet1 = sommet1;
	this->sommet2 = sommet2;
	this->temps = temps;
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
	if (sommet->getId() == sommet1->getId()) {
		sommetTemp = sommet2;
	}

	std::cout << "	([ id = " << sommetTemp->getId() << " , type = " << sommetTemp->getType() << "], Distance = " << temps << ")";
}

Sommet * Arc::getSommet1()
{
	return sommet1;
}

Sommet * Arc::getSommet2()
{
	return sommet2;
}

int Arc::getTemps() const {
	return temps;
}

Sommet* Arc::retournerSommetAdjacent(int id) const {
	if (sommet1->getId() == id)
		return sommet2;
	return sommet1;
}

