#include <stdio.h>
#define taille 100

int acc = 0;
int co = 0;

int* memoire = NULL;

void chargement_bande() {
	int information = 0;
	for (int i=0;i<taille;++i) {
		if (i == 0) {
            memoire[i] = 001;
		} else if (i == 99) {
            memoire[i] = 800;
		} else {
            memoire[i] = 000;
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

void lecture() {
	while (1) {
	    if (co > 99) {
            break;
	    }
		int j = memoire[co];
		if (j>=900) {
			HRS();
			break;
		} else if (j>=800) {
			JAZ(j-800);
		} else if (j>=700) {
			SUB(j-700);
			++co;
		} else if (j>=600) {
			ADD(j-600);
			++co;
		} else if (j>=500) {
			STI(j-500);
			++co;
		} else if (j>=400) {
			STA(j-400);
			++co;
		} else if (j>=300) {
			LDI(j-300);
			++co;
		} else if (j>=200) {
			LDA(j-200);
			++co;
		} else if (j>=100) {
			OUT(j-100);
			++co;
		} else {
			INP(j);
			++co;
		}
	}
}


int main() {
   	memoire = malloc(sizeof(int)*taille);
	chargement_bande();
	lecture();
	free(memoire);
	return 0;
}
