#include <iostream>
#include <string>
#include <fstream>
#include "Sommet.h"
#include "Graphe.h"
#include "Arc.h"
#include <vector> 
#include "Trajet.h"

using namespace std;
Graphe* graphe;

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
					Sommet* sommet1 = graphePrincipal->GetSommetById(stoi(vect_temp[0]));
					Sommet* sommet2 = graphePrincipal->GetSommetById(stoi(vect_temp[1]));

					Arc* nouvelArc = new Arc(sommet1, sommet2, stoi(vect_temp[2]));

					sommet1->ajouterArc(nouvelArc);
					sommet2->ajouterArc(nouvelArc);


				}
			}
			else
			{
				premierTraitement = false;
			}
		}
	}

	fichier.close();
	return graphePrincipal;
}

void LireGraphe(Graphe* graphePrincipal){
	graphePrincipal->Afficher();
}

char afficherMenu()
{
	char reponse;
	string reponses = "abcd";
	do {
		cout << "(a) Mettre à jour la carte" << endl;
		cout << "(b) Déterminer le plus court chemin sécuritaire" << endl;
		cout << "(c) Extraire un sous-graphe" << endl;
		cout << "(d) Quitter" << endl;
		cout << "votre choix: " << endl;
		cin >> reponse;
	} while (reponses.find(reponse) == string::npos);
	return reponse;
}

void mettreAjourCarte()
{
		string nomFichier = "centresLocaux.txt";
		std::cout << "entrer le nom du fichier svp:\n";
	/*	std::cin >> nomFichier;*/

		nomFichier = "centresLocaux.txt";

		graphe = CreerGraphe(nomFichier);
		cout << "votre graphe a bien ete ouvert et le voici:\n" << endl;

		LireGraphe(graphe);
}

double getTauxRecharge(int type_transport) {
	return 0;
}

void initTab(vector<Trajet*>& tab, int depart) {
	vector<Sommet*> list_sommets = graphe->GetSommets();
	for (int i = 0; i < list_sommets.size(); i++) {
		if (list_sommets[i]->getId() == depart) {
			tab.push_back(new Trajet(list_sommets[i]->getId(), 0, 0, 1, 1));
		}
		else {
			tab.push_back(new Trajet(list_sommets[i]->getId(), std::numeric_limits<int>::max(), 0, 0, 0));
		}
	}
}

int getSmallestDistanceNotVisited(vector<Trajet*> tab) {
	int min = std::numeric_limits<int>::max();
	for (int i = 0; i < tab.size(); i++) {;
		if (!tab[i]->getIsVisited() && min < tab[i]->getTemps() )
			min = tab[i]->getTemps();
	}
	return min;
}

bool IsAllVisited(vector<Trajet*> tab) {
	for (int i = 0; i < tab.size(); i++) {
		if (!tab[i]->getIsVisited())
			return false;
	}
	return true;
}

vector<Sommet*> getAdjacentsNotVisited(vector<Trajet*> tab, int id) {
	vector<Sommet*> results;
	vector<Arc*> list_arc = graphe->GetSommetById(id)->getArcs();
	for (int i = 0; i < list_arc.size(); i++) {
		if (list_arc[i]->getSommet1()->getId() == id) {
			if(isNotVisited(tab, list_arc[i]->getSommet2()->getId()))
				results.push_back(list_arc[i]->getSommet2());
		}
		else {
			if (isNotVisited(tab, list_arc[i]->getSommet1()->getId()))
				results.push_back(list_arc[i]->getSommet1());
		}
	}
}


bool isNotVisited(vector<Trajet*> tab, int id) {
	for (int i = 0; i < tab.size(); i++) {
		if (tab[i]->getId() == id)
			return false;
	}
	return true;
}




Trajet* getTrajetById(int id) {
	return nullptr;
}


void plusCourtChemin(int depart, int destination, int type_transport) {

	double taux = getTauxRecharge(type_transport);
	int current_id;

	vector<Trajet*> list_trajet;
	initTab(list_trajet, depart);

	do {
		current_id = getSmallestDistanceNotVisited(list_trajet);

		vector<Sommet*> AdjacentNotVisited = getAdjacentsNotVisited(list_trajet, current_id);

		for (int i = 0; i < AdjacentNotVisited.size(); i++) {

			Trajet* trajet = getTrajetById(AdjacentNotVisited[i]->getId());

			//

		}


	} while (IsAllVisited(list_trajet));
	
}

int main(int* argc, char* argv[]) {
	//enum VehiculeTypePosition{NIOH,MIOH};
	//enum VehiculeCategoriePosition { NIOH, MIOH };


	switch (afficherMenu())
	{
	case 'a':
		mettreAjourCarte();
		break;
	case 'b':
		break;
	default:
		break;
	}


	int pause = 0;
	std::cin >> pause;
	return 0;
}



