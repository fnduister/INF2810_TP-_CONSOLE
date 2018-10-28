#pragma once
class Arc
{
public:
	Arc(int id1, int id2, int distance);
	~Arc();
	int retournerIdSommetAdjacent(int idPremierSommet);
	void ajouterSommetId(int id1, int id2);
private:
	int distance;
	int sommetIDS[2];
};

