#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "functionscat.h"
#include "Map.h"
#include "list.h"
#include "queue.h"

int recentList(list* latest){
    int i = 1;
    char* filename_recents = calloc(30,sizeof(char));
    filename_recents = list_first(latest);
    if(filename_recents != NULL){
        printf("Tus 5 archivos mas recientes son: \n"); /** Solo como prueba de concepto */
        while(filename_recents != NULL){
            printf("Archivo %d: %s\n",i,filename_recents);
            filename_recents = list_next(latest);
        }
    }else{
        printf("No hay archivos recentes. \n\n");
        return 0;
    }
    return 1;
}

void loadmenu(){
    printf("                Bienvenido a\n\n"); //Portada del programa
    printf("                PLACEHOLDER \n\n\n\n");

    printf("Ingrese numero de la operacion deseada: \n"); /**Menu principal del programa*/
    printf("1) Agregar categoria \n");
    printf("2) Eliminar categoria \n");
    printf("3) Ingresar a categoria \n");
    printf("4) Acceder a archivo reciente\n");
    printf("5) Salir \n\n");
}

void loadcatmenu(){

                 /** Menu de tag, usa los valores que entrege la funcion enterCat*/
                system("cls");
                printf("Menu de tags\n\n");
                printf("Crear nueva tag: Ingrese tecla [1]\n");
                printf("A�adir archivo a la categoria: Ingrese tecla [2]\n");
                printf("A�adir multiples archivos a la categoria: Ingrese tecla [3]\n");
                printf("Borrar una tag: Ingresar tecla [4]\n");
                printf("Mostrar archivos de una tag: Ingresar tecla [5]\n");
                printf("Cargar un archivo especifico [6]\n");
                printf("Eliminar un archivo especufico [7]\n");
                printf("Volver al menu de la principal: Ingresar tecla [8]\n");

}

int main()
{
    char op = 0;
    int switchop = 0;
    char op2 = 0;
    int switchop2 = 0;
    int i;
    char* catname = calloc(30,sizeof(char));
    //Map* catMap = createMap(stringHash,stringEqual); /** mapa para categorias*/
    //Map* tagMap = createMap(stringHash,stringEqual);         /**estan en functionscat.h y .c*/
    Map* catMap = loadCats();
    list* latest = list_create_empty();
    loadmenu();
    recentList(latest);
    catList(catMap);
    while(switchop != 5){          /** Menu de categoria, usa los valores que entrege el usuario (nombres)*/
        scanf("%c", &op);
        if(isalpha(op)){
                while(isalpha(op)){
                    printf("Entrada invalida, porfavor ingrese un numero\n");
                    getchar();
                    scanf("%c", &op);
                }
        }
        switchop = op - '0';
        switch(switchop){

        case 1: printf("Ingrese nombre de la categoria \n");
            fgets(catname,10,stdin);             /**para eliminar "\n" del switch*/
            scanf("%s",catname);
            addCat(catname,catMap);
            system("cls");
            loadmenu();
            recentList(latest);
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
            recentList(latest);
            catList(catMap);
            break;
        case 3: printf("Ingrese nombre categoria \n");
            fgets(catname,10,stdin);
            fgets(catname,30,stdin);
            if ((strlen(catname) > 0) && (catname[strlen (catname) - 1] == '\n'))
            catname[strlen (catname) - 1] = '\0';
            printf("Entrando a categoria %s ", catname);
            cat* auxCat = enterCat(catname,catMap);
            if (auxCat == NULL){
                getchar();
                system("cls");
                loadmenu();
                recentList(latest);
                catList(catMap);
                break;
            }
            char* fileName = calloc(30,sizeof(char));
                    loadcatmenu();
                    while(switchop2 != -2){
                        scanf("%c", &op2);
                        if(isalpha(op2)){
                            while(isalpha(op2)){
                                printf("Entrada invalida, porfavor ingrese un numero");
                                scanf("%c", &op2);
                            }
                        }
                        switchop2 = op2 - '0';
                        switch(switchop2){
                        case 1: //crear nueva tag

 //                           system("cls");
 //                           addTag (char * category,Map * tagMap);
                            loadcatmenu();
                            break;

                        case 2: //a�adir archivo a tag
                            printf("ingrese nombre archivo\n");
                            fgets(fileName,10,stdin);
                            fgets(fileName,30,stdin);
                            if ((strlen(fileName) > 0) && (fileName[strlen (fileName) - 1] == '\n'))
                            fileName[strlen (fileName) - 1] = '\0';
                            addFile(fileName,auxCat);
                            loadcatmenu();
                            break;

                        case 3: //A�adir multiples archivos a una tag

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
                            loadFile(fileName,auxCat,latest);
                            loadcatmenu();
                            break;

                        case 7:
                            printf("ingrese nombre archivo\n");
                            fgets(fileName,10,stdin);
                            fgets(fileName,30,stdin);
                            if ((strlen(fileName) > 0) && (fileName[strlen (fileName) - 1] == '\n'))
                            fileName[strlen (fileName) - 1] = '\0';
                            deleteFile(fileName,auxCat);
                            loadcatmenu();
                            break;

                        case 8: //Volver al menu de la categoria
                            switchop2 = -2;
                            break;
                            default: printf("Opcion no valida, intente nuevamentente \n");
                                     getchar();
                                     loadcatmenu();
                            continue;
                        }
                    }
            system("cls");
            switchop2 = 0;
            loadmenu();
            recentList(latest);
            catList(catMap);
            break;

        case 4: if(recentList(latest)){
                    printf("Ingrese nombre archivo\n");
                    char* recentFile = calloc(30,sizeof(char));
                    fgets(fileName,10,stdin);
                    fgets(fileName,30,stdin);
                    if ((strlen(fileName) > 0) && (fileName[strlen (fileName) - 1] == '\n'))
                            fileName[strlen (fileName) - 1] = '\0';
                    cat* recentCat = findLatest(catMap,fileName);
                    loadFile(fileName,recentCat,latest);
                }
                else{
                    printf("No hay archivos recientes\n");
                }
                system("cls");
                loadmenu();
                recentList(latest);
                catList(catMap);
                op = 0;
                break;

        case 5: system("cls"); /**Con esta se sale del programa*/
                exportcats(catMap);
                printf ("\n\n\n\n\n                HASTA PRONTO!!!\n\n\n\n");
                exit(0);

        default: printf("Opcion no valida, intente nuevamentente \n");
                getchar();
                continue;
        }
    }
    return 0;
}
