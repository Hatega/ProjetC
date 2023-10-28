#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash_list.h"



void afficher_hash(Hash_list *p){
	//printf("-----%p--------\n", p);
	printf("Val : %s\n",p->val);
	//printf("next : %p\n",p->next);
	printf("--------------\n");
}
void afficher_liste_hash(Hash_list *p){
	while(p!=NULL){
		afficher_hash(p);
		p = p->next;
		printf("|\n");
		printf("v\n");
	}
}

void afficher_N_hash(Hash_list *p,int N){
	for(int i=0;i<N;i++){
		p = p->next;
	}
	afficher_hash(p);
}

Hash_list * create_Hash_list(char value[]){
	Hash_list *n = malloc(sizeof(Hash_list));
	strcpy(n->val,value);
	n->next = NULL;
	return n;
}


int taille_hash(Hash_list *p){
	int compteur = 0;
	while(p!=NULL){
		compteur++;
		p=p->next;
	}
	return compteur;
}

Hash_list * pointeur_N_hash(Hash_list *p, int N){
	int i=0;
	while(p!=NULL && i<N-1){
		p=p->next;
		i++;
	}
	return p;
}

struct hash_list * creer_avant_hash(Hash_list *p, char Value[]){
	Hash_list *n = create_Hash_list(Value);
	n->next = p;
	p = n;
	return p;
}

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

void destruct_hash(Hash_list *p){
	for(int i=taille_hash(p);i>0;i--){
		supprimer_hash(p,i);
	}
}

/*int main(){

	Hash_list * p = NULL;
	p=creer_avant_hash(p,"kec");
	p=creer_avant_hash(p,"zhqJ");

	afficher_liste_hash(p);

	destruct_hash(p);
	return 0;
}*/


