#ifndef HASH_LIST_H
#define HASH_LIST_H

typedef struct hash_list {
    char val[100];
    struct hash_list *next;
} Hash_list;

void afficher_hash(Hash_list *p);

void afficher_liste_hash(Hash_list *p);

void afficher_N_hash(Hash_list *p, int N);

Hash_list *create_Hash_list(char value[]);

int taille_hash(Hash_list *p);

Hash_list *pointeur_N_hash(Hash_list *p, int N);

Hash_list *creer_avant_hash(Hash_list *p, char Value[]);

Hash_list *supprimer_hash(Hash_list *p, int N);

void destruct_hash(Hash_list *p);

#endif

