#include "Vehicule.h"


Vehicule::Vehicule(int categorie, int type)
{
	taux[NI_NH][FAIBLE_RISQUE] = 6/60;
	taux[NI_NH][MOYEN_RISQUE] = 12 / 60;
	taux[NI_NH][HAUT_RISQUE] = 48 / 60;
	taux[LI_ION][FAIBLE_RISQUE] = 5 / 60;
	taux[LI_ION][MOYEN_RISQUE] = 10 / 60;
	taux[LI_ION][HAUT_RISQUE] = 30 / 60;
	currentTauxDecharge = taux[type][categorie];
}


Vehicule::~Vehicule()
{
}

void Vehicule::setType(int type)
{
	this->type = type;
}

std::string Vehicule::getStringType(int type)
{
	switch (type)
	{
	case 0:
		return "NI_NH";
	case 1:
		return "LI-ION";
	default:
		break;
	}
}

std::string Vehicule::getStringCategorie(int categorie)
{
	switch (categorie)
	{
	case 0:
		return "FAIBLE RISQUE";
	case 1:
		return "MOYEN RISQUE";
	case 2:
		return "HAUT RISQUE";
	default:
		break;
	}
}

void Vehicule::setCurrentTauxDecharge(int type, int categorie)
{
	currentTauxDecharge = taux[type][categorie];
}

std::string Vehicule::getType() const
{
	return type;
}

double Vehicule::getCurrentTauxDecharge() const {
	return currentTauxDecharge;
}