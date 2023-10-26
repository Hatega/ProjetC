#include <stdio.h>
#include <string.h>

#include "generate.h"
//#include "lookup.h"

int main(int argc, char *argv[]){

    int mode = 0; //0: generate , 1: lookup
    int input ;
    int output; 

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
        }
    }

    switch(mode){
        case 0:
            generate(argv[input],argv[output]);
        /*case 1:
            lookup(argv[input]);*/
    }

    return 0;
}