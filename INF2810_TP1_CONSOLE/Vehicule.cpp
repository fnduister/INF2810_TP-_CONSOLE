#include "Vehicule.h"


Vehicule::Vehicule(int categorie, int type):categorie(categorie), type(type)
{
	taux[NI_NH][FAIBLE_RISQUE] = 6.0 / 60;
	taux[NI_NH][MOYEN_RISQUE] = 12.0 / 60;
	taux[NI_NH][HAUT_RISQUE] = 48.0 / 60;
	taux[LI_ION][FAIBLE_RISQUE] = 5.0 / 60;
	taux[LI_ION][MOYEN_RISQUE] = 10.0 / 60;
	taux[LI_ION][HAUT_RISQUE] = 30.0 / 60;

}


Vehicule::~Vehicule()
{
}

void Vehicule::setType(int type)
{
	this->type = type;
}

void Vehicule::setCategorie(int categorie)
{
	this->categorie = categorie;
}

int Vehicule::getType() const
{
	return type;
}

int Vehicule::getCategorie() const
{
	return categorie;
}

std::string Vehicule::getStringType() const
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

std::string Vehicule::getStringCategorie() const
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


double Vehicule::getCurrentTauxDecharge() const {
	return taux[type][categorie];
}