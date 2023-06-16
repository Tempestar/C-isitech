#include <iostream>
#include <Windows.h>
#include "Application.h"
#include "Concurrent.h"

using namespace std;

/// <summary>
/// Retourne un nombre entier genere au hasard, n,
/// avec deb <= n < fin
/// </summary>
/// <param name="deb"> la valeur minimale de n</param>
/// <param name="fin"> la valeur a laquelle n doit etre < </param>
/// <returns> n avec deb <= n < fin </returns>
int hasard(int deb, int fin)
{
	int val;
	val = (rand() % fin) + deb;
	return val;
}


/// <summary>
/// Initialiser la competition.
/// Consiste a saisir le nombre de dossards necessaires (= nombre de concurrents)
/// puis a les creer dans le conteneur dossardsPourAffectation.
/// Entre 2 et 100 dossards.
/// </summary>
void Application::InitialiserCompetition()
{
    int nombreConcurrents;

    // Demande à l'utilisateur de saisir le nombre de concurrents
    cout << "Entrez le nombre de concurrents : ";
    cin >> nombreConcurrents;

    // Vérifie que le nombre de concurrents est valide
    if (nombreConcurrents < 2 || nombreConcurrents > 100)
    {
        cout << "Nombre de concurrents invalide. Le nombre doit être compris entre 2 et 100." << endl;
        return;
    }

    // Génère les dossards pour chaque concurrent
    for (int i = 1; i <= nombreConcurrents; i++)
    {
        dossardsPourAffectation.push_back(i);
    }

    cout << "La compétition a été initialisée avec " << nombreConcurrents << " " << endl;
}


/// <summary>
/// Inscrire un concurent.
/// Apres verification qu'il reste un dossard disponible, il faut:
/// - saisir le nom du concurrent
/// - retirer 1 dossard au hasard dans le conteneur dossardsPourAffectation
/// - creer le concurrent avec son nom et le dossard
/// - ajouter le concurrent au conteneur concurentsInscrits
/// Pas d'inscription possible s'il ne reste plus de dossard disponible.
/// </summary>
void Application::InscrireUnConcurrent()
{
	//@TODO � compl�ter.
}

/// <summary>
/// Affiche la liste des concurrents inscrits, par ordre alphab�tique des noms
/// </summary>
void Application::AfficherParNom()
{
	//@TODO � compl�ter.
}

/// <summary>
/// Affiche la liste des concurrents inscrits, par ordre croissant des dossards
/// </summary>
void Application::AfficherParDossard()
{
	//@TODO � compl�ter.
}

/// <summary>
/// Permet de noter (scorer) tous les concurrents.
/// - extrait et supprime le premier concurrent du conteneur concurentsInscrits
/// - lui affecte un score entre 0 et 10 inclus
/// - insere le concurrent note dans le conteneur resultats, les mieux notes ranges en premier
/// Le score doit servir de cle pour retrouver tous les concurrents ayant un certain score.
/// Attention!! On peut avoir plusieurs concurrents avec le meme score.
/// </summary>
void Application::NoterConcurrents()
{
	//@TODO � compl�ter.
}

/// <summary>
/// Affiche le score, le dossard et le nom des concurrents not�s.
/// </summary>
void Application::AfficherResultats()
{
	//@TODO � compl�ter.
}

/// <summary>
/// Boucle d'execution du programme.
/// </summary>
void Application::Run()
{
	bool quit = false;
	int choix = 0;

	do
	{
		//  Affiche le menu et lit le choix de l'utilisateur
		menu.Affiche();
		choix = menu.SaisirEntierEntre(1, 6);

		switch(choix)	//  Realise l'action choisie par l'utilisateur
		{
		case 1:
			InscrireUnConcurrent();
			break;
		case 2:
			AfficherParNom();
			break;
		case 3:
			AfficherParDossard();
			break;
		case 4:
			NoterConcurrents();
			break;
		case 5:
			AfficherResultats();
			break;
		case 6:
			quit = true;
			break;
		}
	} while (!quit);
}
