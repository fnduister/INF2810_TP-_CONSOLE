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

vector<Arc*> Sommet::getArcs()
{
	return arcs;
}

Arc* Sommet::getArc(int idAutreSommet) const {
	for (Arc* arc : arcs) {
		if (arc->getSommet1()->getId() == idAutreSommet || arc->getSommet2()->getId() == idAutreSommet)
			return arc;
	}
	return nullptr;
}

void Sommet::afficher()
{
	std::cout << "([ id = " << id << " , type = " << type << "] \n";

	for (int i = 0; i < arcs.size(); i++) {
		arcs[i]-> afficher(this);

		if (i != arcs.size() - 1)
			std::cout << ", " << "\n";
	}

	std::cout << ")" << "\n";
}

int Sommet::getTemps(int idAutreSommet) const {
	return getArc(idAutreSommet)->getTemps;
}

void Sommet::setType(int type)
{
	this->type = type;
}

bool Sommet::isVisited() const {
	return visited;
}

Sommet::~Sommet()
{
}
