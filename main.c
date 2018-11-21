// On rajoute les bibliothèques "standards" à notre programme C
#include <stdio.h>
#include <stdlib.h>

// Définition d'une fonction pour trouver le maximum entre deux valeurs
#define MAX(a,b) ((a) > (b) ? a : b)

// Définition de la taille de la mémoire du processeur Cardiac
#define taille 100

// On définit l'accumulateur et le compteur ordinal comme des variables globales
int acc = 0;
int co = 0;

// On définit le pointeur (tableau) qui définira la mémoire
int* memoire;

// Cette fonction sert à remplir la mémoire du cardiac avec les données de bases
// 001 pour la case 00
// 800 pour la case 99
// 1000 pour les cases "vides" (hors définition)
void chargement_bande() {
	for (int i=0;i<taille;++i) {
		if (i == 0) {
            		memoire[i] = 001;
		} else if (i == taille-1) {
		    	memoire[i] = 800;
		} else {
            		memoire[i] = 1000;
		}
	}
}

// Fonction pour agir comme le "INPUT" (0) du Cardiac
void INP(int adresse) {
	int nbr = 0;
	printf("INP: ");
	scanf("%d", &nbr);
	memoire[adresse] = nbr;
}

// Fonction pour agir comme le "OUTPUT" (1) du Cardiac
void OUT(int adresse) {
	int nbr = memoire[adresse];
	printf("OUT: %d\n", nbr);
}

// Fonction pour agir comme le "LOAD TO ACC" (2) du Cardiac
void LDA(int adresse) {
	acc = memoire[adresse];
}

// Fonction pour agir comme le "LOAD INDIRECT" (3) du Cardiac
void LDI(int adresse) {
	acc = memoire[memoire[adresse]%100];
}

// Fonction pour agir comme le "STORE FROM ACC" (4) du Cardiac
void STA(int adresse) {
	memoire[adresse] = acc%1000;
}

// Fonction pour agir comme le "STORE INDIRECT" (5) du Cardiac
void STI(int adresse) {
	memoire[memoire[adresse]%100] = acc%1000;
}

// Fonction pour agir comme le "ADD" (6) du Cardiac
void ADD(int adresse) {
	acc = (acc + memoire[adresse])%10000;
}

// Fonction pour agir comme le "SUB" (7) du Cardiac
void SUB(int adresse) {
	acc = MAX(acc - memoire[adresse], 0);
}

// Fonction pour agir comme le "JUMP IF ACC IS ZERO" (8) du Cardiac
void JAZ(int adresse) {
	if (acc == 0) {
		memoire[99] = co + 800;
		co = adresse;
	} else {
        	++co;
	}
}

// Fonction pour agir comme le "HALT AND RESET" (9) du Cardiac
void HRS() {
	co = 0;
	acc = 0;
}

// Cette fonction s'occupe de la lecture du programme inscrit dans la mémoire du Cardiac
int lecture() {
   	// Boucle infinie
	while (1) {
        	// La boucle se termine si le compteur ordinal dépasse la dernière case de la mémoire
	    	if (co > taille-1) {
            		return -1;
	    	}

        	// Permet de récupérer les infos de la case mémoire actuelle en deux parties:
        	// La clef :    X__ (premier des 3 chiffres)
        	// L'adresse :  _XX (les deux autres chiffres)
	  	int adresse = memoire[co]%100;
		int clef = memoire[co]/100;

       		// Le switch permet de comparer avec la clef avec les différentes possibilités pour celle-ci
		switch (clef) {
        	case 9:
           		HRS();
			// On interrompt la fonction 
            		return 0;
        	case 8:
            		JAZ(adresse);
           		break;
        	case 7:
            		SUB(adresse);
            		++co;
            		break;
        	case 6:
           		ADD(adresse);
           		++co;
            		break;
        	case 5:
            		STI(adresse);
			++co;
			break;
        	case 4:
            		STA(adresse);
			++co;
			break;
        	case 3:
            		LDI(adresse);
			++co;
			break;
        	case 2:
            		LDA(adresse);
			++co;
			break;
        	case 1:
            		OUT(adresse);
			++co;
			break;
        	case 0:
            		INP(adresse);
			++co;
			break;
       		// Si la clef n'est aucune des possibilités, on renvoie une valeur négative, pour montrer que ça a merdé
        	default:
            		return -1;
		}
	}
}

// La fonction principale
int main() {
    	// On alloue la mémoire pour le tableau servant de "mémoire" au Cardiac
   	memoire = malloc(sizeof(int)*taille);

   	// On utilise nos fonctions de simulation de Cardiac
	chargement_bande();
	lecture();

	// On libère la mémoire que l'on a malloc
	free(memoire);

	printf("Fin du programme\n");
	return 0;
}
