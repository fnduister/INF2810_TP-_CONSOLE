#pragma once
#include <vector>
#include <iostream>
#include "Sommet.h"

class Sommet;

class Arc
{
public:
	Arc(Sommet* sommet1, Sommet* sommet2, int temps);
	~Arc();
	Sommet* retournerIdSommetAdjacent(int idPremierSommet);
	void ajouterSommet(Sommet* sommet1, Sommet* sommet2);

	void afficher(Sommet* sommet);
	int getTemps() const;

	Sommet* getSommet1();
	Sommet* getSommet2();

private:
	Sommet* sommet1;
	Sommet* sommet2;
	int temps;
};

