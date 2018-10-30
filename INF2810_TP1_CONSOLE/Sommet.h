#pragma once
#include "Arc.h"


class Sommet
{
public:
	Sommet();
	~Sommet();
	int getId() const;
	void setId(int id);
	void setType(int type);
	void setArc(Arc* arc);

	void ajouterArc(Arc* arc);

	int getType() const;
	int getGain() const;

	void afficher();
private:
	int id;
	int type;
	int gain;
	std::vector<Arc*> arcs;

};

