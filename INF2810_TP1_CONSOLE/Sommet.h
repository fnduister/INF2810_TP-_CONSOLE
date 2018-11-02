#pragma once
#include <vector>
#include <iostream>
#include "Arc.h"
using namespace std;

class Arc;

class Sommet
{
public:
	Sommet();
	~Sommet();
	int getId() const;
	void setId(int id);
	void setType(int type);
	void setArc(Arc* arc);

	Arc* getArc(int idAutreSommet) const;
	void ajouterArc(Arc* arc);
	bool isVisited() const;
	int getTemps(int idAutreSommet) const;
	int getType() const;
	double getGain() const;
	void setGain(double gain);
	int trouverChargedAdjacent() const;

	vector<Arc*> getArcs();

	void afficher();

private:
	int id;
	int type;
	double gain;
	vector<Arc*> arcs;
	bool visited;
};

