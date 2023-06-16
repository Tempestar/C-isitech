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
    // Vérifie s'il reste des dossards disponibles
    if (dossardsPourAffectation.empty())
    {
        cout << "Il n'y a plus de dossards disponibles." << endl;
        return;
    }

    string nomConcurrent;
    int dossard;

	// Saisie du nom du concurrent
    cout << "Entrez le nom du concurrent : ";
    cin >> nomConcurrent;

    // Retire un dossard au hasard du conteneur dossardsPourAffectation
    int indexDossard = hasard(0, dossardsPourAffectation.size());
    dossard = dossardsPourAffectation[indexDossard];
    dossardsPourAffectation.erase(dossardsPourAffectation.begin() + indexDossard);

    // Instanciation du concurrent avec son nom et le dossard récupéré
    Concurrent concurrent(nomConcurrent, dossard);

    // Ajout du concurrent au conteneur concurrentsInscrits
    concurrentsInscrits.push_back(concurrent);

    // Affichage du concurrent instancié (nom et dossard)
    cout << "Concurrent inscrit : " << concurrent.getNom() << " (Dossard : " << concurrent.getDossard() << ")" << endl;

    // Affichage du nombre de dossards disponibles
    cout << "Nombre de dossards disponibles : " << dossardsPourAffectation.size() << endl;
}

/// <summary>
/// Affiche la liste des concurrents inscrits, par ordre alphabetique des noms
/// </summary>
void Application::AfficherParNom()
{
	// Trie les concurrents par ordre alphabétique des noms
    sort(concurrentsInscrits.begin(), concurrentsInscrits.end(), [](const Concurrent& c1, const Concurrent& c2) {
        return c1.getNom() < c2.getNom();
    });

	// Affiche les concurrents inscrits par ordre alphabétique des noms
    cout << "Liste des concurrents inscrits par ordre alphabétique des noms :" << endl;
    for (const Concurrent& concurrent : concurrentsInscrits)
    {
        cout << "Nom: " << concurrent.getNom() << " - Dossard: " << concurrent.getDossard() << endl;
    }
}

/// <summary>
/// Affiche la liste des concurrents inscrits, par ordre croissant des dossards
/// </summary>
void Application::AfficherParDossard()
{
	// Vérifie s'il n'y a pas de concurrent inscrit
    if (concurrentsInscrits.empty())
    {
        cout << "Aucun concurrent inscrit." << endl;
        return;
    }

	// Trie les concurrents par dossard en ordre croissant
    sort(concurrentsInscrits.begin(), concurrentsInscrits.end(), [](const Concurrent& c1, const Concurrent& c2) {
        return c1.GetDossard() < c2.GetDossard();
    });

	// Affiche la liste des concurrents par dossard
    cout << "Liste des concurrents inscrits par dossard :" << endl;
    for (const Concurrent& concurrent : concurrentsInscrits)
    {
        cout << "Dossard : " << concurrent.GetDossard() << ", Nom : " << concurrent.GetNom() << endl;
    }
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
    // Parcourt les concurrents inscrits dans leur ordre d'inscription
    while (!concurrentsInscrits.empty())
    {
        // Récupère le premier concurrent
        Concurrent concurrent = concurrentsInscrits.front();
        concurrentsInscrits.pop_front();

        // Affecte un score aléatoire entre 0 et 10 inclus
        int score = hasard(0, 11);

        // Insère le concurrent noté dans le conteneur resultat
        auto it = lower_bound(resultats.begin(), resultats.end(), score, [](const Concurrent& c, int s) {
            return c.getScore() > s;
        });
        resultats.insert(it, concurrent.setScore(score));
    }

    cout << "Tous les concurrents ont été notés et insérés dans le conteneur 'resultats'." << endl;
}


/// <summary>
/// Affiche le score, le dossard et le nom des concurrents not�s.
/// </summary>
void Application::AfficherResultats()
{
    // Vérifie s'il n'y a pas de résultats
    if (resultats.empty())
    {
        cout << "Aucun résultat à afficher." << endl;
        return;
    }

    // Trie les résultats par score en ordre décroissant
    sort(resultats.begin(), resultats.end(), [](const Concurrent& c1, const Concurrent& c2) {
        return c1.GetScore() > c2.GetScore();
    });

    // Affiche les résultats
    cout << "Résultats de la compétition :" << endl;
    for (const Concurrent& concurrent : resultats)
    {
        cout << "Score : " << concurrent.GetScore() << ", Dossard : " << concurrent.GetDossard() << ", Nom : " << concurrent.GetNom() << endl;
    }
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
