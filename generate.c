#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <openssl/md5.h>
#include "generate.h"

#define LEN_LIGNE 100

void generate(char input[], char output[], char algorithm[]){
    //Initialisation des fichiers
    FILE * f_input;
	FILE * f_output;
    f_input = fopen(input,"r");
    f_output = fopen(output,"w");

    //Déclaration diverse
    char ligne[LEN_LIGNE]; //pour stocker une ligne du fichier
    int compteur_affichage = 0; //pour afficher des messages d'information

    //Lecture du dictionaire et génération des condensat
	while(fgets(ligne,sizeof(ligne),f_input)!=NULL){
        //Déclaration variable interne pour chaque ligne
        const char * separateur = "\n";
        int taille =0;
        int algo = 0;

        if(ligne[0]!='\n'){
            char * strToken = strtok(ligne, separateur);
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
            unsigned char hash[taille];
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
            for (int i = 0; i < taille; i++) {
                fprintf(f_output, "%02x", hash[i]);
            }
            fprintf(f_output,":%s",strToken);
            fprintf(f_output,"\n");
            compteur_affichage ++;
            if(compteur_affichage%10000==0){
                printf("INFO %d hashes written...\n",compteur_affichage);
            }
        }
    }
    printf("INFO Total of hashes written : %d\n",compteur_affichage);
	fclose(f_input);
    fclose(f_output);
}

