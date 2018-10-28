#pragma once
class Arc
{
public:
	Arc();
	~Arc();
	int retournerIdSommetAdjacent(int idPremierSommet);
	void ajouterSommetId(int id1, int id2);
private:
	int distance;
	int sommetIDS[2];
};

