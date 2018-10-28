#pragma once
#include "Arc.h";
class Sommet
{
public:
	Sommet();
	~Sommet();
	int getId() const;
	void setId(int id);
	void setType(int type);
	void setArc(Arc* arc);
	int getType() const;
	int getGain() const;
private:
	int id;
	int type;
	int gain;
	Arc* arc;
};

