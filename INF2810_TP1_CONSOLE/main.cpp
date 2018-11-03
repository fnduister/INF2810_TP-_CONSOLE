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



void split(const std::string& str, vector<string>& cont,
           char delim = ',')
{
	std::size_t current, previous = 0;
	current = str.find(delim);
	while (current != std::string::npos)
	{
		cont.push_back(str.substr(previous, current - previous));
		previous = current + 1;
		current = str.find(delim, previous);
	}
	cont.push_back(str.substr(previous, current - previous));
}

Graphe* CreerGraphe(string nomFichier)
{
	ifstream fichier(nomFichier);
	if (fichier.fail())
	{
		do
		{
			std::cout << "entrer le nom d'un fichier valide svp:\n";
			std::cin >> nomFichier;
			fichier.open(nomFichier);
		}
		while (fichier.fail());
	}


	Graphe* graphePrincipal = new Graphe();
	std::string ligne;
	bool premierTraitement = true;

	while (!ws(fichier).eof())
	{
		while (getline(fichier, ligne))
		{
			size_t pos = 0;
			if (!ligne.empty())
			{
				vector<string> vect_temp;
				split(ligne, vect_temp,
				      ',');

				if (premierTraitement)
				{
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

void LireGraphe(Graphe* graphePrincipal)
{
	graphePrincipal->Afficher();
}



Graphe* mettreAjourCarte(bool demarrageApplication = false)
{
	Graphe* graphe = new Graphe;
	string nomFichierParDefaut = "centresLocaux.txt";
	string nomFichier = "";

	if (!demarrageApplication)
	{
		std::cout << "entrer le nom du fichier svp:\n";
		std::cin >> nomFichier;
		graphe = CreerGraphe(nomFichier);
		cout << "votre graphe a bien ete ouvert et le voici:\n" << endl;
		LireGraphe(graphe);
	}
	else { graphe = CreerGraphe(nomFichierParDefaut); }
	return graphe;
}


void initTab(Graphe* graphe, vector<Trajet*>& tab, int depart)
{
	vector<Sommet*> list_sommets = graphe->GetSommets();
	for (int i = 0; i < list_sommets.size(); i++)
	{
		if (list_sommets[i]->getId() == depart)
		{
			tab.push_back(new Trajet(list_sommets[i]->getId(), 0, 100, 777, 0));
		}
		else
		{
			tab.push_back(new Trajet(list_sommets[i]->getId(), std::numeric_limits<int>::max(), 0, 0, 0));
		}
	}
}

bool IsAllVisited(vector<Trajet*> tab)
{
	for (int i = 0; i < tab.size(); i++)
	{
		if (!tab[i]->getIsVisited())
			return false;
	}
	return true;
}


Trajet* getSmallestDistanceNotVisited(vector<Trajet*> trajets)
{
	int min = std::numeric_limits<int>::max();
	Trajet* result = nullptr;
	for (Trajet* trajet : trajets)
	{
		if (!trajet->getIsVisited() && trajet->getTemps() <= min)
		{
			min = trajet->getTemps();
			result = trajet;
		}
	}
	return result;
}


vector<Sommet*> getAdjacentsNotVisited(Graphe* graphe, int id)
{
	vector<Sommet*> results;
	Sommet* sommet_temp;
	vector<Arc*> list_arc = graphe->GetSommetById(id)->getArcs();
	for (Arc* arc : list_arc)
	{
		sommet_temp = arc->retournerSommetAdjacent(id);
		if (!sommet_temp->isVisited())
		{
			results.push_back(sommet_temp);
		}
	}
	return results;
}


bool isNotVisited(vector<Trajet*> tab, int id)
{
	for (int i = 0; i < tab.size(); i++)
	{
		if (tab[i]->getId() == id)
			return false;
	}
	return true;
}


Trajet* getTrajetById(vector<Trajet*> tab, int id)
{
	for (int i = 0; i < tab.size(); i++)
	{
		if (tab[i]->getId() == id)
			return tab[i];
	}
	return nullptr;
}

string afficherChemin(vector<Trajet*>& trajets, int depart, int destination)
{
	string message;
	Trajet* current = getTrajetById(trajets, destination);
	message += to_string(current->getId());
	while (current->getId() != depart)
	{
		string temp = to_string(current->getIdDepart()) + " --> ";
		message.insert(0,temp);

		current = getTrajetById(trajets, current->getIdDepart());
	}
	return message;
}

bool plusgrandtrajet(Trajet* a, Trajet* b)
{
	return a->getTemps() > b->getTemps();
}



vector<Trajet*> dijkstra(Graphe* graphe, int depart, int destination = 777,
                         bool plusLongUniquement = false
)
{
	bool premierTypeTeste = true;
	Trajet* currentTrajet = nullptr;

	double nouveauTemps = 0, nouvelAutonomie = 0.0;
	bool recommence = true;

	vector<Trajet*> list_trajet;
	initTab(graphe, list_trajet, depart);

	bool fini = false;
	Sommet* destinationSommet = graphe->GetSommetById(destination);


	bool FirstTime = true;

	do
	{
		if (FirstTime)
		{
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

		for (Sommet* sommet : adjacentNotVisited)
		{
			Trajet* adjacentTrajet = getTrajetById(list_trajet, sommet->getId());
			double currentTrajetTemps = sommet->getArc(currentTrajet->getId())->getTemps();
			nouveauTemps = currentTrajetTemps + currentTrajet->getTemps();
			nouvelAutonomie = currentTrajet->getAutonomie() - currentTrajetTemps * graphe->getVehicule()->
				getCurrentTauxDecharge();
			if (adjacentTrajet->getTemps() > nouveauTemps)
			{
				//Si on trouve un trajet plus court alors on test pour voir si l'autonomie est toujours bonne

				if (nouvelAutonomie > 20)
				{
					adjacentTrajet->setTemps(nouveauTemps);
					adjacentTrajet->setAutonomie(nouvelAutonomie);
					adjacentTrajet->setIdDepart(currentTrajet->getId());
				}
				else
				{
					// au cas ou on veut le plus long chemin uniquement on n'arrete la recherche au dessus de 20% d'autonomie.
					if (destinationSommet)
					{
						if (currentSommet->getType())
						{
							// Si nous somme sur un sommet qui peut charger alors on charge directement ici.
							nouvelAutonomie = 100 - currentTrajetTemps * graphe->getVehicule()->getCurrentTauxDecharge();
							sommet->setGain(100 - currentTrajet->getAutonomie());
							adjacentTrajet->setTemps(nouveauTemps);
							adjacentTrajet->setAutonomie(nouvelAutonomie);
							adjacentTrajet->setIdDepart(currentTrajet->getId());
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
									altAutonomie = 100 - currentSommet->getArc(procheAdjacentIdCharged)->getTemps()
										* graphe->getVehicule()->getCurrentTauxDecharge();

									//on ajoute le temps supplementaire necessaire a la recharge
									altTemps = 120 + precedentTrajet->getTemps() + currentSommet
									                                               ->getArc(procheAdjacentIdCharged)
									                                               ->getTemps();

									//ajouter au tableau des trajets
									list_trajet.push_back(
										new Trajet(altId, altTemps, altAutonomie, procheAdjacentIdCharged, true));
									alternativeCreated = true;
								}
								//Assignation de ce trajet dans notre prochain trajet.
								nouveauTemps = currentTrajetTemps + altTemps;
								nouvelAutonomie = altAutonomie - currentTrajetTemps * graphe->getVehicule()->
									getCurrentTauxDecharge();
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
	}
	while (!IsAllVisited(list_trajet) && !fini && currentTrajet);
	return list_trajet;
}


void extraireSousGraphe(Graphe* graphe, int& depart, int categorie, int type)
{
	string infoTrajet;
	graphe->setVehicule(new Vehicule(categorie, type));
	vector<Trajet*> trajets = dijkstra(graphe, depart);
	Trajet* plusLongTrajet = nullptr;
	std::sort(trajets.begin(), trajets.end(), plusgrandtrajet);

	for (Trajet* trajet : trajets)
	{
		if (trajet->getTemps() != std::numeric_limits<int>::max()) {
			plusLongTrajet = trajet;
			break;
		}
	}

	infoTrajet += "\nType de vehicule: " + graphe->getVehicule()->getStringType() + "\n";
	infoTrajet += "Categorie de vehicule demande : " + graphe->getVehicule()->getStringCategorie() + "\n";
	infoTrajet += "Le trajet se fait en : " + to_string(plusLongTrajet->getTemps()) + "\n";
	infoTrajet += "Avec une autonomie finale de : " + to_string(plusLongTrajet->getAutonomie()) + "\n";
	infoTrajet += afficherChemin(trajets, depart, plusLongTrajet->getId());

	cout << infoTrajet;
	cout << "\n\n\n\n\n\n\n\n";
}

void prendreInformationsPlusLongChemin(Graphe* graphe, int& depart, int& categorie, int& type)
{
	int choix;
	do
	{
		cout << "- point d'origine: ";
		cin >> depart;
		cout << endl;
	}
	while (!graphe->GetSommetById(depart));

	cout << endl;

	do
	{
		cout << "Choisissez la categorie de transport que vous voulez" << endl;
		cout << " 1 - Haut risque \n 2 - Moyen risque \n 3 - Faible risque \n ";
		cout << "votre choix: ";
		cin >> choix;

		switch (choix)
		{
		case 1:
			categorie = HAUT_RISQUE;
			break;
		case 2:
			categorie = MOYEN_RISQUE;
			break;
		case 3:
			categorie = FAIBLE_RISQUE;
			break;
		default:
			cout << "votre choix n'est pas valide" << endl;
			choix = 4;
			break;
		}

		cout << endl;
	} while (choix == 4);


	do
	{
		cout << "Choisissez le type de transport que vous voulez" << endl;
		cout << " 1 - LI-ION \n 2 - NI_NH \n ";
		cout << "votre choix: ";
		cin >> choix;

		switch (choix)
		{
		case 1:
			type = LI_ION;
			break;
		case 2:
			type = NI_NH;
			break;
		default:
			cout << "votre choix n'est pas valide" << endl;
			choix = 4;
			break;
		}
		cout << endl;

	} while (choix == 4);

}

void prendreInformationsPlusCourtChemin(Graphe* graphe, int& depart, int& destination, int& categorie)
{
	int choix;
	do
	{
		cout << "- point d'origine: ";
		cin >> depart;
		cout << endl;
	} while (!graphe->GetSommetById(depart));

	do
	{
		cout << "- point de destination: ";
		cin >> destination;
		cout << endl;
	} while (!graphe->GetSommetById(destination));

	do
	{
		cout << "Choisissez la categorie de transport que vous voulez" << endl;
		cout << " 1 - Haut risque \n 2 - Moyen risque \n 3 - Faible risque \n ";
		cout << "votre choix: ";
		cin >> choix;

		switch (choix)
		{
		case 1:
			categorie = HAUT_RISQUE;
			break;
		case 2:
			categorie = MOYEN_RISQUE;
			break;
		case 3:
			categorie = FAIBLE_RISQUE;
			break;
		default:
			cout << "votre choix n'est pas valide" << endl;
			choix = 4;
			break;
		}
	} while (choix == 4);

	cout << endl;
}

void plusCourtChemin(Graphe* graphe, int& depart, int& destination, int& categorie)
{
	bool besoinPlusEnergie = false;
	int type = NI_NH;
	string message, infoTrajet;
	Sommet* destinationSommet = graphe->GetSommetById(destination);

	graphe->getVehicule()->setCategorie(categorie);
	vector<Trajet*> trajets = dijkstra(graphe, depart, destination);
	Trajet* destinationTrajet = getTrajetById(trajets, destination);

	if (destinationSommet->isVisited()) {
		message = afficherChemin(trajets, depart, destination);
	}
	else {
		graphe->getVehicule()->setType(LI_ION);
		trajets = dijkstra(graphe, depart, destination);
		besoinPlusEnergie = true;
		if (destinationSommet->isVisited()) {
			message = afficherChemin(trajets, depart, destination);
			type = LI_ION;
		}
	}
	infoTrajet += "\n\nType de vehicule: " + graphe->getVehicule()->getStringType() + "\n";
	infoTrajet += "Categorie de vehicule demande : " + graphe->getVehicule()->getStringCategorie() + "\n";

	if (destinationSommet->isVisited()) {
		infoTrajet += "Le trajet se fait en : " + to_string(destinationTrajet->getTemps()) + "\n";
		infoTrajet += "Avec une autonomie finale de : " + to_string(destinationTrajet->getAutonomie()) + "\n";
		infoTrajet += afficherChemin(trajets, depart, destination);
	}
	else
	{
		infoTrajet += "Type de vehicule: " + graphe->getVehicule()->getStringType() + "\n";
		infoTrajet += "Categorie de vehicule demande : " + graphe->getVehicule()->getStringCategorie() + "\n";
		infoTrajet += "desole mais malheureusement on ne peut pas vous deservir car c'est trop loin";
	}
	cout << infoTrajet;
	cout << "\n\n\n\n\n\n\n\n";

}

void afficherMenu()
{
	Graphe* graphe = mettreAjourCarte(true);
	int depart = 0, destination = 0, categorie_transport = HAUT_RISQUE, type_transport = NI_NH;
	graphe->setVehicule(new Vehicule(NI_NH, FAIBLE_RISQUE));

	char reponse;
	string reponses = "abcd";
	do
	{
		cout << "(a) Mettre a jour la carte" << endl;
		cout << "(b) Determiner le plus court chemin securitaire" << endl;
		cout << "(c) Extraire un sous-graphe" << endl;
		cout << "(d) Quitter" << endl;
		cout << "votre choix: ";
		cin >> reponse;
	} while (reponses.find(reponse) == string::npos);

	switch (reponse)
	{
	case 'a':
		graphe = mettreAjourCarte();
		break;
	case 'b':
		prendreInformationsPlusCourtChemin(graphe, depart, destination, categorie_transport);
		plusCourtChemin(graphe, depart, destination, categorie_transport);
		break;
	case 'c':
		prendreInformationsPlusLongChemin(graphe, depart, categorie_transport, type_transport);
		extraireSousGraphe(graphe, depart, categorie_transport, type_transport);
		break;
	case 'd':
		cout << "a la prochaine";
	default:
		break;
	}
	if(reponse != 'd')
		afficherMenu();
}

int main(int* argc, char* argv[])
{
	afficherMenu();
	return 0;
}
