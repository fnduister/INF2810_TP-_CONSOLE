#include <iostream>
#include <string>
#include <fstream>
#include "Sommet.h";
#include "Graphe.h"
#include "Arc.h"
#include <vector> 

using namespace std;


void split(const std::string& str, vector<string>& cont,
	char delim = ',')
{
	std::size_t current, previous = 0;
	current = str.find(delim);
	while (current != std::string::npos) {
		cont.push_back(str.substr(previous, current - previous));
		previous = current + 1;
		current = str.find(delim, previous);
	}
	cont.push_back(str.substr(previous, current - previous));
}

Graphe* CreerGraphe(string nomFichier){
	ifstream fichier(nomFichier);
	if (fichier.fail()){
		do{
			std::cout << "entrer le nom d'un fichier valide svp:\n";
			std::cin >> nomFichier;
			fichier.open(nomFichier);
		} while (fichier.fail());
	}
		
	
	Graphe* graphePrincipal = new Graphe();
	std::string ligne;
	bool premierTraitement = true;

	while (!ws(fichier).eof())
	{
		while (getline(fichier, ligne))
		{

			size_t pos = 0;
			if (!ligne.empty()) {

				vector<string> vect_temp;
				split(ligne, vect_temp,
					',');

				if (premierTraitement) {
					Sommet* nouveauSommet = new Sommet();

					nouveauSommet->setId(stoi(vect_temp[0]));
					nouveauSommet->setType(stoi(vect_temp[1]));
					graphePrincipal->ajouterSommet(nouveauSommet);
				}
				else
				{
					Arc* nouvelArc = new Arc(stoi(vect_temp[0]), stoi(vect_temp[1]), stoi(vect_temp[2]));

					graphePrincipal->GetSommetById(stoi(vect_temp[0]))->ajouterArc(nouvelArc);
					graphePrincipal->GetSommetById(stoi(vect_temp[1]))->ajouterArc(nouvelArc);
				}
			}
			else
			{
				premierTraitement = false;
			}
		}
	}

	return graphePrincipal;
}

int main(int* argc, char* argv[]) {
	//enum VehiculeTypePosition{NIOH,MIOH};
	//enum VehiculeCategoriePosition { NIOH, MIOH };
	string nomFichier;

	std::cout << "entrer le nom du fichier svp:\n";
	std::cin >> nomFichier;

	Graphe* graphePrincipal = CreerGraphe(nomFichier);

	

	int pause = 0;
	std::cin >> pause;
	return 0;
}



