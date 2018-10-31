#include "Trajet.h"

Trajet::Trajet(int id, int temps, double autonomie, int id_depart, bool is_visited)
{
	this->id = id;
	this->temps = temps;
	this->autonomie = autonomie;
	this->id_depart = id_depart;
	this->is_visited = is_visited;
}

Trajet::~Trajet()
{
}

int Trajet::getId()
{
	return id;
}

int Trajet::getTemps()
{
	return temps;
}

double Trajet::getAutonomie()
{
	return autonomie;
}

int Trajet::getIdDepart()
{
	return id_depart;
}

bool Trajet::getIsVisited()
{
	return is_visited;
}

void Trajet::setId(int id)
{
	this->id = id;
}

void Trajet::setTemps(int temps)
{
	this->temps = temps;
}

void Trajet::setAutonomie(double autonomie)
{
	this->autonomie = autonomie;
}

void Trajet::setIdDepart(int id_depart)
{
	this->id_depart = id_depart;
}

void Trajet::setIsVisited(bool is_visited)
{
	this->is_visited = is_visited;
}
