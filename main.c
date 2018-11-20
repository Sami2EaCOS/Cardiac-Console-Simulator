// On rajoute les bibliothèques "standards" à notre programme C
#include <stdio.h>
#include <stdlib.h>

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
		} else if (i == 99) {
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
	acc = max(acc - memoire[adresse], 0);
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

int lecture() {
	while (1) {
	    if (co > 99) {
            break;
	    }

	    int adresse = memoire[co]%100;
		int clef = memoire[co]/100;

		switch (clef) {
        case 9:
            HRS();
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
        default:
            return -1;
		}
	}
}

int main() {
   	memoire = malloc(sizeof(int)*taille);
	chargement_bande();
	lecture();
	free(memoire);
	printf("Fin du programme");
	return 0;
}
