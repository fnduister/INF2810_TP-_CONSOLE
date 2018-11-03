#include "Vehicule.h"


Vehicule::Vehicule(int categorie, int type = NI_NH)
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
	switch (type)
	{
	case 0:
		this->type = "NI_NH";
		break;
	case 1:
		this->type = "LI-ION";
		break;
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