#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Bibliothèque personnelle
#include "hash_list.h"

//Méthode Liste Chainée des Hash à trouver

//Création d'un noeud
Hash_list * create_Hash_list(char value[]){
	Hash_list *n = malloc(sizeof(Hash_list));
	strcpy(n->val,value);
	n->next = NULL;
	return n;
}

//Récupération de la taille de la chaine
int taille_hash(Hash_list *p){
	int compteur = 0;
	while(p!=NULL){
		compteur++;
		p=p->next;
	}
	return compteur;
}

//Récupération de l'élément N de la chaine
Hash_list * pointeur_N_hash(Hash_list *p, int N){
	int i=0;
	while(p!=NULL && i<N-1){
		p=p->next;
		i++;
	}
	return p;
}

//Mise en place d'un noeud au début
struct hash_list * creer_avant_hash(Hash_list *p, char Value[]){
	Hash_list *n = create_Hash_list(Value);
	n->next = p;
	p = n;
	return p;
}

//Suppression d'un noeud
Hash_list * supprimer_hash(Hash_list *p, int N){
	if(N==1){
		Hash_list *s = p;
		p=p->next;
		//free(s->val);
		free(s);

	}else{
		Hash_list *avant = pointeur_N_hash(p,N-1);
		Hash_list *s = pointeur_N_hash(p,N);
		avant->next = s->next;
		//free(s->val);
		free(s);
	}
	return p;
	
}

//Suppression de la liste chainé
void destruct_hash(Hash_list *p){
	for(int i=taille_hash(p);i>0;i--){
		supprimer_hash(p,i);
	}
}

