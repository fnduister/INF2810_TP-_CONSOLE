#pragma once
#include <vector>
#include <iostream>
#include "Sommet.h"

using namespace std;

class Arc
{
public:
	Arc(Sommet* sommet1, Sommet* sommet2, int distance);
	~Arc();
	int retournerIdSommetAdjacent(int idPremierSommet);
	void ajouterSommet(Sommet* sommet1, Sommet* sommet2);

	void afficher(Sommet* sommet);
private:
	int distance;
	Sommet* sommet1;
	Sommet* sommet2;
};

