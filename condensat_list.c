#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "condensat_list.h"



void afficher_condensat(Condensat *p){
	printf("-----%p--------\n", p);
	printf("Hash : %s\n",p->hash);
	printf("Mot : %s\n",p->mot);
	printf("next : %p\n",p->next);
	printf("--------------\n");
}
void afficher_liste_condensat(Condensat *p){
	while(p!=NULL){
		afficher_condensat(p);
		p = p->next;
		printf("|\n");
		printf("v\n");
	}
}

void afficher_N_condensat(Condensat *p,int N){
	for(int i=0;i<N;i++){
		p = p->next;
	}
	afficher_condensat(p);
}

Condensat * create_Condensat(char hash[], char mot[]){
	Condensat *n = malloc(sizeof(Condensat));
	strcpy(n->hash,hash);
	strcpy(n->mot,mot);
	n->next = NULL;
	return n;
}


int taille_condensat(Condensat *p){
	int compteur = 0;
	while(p!=NULL){
		compteur++;
		p=p->next;
	}
	return compteur;
}

Condensat * pointeur_N_condensat(Condensat *p, int N){
	int i=0;
	while(p!=NULL && i<N-1){
		p=p->next;
		i++;
	}
	return p;
}

Condensat * creer_avant_condensat(Condensat *p, char hash[], char mot[]){
	Condensat *n = create_Condensat(hash,mot);
	n->next = p;
	p = n;
	return p;
}

Condensat * supprimer_condensat(Condensat *p, int N){
	if(N==1){
		Condensat *s = p;
		p=p->next;
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

void destruct_condensat(Condensat *p){
	for(int i=taille_condensat(p);i>0;i--){
		supprimer_condensat(p,i);
	}
}

/*int main(){

	Condensat * p = NULL;
	p=creer_avant_condensat(p,"sjsqj","shsq");
	p=creer_avant_condensat(p,"sjsqzaj","shsqzz");

	afficher_liste_condensat(p);

	destruct_condensat(p);
	return 0;
}*/


