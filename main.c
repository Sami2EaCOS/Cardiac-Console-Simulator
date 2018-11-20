// On rajoute la bibliothèque standart à notre programme C
#include <stdio.h>

// Définition de la taille de la mémoire du processeur Cardiac
#define taille 100

int acc = 0;
int co = 0;

int* memoire = NULL;

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

void INP(int adresse) {
	int nbr = 0;
	printf("INP: ");
	scanf("%d", &nbr);
	memoire[adresse] = nbr;
}

void OUT(int adresse) {
	int nbr = memoire[adresse];
	printf("OUT: %d\n", nbr);
}

void LDA(int adresse) {
	acc = memoire[adresse];
}

void LDI(int adresse) {
	acc = memoire[memoire[adresse]%100];
}

void STA(int adresse) {
	memoire[adresse] = acc;
}

void STI(int adresse) {
	memoire[memoire[adresse]%100] = acc;
}

void ADD(int adresse) {
	acc = (acc + memoire[adresse])%1000;
}

void SUB(int adresse) {
	acc = (acc - memoire[adresse])%1000;
}

void JAZ(int adresse) {
	if (acc == 0) {
		memoire[99] = co + 800;
		co = adresse;
	} else {
        ++co;
	}
}

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
