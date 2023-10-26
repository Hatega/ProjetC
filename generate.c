#include <stdio.h>
#include <openssl/sha.h>
#include "generate.h"

#define LEN_LIGNE 100

void generate(char input[], char output[]){
    FILE * fp;
	FILE * fp2;
    fp = fopen(input,"r");
    fp2 = fopen(output,"w");
	char ligne[LEN_LIGNE];
    unsigned char hash[SHA256_DIGEST_LENGTH];
	while(fgets(ligne,sizeof(ligne),fp)!=NULL){
        int compteur =0;
        for(int i=0; i<LEN_LIGNE;i++){
            if(ligne[i]=='\n'){
                ligne[i]='\0';
                break;
            }
            compteur++;
        }
		SHA256((const unsigned char *)ligne, compteur,hash);
        fprintf(fp2,"%s:",ligne);
        for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
            fprintf(fp2,"%02x", hash[i]);
        }
        fprintf(fp2,"\n");
	}
	fclose(fp);
    fclose(fp2);
}