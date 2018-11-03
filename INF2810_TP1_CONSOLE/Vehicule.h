#pragma once
#include <string>

enum VehiculeTypePosition { NI_NH, LI_ION };
enum VehiculeCategoriePosition { FAIBLE_RISQUE, MOYEN_RISQUE, HAUT_RISQUE };

class Vehicule
{
public:
	Vehicule(int categorie = FAIBLE_RISQUE, int type = NI_NH);
	~Vehicule();

	void setType(int type);
	void setCategorie(int categorie);
	int getCategorie() const;
	void getType() const;
	std::string getStringType(int type);
	double getCurrentTauxDecharge() const;
	void setCurrentTauxDecharge(int type, int categorie);



private:
	double taux[2][3];
	int type;
	double currentTauxDecharge;
	int categorie;
};

