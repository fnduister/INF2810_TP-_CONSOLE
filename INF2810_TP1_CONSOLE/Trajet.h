#pragma once

class Trajet
{
public:
	Trajet(int id, int temps, double autonomie, int id_depart, bool is_visited);
	~Trajet();
	
	int getId();
	int getTemps();
	double getAutonomie();
	int getIdDepart();
	bool getIsVisited();

	void setId(int id);
	void setTemps(double temps);
	void setAutonomie(double autonomie);
	void setIdDepart(int id_depart);
	void setIsVisited(bool is_visited);


private:
	int id;
	double temps;
	double autonomie;
	int id_depart;
	bool is_visited;
};