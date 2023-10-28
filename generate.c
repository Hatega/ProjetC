#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <openssl/md5.h>

//Bibliothèque personnelle
#include "generate.h"

//Taille maximale des lignes d'entrées
#define LEN_LIGNE 100 //Si on veut pouvoir manipuler des mot de passe plus grand que 100 caractère il faut modifier cet valeur

void generate(char input[], char output[], char algorithm[]){
    //Initialisation des fichiers
    FILE * f_input;
	FILE * f_output;
    f_input = fopen(input,"r");
    f_output = fopen(output,"w");

    //Déclaration diverse
    char ligne[LEN_LIGNE]; //pour stocker une ligne du fichier
    int compteur_affichage = 0; //Compteur du nombre de hash écrit dans le fichier de sortie
    const char * separateur = "\n"; //Caractère de fin de ligne

    //Lecture du dictionaire et génération des condensat
	while(fgets(ligne,sizeof(ligne),f_input)!=NULL){
        //Déclaration variable interne pour chaque ligne
        int taille =0; 
        int algo = 0; // type d'algorithme de hachage : 0-SHA256, 1-MD5, 2-SHA1

        if(ligne[0]!='\n'){ // Enleve le cas de ligne vide
            char * strToken = strtok(ligne, separateur); // Récupère dans ligne tout les char avant le séparateur

            //Définition algorithme à utiliser
            if (strcmp(algorithm, "sha256") == 0) {
                taille = SHA256_DIGEST_LENGTH;
                algo = 0;
            }else if(strcmp(algorithm, "md5")==0){
                taille = MD5_DIGEST_LENGTH;
                algo = 1;
            }else if(strcmp(algorithm, "sha1")==0){
                taille = SHA_DIGEST_LENGTH;
                algo = 2;
            }

            unsigned char hash[taille]; //Déclaration de la variable qui va contenir le futur hash

            //Hachage selon l'algorithme
            switch(algo){
                case 1 : 
                    MD5((const unsigned char *)strToken, strlen(strToken), hash);
                    break;
                case 2 :
                    SHA1((const unsigned char *)strToken, strlen(strToken), hash);
                    break;
                case 0 :
                default :
                    SHA256((const unsigned char *)strToken, strlen(strToken), hash);
                    break;
            }

            //Ecriture dans le fichier de sorti
            for (int i = 0; i < taille; i++) {
                fprintf(f_output, "%02x", hash[i]); //Ecriture du hash en héxadécimal
            }
            fprintf(f_output,":%s\n",strToken); //Ecriture du séparateur : et de la ligne correspodant au hash

            //Affichage des informations
            compteur_affichage ++; 
            if(compteur_affichage%10000==0){
                printf("INFO %d hashes written...\n",compteur_affichage); //Affichage en console du nombre de hash écrit tout les 10 000 hash
            }
        }
    }
    printf("INFO Total of hashes written : %d\n",compteur_affichage); //Affichage en console du nombre de hash total écrit

    //Fermeture des fichiers ouvert
	fclose(f_input);
    fclose(f_output);
}

