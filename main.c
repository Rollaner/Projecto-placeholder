#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "functionscat.h"
#include "functionstag.h"
#include "Map.h"
#include "list.h"
#include "queue.h"

long long stringHash(const void * key) {
    long long hash = 5381;

    const char * ptr;

    for (ptr = key; *ptr != '\0'; ptr++) {
        hash = ((hash << 5) + hash) + tolower(*ptr); /* hash * 33 + c */
    }

    return hash;
}

int stringEqual(const void * key1, const void * key2) {
    const char * A = key1;
    const char * B = key2;

    return strcmp(A, B) == 0;
}

int main()
{
    int op = 0;
    char* catname = calloc(30,sizeof(char));
    Map* catMap = createMap(stringHash,stringEqual);
    //Map* catMap = loadcats(Catfile);
    printf("Ingrese numero de la operacion deseada: \n");
    printf("1) Agregar categoria \n");
    printf("2) Eliminar categoria \n");
    printf("3) Ingresar categoria \n");
    printf("4) Salir \n");
    while(op!=4){
        scanf("%d", &op);
        switch(op){
        case 1: printf("Ingrese nombre de la categoria \n");
            fgets(catname,10,stdin);             //para eliminar "\n del switch"
            fgets(catname,30,stdin);
            addCat(catname,catMap);
            break;
        case 2: printf("Ingrese nombre de la categoria a eliminar \n ");
            fgets(catname,10,stdin);
            fgets(catname,30,stdin);
            deleteCat(catname,catMap);
            break;
        case 3: printf("ingrese nombre cat \n");
            fgets(catname,10,stdin);
            fgets(catname,30,stdin);
            printf("entrando a categoria %s ", catname);
            enterCat(catname);
            break;
        default: printf("Opcion no valida, intente nuevamentente \n");
        continue;
        }
    }
    return 0;
}
