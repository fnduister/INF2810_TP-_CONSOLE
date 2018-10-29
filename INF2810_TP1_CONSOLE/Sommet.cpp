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

void Sommet::setType(int type)
{
	this->type = type;
}


Sommet::~Sommet()
{
}
