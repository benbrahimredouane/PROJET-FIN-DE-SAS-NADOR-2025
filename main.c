#include <stdio.h>
#include <string.h>
#include <ctype.h>




#define MAX_TEXT 2000
#define MAX_MOTS 500
#define TAILLE_MOT 30



typedef struct {
    char mot[TAILLE_MOT];
    int occurrences;
    int longueur;
} Dictionnaire;





void menu();
void analyserTexte(char texte[], Dictionnaire dico[], int *nbMots);
void afficherDico(Dictionnaire dico[], int nbMots);
void rechercherMotExact(Dictionnaire dico[], int nbMots, char mot[]);
void rechercherMotPartiel(Dictionnaire dico[], int nbMots, char mot[]);
void trierDicoAlpha(Dictionnaire dico[], int nbMots);
void trierDicoFrequence(Dictionnaire dico[], int nbMots);
void trierDicoLongueur(Dictionnaire dico[], int nbMots);
void statistiques(Dictionnaire dico[], int nbMots);
int estPalindrome(char mot[]);
void palindromes(Dictionnaire dico[], int nbMots);
void anagrammes(Dictionnaire dico[], int nbMots);
void nuageDeMots(Dictionnaire dico[], int nbMots);





int main() {
    char texte[MAX_TEXT];
    Dictionnaire dico[MAX_MOTS];
    int nbMots = 0, choix;

    do {
        menu();
        scanf("%d", &choix);
        getchar();

        if (choix == 1) {
            do{
            printf("Saisir le texte:\n");
            fgets(texte, sizeof(texte), stdin);
            analyserTexte(texte, dico, &nbMots);
            texte[strcspn(texte, "\n")] = '\0';
            }while(texte[0] == '\0');
        } else if (choix == 2) {
            afficherDico(dico, nbMots);
        } else if (choix == 3) {
            char mot[TAILLE_MOT];
            printf("Mot à rechercher: ");
            scanf("%s", mot);
            rechercherMotExact(dico, nbMots, mot);
        } else if (choix == 4) {
            char mot[TAILLE_MOT];
            printf("Mot partiel: ");
            scanf("%s", mot);
            rechercherMotPartiel(dico, nbMots, mot);
        } else if (choix == 5) {
            printf("1. Alphabetique\n2. Frequence\n3. Longueur \n Votre choix: ");
            int t;
            scanf("%d", &t);
            if (t == 1) trierDicoAlpha(dico, nbMots);
            else if (t == 2) trierDicoFrequence(dico, nbMots);
            else if (t == 3) trierDicoLongueur(dico, nbMots);
        } else if (choix == 6) {
            statistiques(dico, nbMots);
        } else if (choix == 7) {
            palindromes(dico, nbMots);
            anagrammes(dico, nbMots);
            nuageDeMots(dico, nbMots);
        }
        else if (choix==8) printf(" ok! have a good day");
        else printf("invalide choix");
    } while (choix != 8);

    return 0;
}


void menu() {
    printf("\n===== MENU =====\n");
    printf("1. Saisir un texte et analyser\n");
    printf("2. Afficher tous les mots\n");
    printf("3. Rechercher un mot exact\n");
    printf("4. Rechercher un mot partiel\n");
    printf("5. Trier les mots\n");
    printf("6. Statistiques globales\n");
    printf("7. Analyses (Palindromes, Anagrammes, Nuage)\n");
    printf("8. Quitter\n");
    printf("Votre choix: ");
}



void analyserTexte(char texte[], Dictionnaire dico[], int *nbMots) {
    char mot[TAILLE_MOT];
    int i = 0;
    *nbMots = 0;

    for (int k = 0; texte[k] != '\0'; k++) {
        if (isalpha(texte[k])) {
            mot[i++] = tolower(texte[k]);
        } else if (i > 0) {
            mot[i] = '\0';
            i = 0;

            int trouve = 0;
            for (int j = 0; j < *nbMots; j++) {
                if (strcmp(dico[j].mot, mot) == 0) {
                    dico[j].occurrences++;
                    trouve = 1;
                    break;
                }
            }
            if (!trouve && *nbMots < MAX_MOTS) {
                strcpy(dico[*nbMots].mot, mot);
                dico[*nbMots].occurrences = 1;
                dico[*nbMots].longueur = strlen(mot);
                (*nbMots)++;
            }
        }
    }
}


void afficherDico(Dictionnaire dico[], int nbMots) {
    printf("\n--- Dictionnaire ---\n");
    for (int i = 0; i < nbMots; i++) {
        printf("%s - %d fois - longueur %d\n", dico[i].mot, dico[i].occurrences, dico[i].longueur);
    }
}


void rechercherMotExact(Dictionnaire dico[], int nbMots, char mot[]) {
    for (int i = 0; i < nbMots; i++) {
        if (strcmp(dico[i].mot, mot) == 0) {
            printf("%s trouve : %d fois, longueur %d\n", mot, dico[i].occurrences, dico[i].longueur);
            return;
        }
    }
    printf("%s non trouve \n", mot);
}


void rechercherMotPartiel(Dictionnaire dico[], int nbMots, char mot[]) {
    printf("Mots contenant '%s':\n", mot);
    for (int i = 0; i < nbMots; i++) {
        if (strstr(dico[i].mot, mot) != NULL) {
            printf("%s\n", dico[i].mot);
        }
    }
}

void trierDicoAlpha(Dictionnaire dico[], int nbMots) {
    for (int i = 0; i < nbMots - 1; i++) {
        for (int j = i + 1; j < nbMots; j++) {
            if (strcmp(dico[i].mot, dico[j].mot) > 0) {
                Dictionnaire tmp = dico[i];
                dico[i] = dico[j];
                dico[j] = tmp;
            }
        }
    }
}



void trierDicoFrequence(Dictionnaire dico[], int nbMots) {
    for (int i = 0; i < nbMots - 1; i++) {
        for (int j = i + 1; j < nbMots; j++) {
            if (dico[i].occurrences < dico[j].occurrences) {
                Dictionnaire tmp = dico[i];
                dico[i] = dico[j];
                dico[j] = tmp;
            }
        }
    }
}



void trierDicoLongueur(Dictionnaire dico[], int nbMots) {
    for (int i = 0; i < nbMots - 1; i++) {
        for (int j = i + 1; j < nbMots; j++) {
            if (dico[i].longueur > dico[j].longueur) {
                Dictionnaire tmp = dico[i];
                dico[i] = dico[j];
                dico[j] = tmp;
            }
        }
    }
}




void statistiques(Dictionnaire dico[], int nbMots) {
    int total = 0, maxFreq = 0, minLen = 1000, maxLen = 0;
    char motFreq[TAILLE_MOT], motCourt[TAILLE_MOT], motLong[TAILLE_MOT];

    for (int i = 0; i < nbMots; i++) {
        total += dico[i].occurrences;
        if (dico[i].occurrences > maxFreq) {
            maxFreq = dico[i].occurrences;
            strcpy(motFreq, dico[i].mot);
        }
        if (dico[i].longueur < minLen) {
            minLen = dico[i].longueur;
            strcpy(motCourt, dico[i].mot);
        }
        if (dico[i].longueur > maxLen) {
            maxLen = dico[i].longueur;
            strcpy(motLong, dico[i].mot);
        }
    }
    float taille;
    for (int i = 0; i < nbMots; i++) {
        taille+=dico[i].longueur;
    }

    printf("\n--- Statistiques ---\n");
    printf("Total mots: %d\n", total);
    printf("Mots uniques: %d\n", nbMots);
    printf("la longueur moyenne est:  %0.3f\n",taille/total);
    printf("Mot le plus frequent: %s (%d fois)\n", motFreq, maxFreq);
    printf("Mot le plus court: %s (%d lettres)\n", motCourt, minLen);
    printf("Mot le plus long: %s (%d lettres)\n", motLong, maxLen);
}

int estPalindrome(char mot[]) {
    int i = 0, j = strlen(mot) - 1;
    while (i < j) {
        if (mot[i] != mot[j]) return 0;
        i++; j--;
    }
    return 1;
}

void palindromes(Dictionnaire dico[], int nbMots) {
    printf("\n--- Palindromes ---\n");
    for (int i = 0; i < nbMots; i++) {
        if (estPalindrome(dico[i].mot)) {
            printf("%s\n", dico[i].mot);
        }
    }
}


void trierMot(char mot[]) {
    int n = strlen(mot);
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (mot[i] > mot[j]) {
                char tmp = mot[i];
                mot[i] = mot[j];
                mot[j] = tmp;
            }
        }
    }
}
void anagrammes(Dictionnaire dico[], int nbMots) {
    printf("\n--- Anagrammes ---\n");
    for (int i = 0; i < nbMots; i++) {
        for (int j = i + 1; j < nbMots; j++) {
            if (strlen(dico[i].mot) == strlen(dico[j].mot)) {
                char a[TAILLE_MOT], b[TAILLE_MOT];
                strcpy(a, dico[i].mot);
                strcpy(b, dico[j].mot);

                trierMot(a);
                trierMot(b);

                if (strcmp(a, b) == 0) {
                    printf("%s <-> %s\n", dico[i].mot, dico[j].mot);
                }
            }
        }
    }
}
void nuageDeMots(Dictionnaire dico[], int nbMots) {
    printf("\n--- Nuage de mots ---\n");
    for (int i = 0; i < nbMots; i++) {
        printf("%s: ", dico[i].mot);
        for (int j = 0; j < dico[i].occurrences; j++) printf("*");
        printf("\n");
    }
}




