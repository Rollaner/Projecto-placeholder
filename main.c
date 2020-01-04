#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "functionscat.h"
#include "functionstag.h"
#include "Map.h"
#include "list.h"
#include "queue.h"


int main()
{
    int op = 0;
    char* catname = calloc(30,sizeof(char));
    Map* catMap = createMap(stringHash,stringEqual);    /** mapa para categorias, stringhash y stringEqual
                                                            estan en functionscat.h y .c*/
    //Map* catMap = loadcats(Catfile);
    printf("Ingrese numero de la operacion deseada: \n");
    printf("1) Agregar categoria \n");
    printf("2) Eliminar categoria \n");
    printf("3) Ingresar categoria \n");
    printf("4) Salir \n");
    while(op < 4){          /** Menu de categoria, usa los valores que entrege el usuario (nombres)*/
        scanf("%d", &op);
        switch(op){
        case 1: printf("Ingrese nombre de la categoria \n");
            fgets(catname,10,stdin);             /**para eliminar "\n" del switch*/
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
            while(op < 4){                  /** Menu de tag, usa los valores que entrege la funcion enterCat*/
                scanf("%d", &op);
                switch(op){
                case 1:
                    printf("case 1");
                    break;
                case 2:
                    printf("case 2");
                    break;
                case 3:
                    printf("case 3");
                    break;
                default: printf("Opcion no valida, intente nuevamentente \n");
                continue;
                }
            }
            break;
        default: printf("Opcion no valida, intente nuevamentente \n");
        continue;
        }
    }
    return 0;
}
