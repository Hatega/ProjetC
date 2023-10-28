#include <stdio.h>
#include <string.h>

//Blibliothèque personnelle
#include "generate.h"
#include "lookup.h"

//Boucle Principal
int main(int argc, char *argv[]){

    int mode = 0; // Mode d'utilisation : 0-generate, 1-lookup, 2-generate+lookup
    int input ; // Position du nom du fichier d'entrée dans argv[] 
    int output; // Position du nom du fichier de sortie dans argv[]
    int algo = -1; // Position du nom de l'algorithme de hachage si fourni

    //Identification des paramètres passé en argument
    for(int i=0; i<argc;i++){
        // Mode d'utilisation
        if(strcmp(argv[i],"-G")==0){
            mode = 0;
        }else if(strcmp(argv[i],"-L")==0){
            mode = 1;
        }else if(strcmp(argv[i],"-GL")==0){
            mode = 2;
        }
        // Fichier entrée et sortie
        else if(strcmp(argv[i],"-i")==0){
            input = i + 1;
            i++;
        }else if(strcmp(argv[i],"-o")==0){
            output = i + 1;
            i++;
        }
        // Algorithme de hachage
        else if(strcmp(argv[i],"-a")==0){
            algo = i+1;
            i++;
        }
    }

    //Lancement des fonctionnalités selon le mode d'utilisation
    switch(mode){
        case 0:
            //Algorithme passé en argument
            if(algo!=-1){
                generate(argv[input],argv[output],argv[algo]);
            }
            //Algorithme non passé en paramètre -> SHA256 choisi par défaut
            else{
                generate(argv[input],argv[output],"sha256");
            }
            break;
        case 1:
            lookup(argv[input]);
            break;
        case 2: 
            if(algo!=-1){
                generate(argv[input],argv[output],argv[algo]);
            }else{
                generate(argv[input],argv[output],"sha256");
            }
            lookup(argv[output]); // L'output généré par generate est réutilisé en tant que input pour lookup
            break;
    }

    return 0;
}