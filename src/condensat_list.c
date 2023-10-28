#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Bibliothèque personnelle
#include "condensat_list.h"

//Méthode Liste Chainée des Condensats

//Création d'un noeud
Condensat * create_Condensat(char hash[], char mot[]){
	Condensat *n = malloc(sizeof(Condensat));
	strcpy(n->hash,hash);
	strcpy(n->mot,mot);
	n->next = NULL;
	return n;
}

//Récupération de la taille de la chaine
int taille_condensat(Condensat *p){
	int compteur = 0;
	while(p!=NULL){
		compteur++;
		p=p->next;
	}
	return compteur;
}

//Récupération de l'élément N de la chaine
Condensat * pointeur_N_condensat(Condensat *p, int N){
	int i=0;
	while(p!=NULL && i<N-1){
		p=p->next;
		i++;
	}
	return p;
}

//Mise en place d'un noeud au début
Condensat * creer_avant_condensat(Condensat *p, char hash[], char mot[]){
	Condensat *n = create_Condensat(hash,mot);
	n->next = p;
	p = n;
	return p;
}

//Suppression d'un noeud
Condensat * supprimer_condensat(Condensat *p, int N){
	if(N==1){
		Condensat *s = p;
		p=p->next;
		//free(s->hash);
		//free(s->mot);
		free(s);

	}else{
		Condensat *avant = pointeur_N_condensat(p,N-1);
		Condensat *s = pointeur_N_condensat(p,N);
		avant->next = s->next;
		//free(s->hash);
		//free(s->mot);
		free(s);
	}
	return p;
	
}

//Suppression de la liste chainé
void destruct_condensat(Condensat *p){
	for(int i=taille_condensat(p);i>0;i--){
		supprimer_condensat(p,i);
	}
}


