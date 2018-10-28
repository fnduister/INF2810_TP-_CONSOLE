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
