#include "Sommet.h"


Sommet::Sommet()
{
}

int Sommet::getId() const {
	return id;
}

void Sommet::setId(int id) {
	this->id = id;
}

void Sommet::ajouterArc(Arc* arc)
{
	arcs.push_back(arc);
}

int Sommet::getType() const
{
	return type;
}

int Sommet::getGain() const
{
	return gain;
}

void Sommet::afficher()
{
	std::cout << "([ id = " << id << " , type = " << type << "]";

	for (int i = 0; i < arcs.size(); i++) {
		/*arcs[i]->afficher(this);*/

		if (i != arcs.size() - 1)
			std::cout << ", ";
	}

	std::cout << ")" << "\n";
}

void Sommet::setType(int type)
{
	this->type = type;
}


Sommet::~Sommet()
{
}
