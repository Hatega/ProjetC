#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <openssl/md5.h>

//Bibliothèque personnelle
#include "lookup.h"
#include "hash_list.h"
#include "condensat_list.h"

//Taille maximale des lignes d'entrées
#define LEN_LIGNE 200 // Generate manipule des mot de passe de maximum 100 cela laisse au maximum 99 pour les hashs

// Mode LOOKUP - Recherche de mot de passe depuis un hash
void lookup(char input[]){
    //Déclaration 
    Hash_list * liste_hash = NULL; //Liste Chainé des hashs à trouver
    char ligne[LEN_LIGNE]; //Variable de stockage de ligne

    //Lecture du STDIN
    while(fgets(ligne,sizeof(ligne),stdin)!=NULL){
        //Boucle de modification des lignes pour mettre \0 à la place de \n 
        for(int i=0; i<LEN_LIGNE;i++){
            if(ligne[i]=='\n' || ligne [i]=='\r'){ // Cas \r pour les fichiers issus de Windows
                ligne[i]='\0';
                break;
            }
        }
        liste_hash = creer_avant_hash(liste_hash,ligne); //Ajout du hash à la liste chainé
    }

    //Déclaration 
	FILE * f_input; //Déclaration du fichier d'input
    f_input = fopen(input,"r");
	Condensat * liste_condensat = NULL; //Liste Chainé des condensats
    int compteur_affichage = 0; //Compteur du nombre de hash loader en mémoire depuis le fichier d'entrée'
	
    //Lecture du fichier de condensat
    while(fgets(ligne,sizeof(ligne),f_input)!=NULL){

        //Déclaration interne au while
		int compteur_m =0; //Parser pour l'initialisation de mot
		int separateur =0; //0:séparateur pas encore passé, 1:séparateur déjà rencontré
		char hash[LEN_LIGNE]; //Variable de stockage pour le hash
		char mot[LEN_LIGNE]; //Variable de stockage pour le mot de passe

        //Remplissage de hash et mot depuis ligne
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
        }

		liste_condensat = creer_avant_condensat(liste_condensat,hash,mot); //Ajout du condensat à la liste chainé

        //Affichage des informations
		compteur_affichage ++;
        if(compteur_affichage%100==0){
            printf("INFO Loading %d hashes...\n",compteur_affichage); //Affichage en console du nombre de condensat loader tout les 100 condensat
        }
	}
    printf("INFO %d hashes loaded.\n",compteur_affichage); //Affichage en console du nombre de condensat total loader

    //Fermeture du fichier d'entrée ouvert
    fclose(f_input);

    //Déclaration
    Hash_list * hash_chercher = liste_hash; //Copie de liste_hash pour le parcours
    Condensat * condensat_parser = liste_condensat; //Copie de liste_condensat pour le parcours

    //Comparaison des hashs à trouver et des condensats
	while(condensat_parser!=NULL && liste_hash!=NULL){
        int position = 1; //Position dans liste_hash
        while(hash_chercher!=NULL){
            //Condensat trouver
            if(strcmp(condensat_parser->hash,hash_chercher->val)==0){
                printf("MATCH %s %s\n",condensat_parser->hash,condensat_parser->mot);
                liste_hash = supprimer_hash(liste_hash,position); //Suppression du hash trouver dans la liste chainé pour pas continué à la rechercher
                position --;
            }
            //Déplacement dans la liste de hash
            hash_chercher=hash_chercher->next;
            position ++;
        }
        //mise à jour des hash_chercher 
        hash_chercher = liste_hash;
        //Déplacement dans la liste de condensat
        condensat_parser=condensat_parser->next;

	}

    //Affichage des hash pas trouvé
    hash_chercher = liste_hash;
    while(hash_chercher!=NULL){
        printf("NO MATCH found for hash : %s\n",hash_chercher->val);
        hash_chercher=hash_chercher->next;
    }

    //Libération des listes chainées
    destruct_condensat(liste_condensat);
    destruct_hash(liste_hash);
}
