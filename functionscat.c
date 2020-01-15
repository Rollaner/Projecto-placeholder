#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "functionscat.h"
#include "functionstag.h"
#include "Map.h"

void importData(Map* catMap, Map* tagMap, Map* albumMap);

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

const char *get_csv_field (char * tmp, int i) {
    //se crea una copia del string tmp
    char * line = _strdup (tmp);
    const char * tok;
    for (tok = strtok (line, ","); tok && *tok; tok = strtok (NULL, ",\n")) {
        if (!--i) {
            return tok;
        }
    }
    return NULL;
}

struct cat{
    Map* tagMap;
    Map* fileMap;
    char* name;
};

/** actualmente solo se esta trabajando a nivel de categoria, por lo tanto las tags solo seran strings de momento */

Map* loadCats(){
    Map* CatMap = createMap(stringHash,stringEqual);
    FILE* Catfile = fopen("Files\\Categories.csv","r");
    char* String = calloc(100,sizeof(char));                    //y crea un artista nuevo de ser necesario, ademas crea los albumes ya pre-escritos y los rellena
    while(fgets(String,100,Catfile) != NULL){
        cat* catLoader = malloc(sizeof(cat));
        catLoader->name = calloc(30, sizeof(30,sizeof(char)));
        catLoader->fileMap = createMap(stringHash,stringEqual);
        catLoader->tagMap = createMap(stringHash,stringEqual);
        strcpy(catLoader->name,get_csv_field(String,1));
        insertMap(CatMap,catLoader->name,catLoader);
        //printf("%s \n",catLoader->name);
    }
    return CatMap;
}

void addCat(char * category,Map * catMap) {
    cat* ToAdd = malloc(sizeof(cat));
    ToAdd->fileMap = createMap(stringHash,stringEqual);     // inicializa variables struct cat
    ToAdd->tagMap = createMap(stringHash,stringEqual);
    insertMap(catMap,category,ToAdd);                       // añadido a mapa global de categorias
    ToAdd->name = calloc(30,sizeof(char));                  // nombre para presentar categoria
    ToAdd->name = category;
    return;     /** falta revisar que no se dupliquen un if*/
}

void catList(Map* catMap){
    cat* tempcat = firstMap(catMap);
    printf("%s  \n",tempcat->name);
    while(tempcat!= NULL){
        tempcat = nextMap(catMap);
        if(tempcat == NULL)
            break;
        printf("%s \n",tempcat->name);
    }
}

void deleteCat(char * category, Map * catMap){
    printf("Esta accion es permanente, confirmar? y/n");
    char confirm = 'N';
    scanf("%c", &confirm);
    if(confirm == 'y'){
        cat* ToDel = malloc(sizeof(cat));
        removeAllMap(ToDel->fileMap);
        removeAllMap(ToDel->tagMap);
        ToDel->name = calloc(30,sizeof(char));
        strcpy(ToDel->name, category); //Indica que cat borrar
        eraseKeyMap(catMap,ToDel->name);

    }
    return;
}

void enterCat(char * category) {

    system("cls");

    printf("Ha ingresado exitosamente a la categoria %s \n\n", category);
    printf("Presione ENTER para continuar:\n");

    fflush(stdin);
    getchar();

    system("cls");


    return;
}
