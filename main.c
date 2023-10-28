#include <stdio.h>
#include <string.h>

#include "generate.h"
#include "lookup.h"

int main(int argc, char *argv[]){

    int mode = 0; //0: generate , 1: lookup
    int input ;
    int output; 
    int algo = -1;

    for(int i=0; i<argc;i++){
        if(strcmp(argv[i],"-G")==0){
            mode = 0;
        }else if(strcmp(argv[i],"-L")==0){
            mode = 1;
        }else if(strcmp(argv[i],"-i")==0){
            input = i + 1;
            i++;
        }else if(strcmp(argv[i],"-o")==0){
            output = i + 1;
            i++;
        }else if(strcmp(argv[i],"-a")==0){
            algo = i+1;
            i++;
        }
    }

    switch(mode){
        case 0:
            if(algo!=-1){
                generate(argv[input],argv[output],argv[algo]);
            }else{
                generate(argv[input],argv[output],"sha256");
            }
            break;
        case 1:
            lookup(argv[input]);
            break;
    }

    return 0;
}