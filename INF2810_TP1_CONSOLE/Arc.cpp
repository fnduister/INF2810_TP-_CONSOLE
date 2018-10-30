#include "Arc.h"


Arc::Arc(int id1, int id2, int distance)
{
	sommetIDS[0] = id1;
	sommetIDS[1] = id2;
	this->distance = distance;
}


Arc::~Arc()
{
}

void Arc::ajouterSommetId(int id1, int id2)
{
	sommetIDS[0] = id1;
	sommetIDS[1] = id2;
}

void Arc::afficher()
{
	std::cout << "(" + sommetIDS[1] << ", " << distance +  ")";
}
