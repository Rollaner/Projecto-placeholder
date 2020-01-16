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
            enterCat(catname);

            printf("Estas son las acciones que usted puede realizar: \n"); /** Este es el menu dentro de la categoría*/
            printf("Ver archivos de la categoria: Ingresar tecla [1].\n");
            printf("Ver menu de tags: Ingresar tecla [2].\n");
            printf("Salir al menu principal: Ingresar tecla [3].\n");


            while(op != -1){                  /** Menu de tag, usa los valores que entrege la funcion enterCat*/
                scanf("%d", &op);
                switch(op){
                case 1:
                    system("cls");
                    printf("case 1");
                    break;
                case 2:
                    system("cls");
                    printf("Menu de tags\n\n");
                    printf("Crear nueva tag: Ingrese tecla [1]\n");
                    printf("Añadir archivo a una tag: Ingrese tecla [2]\n");
                    printf("Añadir multiples archivos a una tag: Ingrese tecla [3]\n");
                    printf("Borrar una tag: Ingresar tecla [4]\n");
                    printf("Mostrar archivos de una tag: Ingresar tecla [5]\n");
                    printf("Volver al menu de la categoria: Ingresar tecla [6]\n");

                    while(op != -1){
                        switch(op){
                        case 1: //crear nueva tag

 //                           system("cls");
 //                           addTag (char * category,Map * tagMap);

                            break;

                        case 2: //añadir archivo a tag

                            system("cls");
                            break;

                        case 3: //Añadir multiples archivos a una tag

                            system("cls");
                            break;

                        case 4: //Borrar una tag

                            system("cls");
                            break;

                        case 5: //Mostrar archivos de una tag

                            system("cls");
                            break;

                        case 6: //Volver al menu de la categoria

                            system("cls");
                            break;
                        }
                    }

                    printf("case 2");
                    break;
                case 3:
                    system("cls");
                    op = -1;
                    break;
                default: printf("Opcion no valida, intente nuevamentente \n");
                continue;
                }
            }
            system("cls");
            loadmenu();
            catList(catMap);
            break;

        case 4: system("cls"); /**Con esta se sale del programa*/
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
