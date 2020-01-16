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
    int op2 = 0;

    char* catname = calloc(30,sizeof(char));
    //Map* catMap = createMap(stringHash,stringEqual); /** mapa para categorias*/
    //Map* tagMap = createMap(stringHash,stringEqual);         /**estan en functionscat.h y .c*/

    Map* catMap = loadCats();

    loadmenu();
    catList(catMap);
    while(op < 5){          /** Menu de categoria, usa los valores que entrege el usuario (nombres)*/
        scanf("%d", &op);
        switch(op){

        case 1: printf("Ingrese nombre de la categoria \n");
            fgets(catname,10,stdin);             /**para eliminar "\n" del switch*/
            scanf("%s",catname);
            addCat(catname,catMap);
            system("cls");
            loadmenu();
            catList(catMap);
            break;
        case 2: printf("Ingrese nombre de la categoria a eliminar \n ");
            fgets(catname,10,stdin);
            fgets(catname,30,stdin);
            if ((strlen(catname) > 0) && (catname[strlen (catname) - 1] == '\n'))
            catname[strlen (catname) - 1] = '\0';
            deleteCat(catname,catMap);
            system("cls");
            loadmenu();
            catList(catMap);
            break;
        case 3: printf("ingrese nombre cat \n");
            fgets(catname,10,stdin);
            fgets(catname,30,stdin);
            if ((strlen(catname) > 0) && (catname[strlen (catname) - 1] == '\n'))
            catname[strlen (catname) - 1] = '\0';
            printf("entrando a categoria %s ", catname);
            cat* auxCat = enterCat(catname,catMap);
            if (auxCat == NULL){
                getchar();
                system("cls");
                loadmenu();
                catList(catMap);
                break;
            }
            char* fileName = calloc(30,sizeof(char));
                    loadcatmenu();
                    while(op2 != -2){
                        scanf("%d", &op2);
                        switch(op2){
                        case 1: //crear nueva tag

 //                           system("cls");
 //                           addTag (char * category,Map * tagMap);
                            loadcatmenu();
                            break;

                        case 2: //añadir archivo a tag
                            printf("ingrese nombre archivo\n");
                            fgets(fileName,10,stdin);
                            fgets(fileName,30,stdin);
                            if ((strlen(fileName) > 0) && (fileName[strlen (fileName) - 1] == '\n'))
                            fileName[strlen (fileName) - 1] = '\0';
                            addFile(fileName,auxCat);
                            loadcatmenu();
                            break;

                        case 3: //Añadir multiples archivos a una tag

                            loadcatmenu();
                            break;

                        case 4: //Borrar una tag

                            loadcatmenu();
                            break;

                        case 5: //Mostrar archivos de una tag

                            loadcatmenu();
                            break;

                        case 6: // cargar archivo especifico
                            printf("ingrese nombre archivo\n");
                            fgets(fileName,10,stdin);
                            fgets(fileName,30,stdin);
                            if ((strlen(fileName) > 0) && (fileName[strlen (fileName) - 1] == '\n'))
                            fileName[strlen (fileName) - 1] = '\0';
                            loadFile(fileName,auxCat);
                            loadcatmenu();
                            break;

                        case 7: //Volver al menu de la categoria
                            op2 = -2;
                            break;
                            default: printf("Opcion no valida, intente nuevamentente \n");
                                     loadcatmenu();
                            continue;
                        }
                    }
            system("cls");
            loadmenu();
            catList(catMap);
            break;

        case 4: system("cls"); /**Con esta se sale del programa*/
                exportcats(catMap);
                printf ("\n\n\n\n\n                HASTA PRONTO!!!\n\n\n\n");
                exit(0);

        default: printf("Opcion no valida, intente nuevamentente \n");
        continue;
        }
    }
    return 0;
}

void loadmenu(){
    printf("                Bienvenido a\n\n"); //Portada del programa
    printf("                PLACEHOLDER \n\n\n\n");

    printf("Ingrese numero de la operacion deseada: \n"); /**Menu principal del programa*/
    printf("1) Agregar categoria \n");
    printf("2) Eliminar categoria \n");
    printf("3) Ingresar a categoria \n");
    printf("4) Salir \n\n");

    printf("Tus 5 archivos mas recientes son: \n"); /** Solo como prueba de concepto */
    printf("Archivo 1. ");
    printf("Archivo 2. ");
    printf("Archivo 3. ");
    printf("Archivo 4. ");
    printf("Archivo 5. \n");

    printf("Lista categorias: \n");
}

void loadcatmenu(){

                 /** Menu de tag, usa los valores que entrege la funcion enterCat*/
                system("cls");
                printf("Menu de tags\n\n");
                printf("Crear nueva tag: Ingrese tecla [1]\n");
                printf("Añadir archivo a la categoria: Ingrese tecla [2]\n");
                printf("Añadir multiples archivos a la categoria: Ingrese tecla [3]\n");
                printf("Borrar una tag: Ingresar tecla [4]\n");
                printf("Mostrar archivos de una tag: Ingresar tecla [5]\n");
                printf("Cargar un archivo especifico [6]\n");
                printf("Volver al menu de la principal: Ingresar tecla [7]\n");

}
