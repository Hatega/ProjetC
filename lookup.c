#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <openssl/md5.h>
#include "generate.h"
#include "lookup.h"
#include "hash_list.h"
#include "condensat_list.h"


#define LEN_LIGNE 100


void lookup(char input[]){
    Hash_list * liste_hash = NULL;
    char ligne[LEN_LIGNE];
    while(fgets(ligne,sizeof(ligne),stdin)!=NULL){
        for(int i=0; i<LEN_LIGNE;i++){
            if(ligne[i]=='\n' || ligne [i]=='\r'){
                ligne[i]='\0';
                break;
            }
        }
        liste_hash = creer_avant_hash(liste_hash,ligne);
    }
    afficher_liste_hash(liste_hash);

	FILE * fp;
    fp = fopen(input,"r");
	Condensat * liste_condensat = NULL;
    int compteur_affichage = 0;
	while(fgets(ligne,sizeof(ligne),fp)!=NULL){
        int compteur =0;
		int compteur_m =0;
		int separateur =0;
		char hash[LEN_LIGNE];
		char mot[LEN_LIGNE];
        for(int i=0; i<LEN_LIGNE;i++){
            if(ligne[i]==':' && separateur==0){
				separateur = 1;
				hash[i]='\0';
			}else if(ligne[i]=='\n' || ligne[i]=='\r'){
                mot[compteur_m]='\0';
                break;
            }else{
				if(separateur==0){
					hash[i]=ligne[i];
				}else{
					mot[compteur_m]=ligne[i];
					compteur_m ++;
				}
			}
            compteur++;
        }
		liste_condensat = creer_avant_condensat(liste_condensat,hash,mot);
		compteur_affichage ++;
        if(compteur_affichage%100==0){
            printf("INFO Loading %d hashes...\n",compteur_affichage);
        }
	}

    Hash_list * hash_chercher = liste_hash;

	while(liste_condensat!=NULL){
        while(hash_chercher!=NULL){
            if(strcmp(liste_condensat->hash,hash_chercher->val)==0){
                printf("MATCH %s %s\n",liste_condensat->hash,liste_condensat->mot);
            }
            hash_chercher=hash_chercher->next;
        }
        hash_chercher = liste_hash;
        liste_condensat=liste_condensat->next;

	}    

    destruct_hash(liste_hash);
    destruct_condensat(liste_condensat);
}