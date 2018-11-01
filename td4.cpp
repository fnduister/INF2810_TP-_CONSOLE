#include <string>
#include <fstream>
#include <iostream>

#include <cstdint>
#include <cmath>
#include "ecrireimage.h"
#include <ctime>

using namespace std;

double borneDansIntervalle(double b_min, double b_max, double borne)
{

	double valeur;
	if (borne < b_min) {
		valeur = b_min;
	}
	if (borne > b_max) {
		valeur = b_max;
	}
	if (borne >= b_min && borne < b_max) {
		valeur = borne;
	}
	return valeur;
}

// estDansIntervalle

bool estDansIntervalle(double b_min, double b_max, double borne)
{

	bool valeur = false;

	if (borne >= b_min && borne < b_max) {
		valeur = true;
	}
	return valeur;
}



// dessinePoint

void dessinePoint(double x, double y, int intensite, Pixel image[tailleX][tailleY])
{

	image[int(x)][int(y)] -= intensite;
	borneDansIntervalle(0, 255, image[int(x)][int(y)]);


}

// aleatoireZeroUn

double aleatoireZeroUn()
{
	/*srand(time(NULL));
	double x = rand() % 0 + 0.9;
	return x;*/

	srand(time(NULL)); //generates random seed val

	double f = (double)rand() / RAND_MAX;
	return 0 + f * (1 - 0);
}

/* //deuxieme solution possible //
double aleatoireZeroUn()
{


{ srand(unsigned (time(NULL)));
double nombre_aleatoire = (rand() * 1 / 0.9);
return nombre_aleatoire ;

}

}

*/

// transformePoint

//void transformePoint(double x, double y,transformation[][])
int main() {

	//test
	cout << borneDansIntervalle(10, 20, 15) << "\n";
	cout << borneDansIntervalle(10, 20, 25) << "\n";
	cout << borneDansIntervalle(10, 20, 5) << "\n";
	

	//Test appel fonction
	cout << aleatoireZeroUn() << "\n";
	
	return 0;
}
