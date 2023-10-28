#ifndef CONDENSAT_LIST_H
#define CONDENSAT_LIST_H

typedef struct condensat {
    char hash[100];
    char mot[100];
    struct condensat *next;
} Condensat;

Condensat *create_Condensat(char hash[], char mot[]);

int taille_condensat(Condensat *p);

Condensat *pointeur_N_condensat(Condensat *p, int N);

Condensat *creer_avant_condensat(Condensat *p, char hash[], char mot[]);

Condensat *supprimer_condensat(Condensat *p, int N);

void destruct_condensat(Condensat *p);

#endif

