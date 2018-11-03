#include <iostream>
#include <string>
#include <fstream>
#include "Sommet.h"
#include "Graphe.h"
#include "Arc.h"
#include <vector> 
#include "Trajet.h"
#include <algorithm>
#include "Vehicule.h"

using namespace std;

enum VehiculeCategoriePosition { FAIBLE_RISQUE, MOYEN_RISQUE, HAUT_RISQUE };
enum VehiculeTypePosition { NI_NH, LI_ION };


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

Graphe* CreerGraphe(string nomFichier) {


	ifstream fichier(nomFichier);
	if (fichier.fail()) {
		do {
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

void LireGraphe(Graphe* graphePrincipal) {
	graphePrincipal->Afficher();
}

char afficherMenu()
{
	char reponse;
	string reponses = "abcd";
	do {
		cout << "(a) Mettre a jour la carte" << endl;
		cout << "(b) Determiner le plus court chemin securitaire" << endl;
		cout << "(c) Extraire un sous-graphe" << endl;
		cout << "(d) Quitter" << endl;
		cout << "votre choix: " << endl;
		cin >> reponse;
	} while (reponses.find(reponse) == string::npos);
	return reponse;
}

Graphe* mettreAjourCarte(bool demarrageApplication = false)
{
	Graphe* graphe = new Graphe;
	string nomFichierParDefaut = "centresLocaux.txt";
	string nomFichier = "";

	if (!demarrageApplication) {
		std::cout << "entrer le nom du fichier svp:\n";
		graphe = CreerGraphe(nomFichier);
		cout << "votre graphe a bien ete ouvert et le voici:\n" << endl;
		std::cin >> nomFichier;
		LireGraphe(graphe);
	}
	else { graphe = CreerGraphe(nomFichierParDefaut); }
	return graphe;
}


void initTab(Graphe* graphe, vector<Trajet*>& tab, int depart) {
	vector<Sommet*> list_sommets = graphe->GetSommets();
	for (int i = 0; i < list_sommets.size(); i++) {
		if (list_sommets[i]->getId() == depart) {
			tab.push_back(new Trajet(list_sommets[i]->getId(), 0, 100, 777, 0));
		}
		else {
			tab.push_back(new Trajet(list_sommets[i]->getId(), std::numeric_limits<int>::max(), 0, 0, 0));
		}
	}
}

bool IsAllVisited(vector<Trajet*> tab) {
	for (int i = 0; i < tab.size(); i++) {
		if (!tab[i]->getIsVisited())
			return false;
	}
	return true;
}


Trajet* getSmallestDistanceNotVisited(vector<Trajet*> trajets) {
	int min = std::numeric_limits<int>::max();
	Trajet* result = nullptr;
	for (Trajet* trajet : trajets) {

		if (!trajet->getIsVisited() &&  trajet->getTemps() <= min) {
			min = trajet->getTemps();
			result = trajet;
		}
	}
	return result;
}


vector<Sommet*> getAdjacentsNotVisited(Graphe* graphe, int id) {
	vector<Sommet*> results;
	Sommet* sommet_temp;
	vector<Arc*> list_arc = graphe->GetSommetById(id)->getArcs();
	for (Arc* arc : list_arc) {
		sommet_temp = arc->retournerSommetAdjacent(id);
		if (!sommet_temp->isVisited()) {
			results.push_back(sommet_temp);
		}
	}
	return results;
}




bool isNotVisited(vector<Trajet*> tab, int id) {
	for (int i = 0; i < tab.size(); i++) {
		if (tab[i]->getId() == id)
			return false;
	}
	return true;
}


Trajet* getTrajetById(vector<Trajet*> tab, int id) {
	for (int i = 0; i < tab.size(); i++) {
		if (tab[i]->getId() == id)
			return tab[i];
	}
	return nullptr;
}

void afficherChemin(vector<Trajet*>& trajets, int depart, int destination)
{
	Trajet* current = getTrajetById(trajets, destination);
	int initialId = depart;
	cout << current->getId();
	while (current->getId() != depart)
	{
		cout << " <-- " << current->getIdDepart();
		current = getTrajetById(trajets, current->getIdDepart());
	}

}

bool plusgrandtrajet( Trajet* a, Trajet* b)
{
	return a->getTemps() > b->getTemps();
}

Trajet* extraireSousGraphe(vector<Trajet*>& trajets, int depart)
{
	std::sort(trajets.begin(), trajets.end(), plusgrandtrajet);
	Trajet* trajetLePlusLong;
	for(Trajet* trajet : trajets)
	{
		if (trajet->getTemps() != std::numeric_limits<int>::max())
			return trajet;
	}
}

void plusCourtChemin(Graphe* graphe, int depart, int categorie, int type = NI_NH, bool plusLongUniquement = false, int destination = 777) {
	Vehicule* vehicule = new Vehicule(type, categorie);
	bool premierTypeTeste = true;
	Trajet* currentTrajet = nullptr;

	double nouveauTemps = 0, nouvelAutonomie = 0.0;

	vector<Trajet*> list_trajet;
	initTab(graphe, list_trajet, depart);

	bool fini = false;
	Sommet* destinationSommet = graphe->GetSommetById(destination);


	bool FirstTime = true;
	do{
		do {

		if (FirstTime) {
			currentTrajet = getTrajetById(list_trajet, depart);
			FirstTime = false;
		}

		Sommet* currentSommet = graphe->GetSommetById(currentTrajet->getId());

		if (currentSommet->getId() == 23)
			int pausebro = 5;

		vector<Sommet*> adjacentNotVisited = getAdjacentsNotVisited(graphe, currentTrajet->getId());

		//variables necessaire pour la creation d'un trajet alternatif;
		bool alternativeCreated = false;
		int altId = 0, altTemps = 0;
		double altAutonomie = 0.0;

		for (Sommet* sommet : adjacentNotVisited) {

			Trajet* adjacentTrajet = getTrajetById(list_trajet, sommet->getId());
			double currentTrajetTemps = sommet->getArc(currentTrajet->getId())->getTemps();
			nouveauTemps = currentTrajetTemps + currentTrajet->getTemps();
			nouvelAutonomie = currentTrajet->getAutonomie() - currentTrajetTemps * vehicule->getCurrentTauxDecharge();
			if (adjacentTrajet->getTemps() > nouveauTemps) {
				//Si on trouve un trajet plus court alors on test pour voir si l'autonomie est toujours bonne

				if (nouvelAutonomie > 20) {

					adjacentTrajet->setTemps(nouveauTemps);
					adjacentTrajet->setAutonomie(nouvelAutonomie);
					adjacentTrajet->setIdDepart(currentTrajet->getId());

				}
				else {
					// au cas ou on veut le plus long chemin uniquement on n'arrete la recherche au dessus de 20% d'autonomie.
					if (!plusLongUniquement) {
						if (currentSommet->getType())
						{
							// Si nous somme sur un sommet qui peut charger alors on charge directement ici.
							nouvelAutonomie = 100 - currentTrajetTemps * vehicule->getCurrentTauxDecharge();
							sommet->setGain(100 - currentTrajet->getAutonomie());
						}
						else
						{
							//Si nous somme sur un sommet qui ne peut pas charger, on doit alors 
							//chercher autour de lui pour voir si on a une charge avant
							Sommet* precedentSommet = currentSommet->trouverChargedAdjacent();
							if (precedentSommet != nullptr)
							{
								int procheAdjacentIdCharged = precedentSommet->getId();

								if (!alternativeCreated)
								{
									//creation d'un trajet alternatif

									Trajet* precedentTrajet = getTrajetById(list_trajet, procheAdjacentIdCharged);
									altId = currentSommet->getId() + 100;

									//on ajoute le gain d'energie qui s'est fait a cette hopital ainsi que la nouvelle autonomie l'hopital actuel
									precedentSommet->setGain(100 - precedentTrajet->getAutonomie());
									altAutonomie = 100 - currentSommet->getArc(procheAdjacentIdCharged)->getTemps() * vehicule->getCurrentTauxDecharge();

									//on ajoute le temps supplementaire necessaire a la recharge
									altTemps = 120 + precedentTrajet->getTemps() + currentSommet->getArc(procheAdjacentIdCharged)->getTemps();

									//ajouter au tableau des trajets
									list_trajet.push_back(new Trajet(altId, altTemps, altAutonomie, procheAdjacentIdCharged, true));
									alternativeCreated = true;
								}
								//Assignation de ce trajet dans notre prochain trajet.
								nouveauTemps = currentTrajetTemps + altTemps;
								nouvelAutonomie = altAutonomie - currentTrajetTemps * vehicule->getCurrentTauxDecharge();
								adjacentTrajet->setTemps(nouveauTemps);
								adjacentTrajet->setAutonomie(nouvelAutonomie);
								adjacentTrajet->setIdDepart(altId);
							}
						}
					}
				}
			}
		}

		currentTrajet->setIsVisited(true);
		currentSommet->changeVisibility();

		// 1er etape de dijkstra: trouver le trajet avec la plus petite distance
		currentTrajet = getSmallestDistanceNotVisited(list_trajet);

		if (destinationSommet)
			fini = destinationSommet->isVisited();
		//;
	} while (!IsAllVisited(list_trajet) && !fini && currentTrajet);
	if (!destinationSommet->isVisited() && premierTypeTeste)
		vehicule->setCurrentTauxDecharge(LI_ION, categorie);
	} while (recommence);
	afficherChemin(list_trajet, depart, destination);
}


void prendreInformationsPlusLongChemin(Graphe* graphe, int &depart, int &type_transport)
{
	int choix;
	do {
		cout << "- point d'origine: ";
		cin >> depart; cout << endl;
	} while (!graphe->GetSommetById(depart));

	cout << endl;

	do
	{
		cout << "Choisissez la categorie de transport que vous voulez" << endl;
		cout << " 1 - Haut risque \n 2 - Moyen risque \n 3 - Faible risque \n ";
		cin >> choix;

		switch (choix)
		{
		case 1:
			type_transport = HAUT_RISQUE;
			break;
		case 2:
			type_transport = MOYEN_RISQUE;
			break;
		case 3:
			type_transport = FAIBLE_RISQUE;
			break;
		default:
			cout << "votre choix n'est pas valide" << endl;
			choix = 4;
			break;
		}
	} while (choix == 4);
}

void prendreInformationsPlusCourtChemin(Graphe* graphe, int &depart, int &destination, int &type_transport)
{
	do {
		cout << "- point de destination: ";
		cin >> destination; cout << endl;
	} while (!graphe->GetSommetById(destination));

	cout << endl;

	prendreInformationsPlusLongChemin(graphe, depart, type_transport);


}


int main(int* argc, char* argv[]) {
	Graphe* graphe = mettreAjourCarte(true);
	int depart = 0, destination = 0, categorie_transport = HAUT_RISQUE;

	switch (afficherMenu())
	{
	case 'a':
		graphe = mettreAjourCarte();
		break;
	case 'b':
		prendreInformationsPlusCourtChemin(graphe, depart, destination, categorie_transport);
		plusCourtChemin(graphe, depart, destination, categorie_transport);
		break;
	case 'c':
		prendreInformationsPlusLongChemin(graphe, depart, categorie_transport);
		plusCourtChemin(graphe, 28, 1, 1);
		break;
	case 'd':
		cout << "a la prochaine";
	default:
		break;
	}

	int pause = 0;
	std::cin >> pause;
	return 0;
}