#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "Map.h"
#include "list.h"
#include "functionscat.h"

void loadmenu(){
    printf("                Bienvenido a\n\n"); //Portada del programa
    printf("                HOLDER \n\n\n\n");

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
                printf("Menu de categoria\n\n");
                printf("Crear nueva tag: Ingrese tecla [1]\n");
                printf("Agregar archivo a la categoria: Ingrese tecla [2]\n");
                printf("Agregar multiples archivos a la categoria: Ingrese tecla [3]\n");
                printf("Borrar una tag: Ingresar tecla [4]\n");
                printf("Mostrar archivos de una tag: Ingresar tecla [5]\n");
                printf("Cargar un archivo especifico [6]\n");
                printf("Eliminar un archivo especifico [7]\n");
                printf("Volver al menu de la principal: Ingresar tecla [8]\n\n");

}

int main()
{
    char op = 0;
    int switchop = 0;
    char op2 = 0;
    int switchop2 = 0;
    char buffer; //existe para eliminar basura.
    char* catname = calloc(30,sizeof(char)); //30 caracteres limite para nombres, lo corta si se pasa
    Map* catMap = loadCats();
    list* latest = loadLatest(catMap);
    loadmenu();
    recentList(latest);
    catList(catMap);
    char* fileName = calloc(30,sizeof(char));
    while(switchop != 5){          /** Menu de categoria, usa los valores que entrege el usuario (nombres)*/
        scanf("%c", &op);
        if((isalpha(op))||(isspace(op))){
                while(isalpha(op)||(isspace(op))){
                    printf("Entrada invalida, porfavor ingrese un numero\n");
                    scanf("%c", &op);
                }
        }
        switchop = op - '0'; // para convertir de char a int. '0' es el caracter cero. Todo esto es para que el menu no se rompa con caracteres
        switch(switchop){

        case 1: printf("Ingrese nombre de la categoria \n");
            fgets(catname,10,stdin);             /**para eliminar "\n" del switch*/
            scanf("%s",catname);
            addCat(catname,catMap);
            system("cls");
                op = '0';
                scanf("%c", &buffer); //elimina \n
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
                op = '0';
                scanf("%c", &buffer); //elimina \n
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
            char* tagName = calloc(30,sizeof(char));
                    loadcatmenu();
                    cat_taglist(auxCat);
                    while(switchop2 != -2){
                        scanf("%c", &op2);
                        if(isalpha(op2)||(isspace(op2))){
                            while(isalpha(op2)||(isspace(op2))){
                                printf("Entrada invalida, porfavor ingrese un numero \n");
                                scanf("%c", &op2);
                            }
                        }
                        switchop2 = op2 - '0';
                        switch(switchop2){
                        case 1: //crear nueva tag
                            printf("ingrese nombre tag\n");
                            fgets(tagName,10,stdin);
                            fgets(tagName,30,stdin);
                            if ((strlen(tagName) > 0) && (tagName[strlen (tagName) - 1] == '\n')){
                                tagName[strlen (tagName) - 1] = '\0';
                            }
 //                         system("cls");
                            addTag (tagName,auxCat);
                            op2 = '0';
                            scanf("%c", &buffer); //elimina basura
                            loadcatmenu();
                            cat_taglist(auxCat);
                            break;

                        case 2: //añadir archivo a tag
                            printf("ingrese nombre archivo\n");
                            fgets(fileName,10,stdin);
                            fgets(fileName,30,stdin);
                            if ((strlen(fileName) > 0) && (fileName[strlen (fileName) - 1] == '\n'))
                            fileName[strlen (fileName) - 1] = '\0';
                            addFile(fileName,auxCat);
                            op2 = '0';
                            scanf("%c", &buffer); //elimina basura
                            loadcatmenu();
                            cat_taglist(auxCat);
                            break;

                        case 3: //Añadir multiples archivos a una tag
                            printf("Ingrese nombre de la Tag\n");
                            fgets(tagName,10,stdin);
                            fgets(tagName,30,stdin);
                            if ((strlen(tagName) > 0) && (tagName[strlen (tagName) - 1] == '\n')){
                                tagName[strlen (tagName) - 1] = '\0';
                            }
                                if(strcmp(tagName,"\0") == 0){
                                    strcpy(tagName,"untagged");
                            }
                            massTagging(tagName, auxCat);
                            op2 = '0';
                            scanf("%c", &buffer); //elimina basura
                            loadcatmenu();
                            cat_taglist(auxCat);
                            break;

                        case 4: //Borrar una tag
                            printf("ingrese nombre tag\n");
                            fgets(tagName,10,stdin);
                            fgets(tagName,30,stdin);
                            if ((strlen(tagName) > 0) && (tagName[strlen(tagName) - 1] == '\n')){
                                tagName[strlen(tagName) - 1] = '\0';
                            }
 //                           system("cls");
                            deleteTag (tagName,auxCat);
                            op2 = '0';
                            scanf("%c", &buffer); //elimina basura
                            loadcatmenu();
                            cat_taglist(auxCat);
                            break;

                        case 5: //Mostrar archivos de una tag
                            printf("ingrese nombre tag\n");
                            fgets(tagName,10,stdin);
                            fgets(tagName,30,stdin);
                            if ((strlen(tagName) > 0) && (tagName[strlen (tagName) - 1] == '\n'))
                                tagName[strlen (tagName) - 1] = '\0';
                            taglist(tagName,auxCat);
                            op2 = '0';
                            scanf("%c", &buffer); //elimina basura
                            loadcatmenu();
                            cat_taglist(auxCat);
                            break;

                        case 6: // cargar archivo especifico
                            printf("ingrese nombre archivo\n");
                            fgets(fileName,10,stdin);
                            fgets(fileName,30,stdin);
                            if ((strlen(fileName) > 0) && (fileName[strlen (fileName) - 1] == '\n'))
                            fileName[strlen (fileName) - 1] = '\0';
                            loadFile(fileName,auxCat,latest);
                            op2 = '0';
                            scanf("%c", &buffer); //elimina basura
                            loadcatmenu();
                            cat_taglist(auxCat);
                            break;

                        case 7:
                            printf("ingrese nombre archivo\n");
                            fgets(fileName,10,stdin);
                            fgets(fileName,30,stdin);
                            if ((strlen(fileName) > 0) && (fileName[strlen (fileName) - 1] == '\n'))
                            fileName[strlen (fileName) - 1] = '\0';
                            deleteFile(fileName,auxCat,latest);
                            op2 = '0';
                            scanf("%c", &buffer); //elimina basura
                            loadcatmenu();
                            cat_taglist(auxCat);
                            break;

                        case 8: //Volver al menu de la categoria
                            switchop2 = -2;
                            break;
                            default: printf("Opcion no valida, intente nuevamentente \n");
                                     op2 = '0';
                                     scanf("%c", &buffer); //elimina basura
                                     loadcatmenu();
                                     cat_taglist(auxCat);
                            continue;
                        }
                    }
            system("cls");
            switchop2 = 0;
            scanf("%c", &buffer);
            loadmenu();
            recentList(latest);
            catList(catMap);
            break;

        case 4:     system("cls");
                    if(recentList(latest)){
                    printf("Ingrese nombre archivo\n");
                    fgets(fileName,10,stdin);
                    fgets(fileName,30,stdin);
                    if ((strlen(fileName) > 0) && (fileName[strlen (fileName) - 1] == '\n'))
                            fileName[strlen (fileName) - 1] = '\0';
                    cat* recentCat = findLatest(catMap,fileName);
                    if(recentCat == NULL){
                        printf("Archivo no existe, porfavor intente nuevamente \n");
                        op = '0';
                        scanf("%c", &buffer); //elimina \n
                        system("cls");
                        loadmenu();
                        recentList(latest);
                        catList(catMap);
                        break;
                    }
                    loadFile(fileName,recentCat,latest);
                }
                op = '0';
                scanf("%c", &buffer); //elimina \n
                system("cls");
                loadmenu();
                recentList(latest);
                catList(catMap);
                break;

        case 5: system("cls"); /**Con esta se sale del programa*/
                exportcats(catMap);
                exportlatest(latest);
                printf ("\n\n\n\n\n                HASTA PRONTO!!!\n\n\n\n");
                exit(0);

        default: printf("Opcion no valida, intente nuevamentente \n");
                 scanf("%c",&buffer);
                continue;
        }
    }
    return 0;
}
