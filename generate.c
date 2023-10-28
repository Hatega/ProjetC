#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <openssl/md5.h>
#include "generate.h"

#define LEN_LIGNE 100

unsigned char *hachage(char algorithm[], char ligne[], int compteur, int *taille){
    unsigned char *hash = NULL;

    if (strcmp(algorithm, "sha256") == 0) {
        hash = (unsigned char *)malloc(SHA256_DIGEST_LENGTH);
        if (hash) {
            SHA256((const unsigned char *)ligne, compteur, hash);
        }
        *taille = SHA256_DIGEST_LENGTH;
    }else if(strcmp(algorithm, "md5")==0){
        hash = (unsigned char *)malloc(MD5_DIGEST_LENGTH);
        if (hash) {
            MD5((const unsigned char *)ligne, compteur, hash);
        }
        *taille = MD5_DIGEST_LENGTH;
    }

    return hash;
}

void generate(char input[], char output[], char algorithm[]){
    FILE * fp;
	FILE * fp2;
    fp = fopen(input,"r");
    fp2 = fopen(output,"w");
    char ligne[LEN_LIGNE];
    int compteur_affichage = 0;
	while(fgets(ligne,sizeof(ligne),fp)!=NULL){
        int compteur =0;
        for(int i=0; i<LEN_LIGNE;i++){
            if(ligne[i]=='\n'){
                ligne[i]='\0';
                break;
            }
            compteur++;
        }
        int *taille = malloc(sizeof(int));
        unsigned char *hash = hachage(algorithm,ligne,compteur,taille);
        if (hash) {
            for (int i = 0; i < *taille; i++) {
                fprintf(fp2, "%02x", hash[i]);
             }
        }
        free(hash);
        free(taille);
        fprintf(fp2,":%s",ligne);
        fprintf(fp2,"\n");
        compteur_affichage ++;
        if(compteur_affichage%1000==0){
            printf("INFO %d hashes written...\n",compteur_affichage);
        }
    }
    printf("INFO Total of hashes written : %d\n",compteur_affichage);
	fclose(fp);
    fclose(fp2);
}

