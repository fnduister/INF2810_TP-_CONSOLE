#pragma once
#include <vector>
#include <iostream>
using namespace std;

class Arc
{
public:
	Arc(int id1, int id2, int distance);
	~Arc();
	int retournerIdSommetAdjacent(int idPremierSommet);
	void ajouterSommetId(int id1, int id2);

	void afficher();
private:
	int distance;
	int sommetIDS[2];
};

