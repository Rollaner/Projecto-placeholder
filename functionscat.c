#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "functionscat.h"
#include "functionstag.h"
#include "Map.h"
#include "list.h"

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
    cat* aux = malloc (sizeof(cat));
    aux = searchMap(catMap,category);
    if(aux != NULL){
        printf("categoria %s ya existe, porfavor intente con otro nombre \n",aux->name);
        getchar();
        getchar(); /*porque demonios requiere dos y el otro solo 1?, solo el dios del spaghetti lo sabe*/
        return;
    }
    ToAdd->name = calloc(30,sizeof(char));                  // nombre para presentar categoria
    ToAdd->name = category;
    //addDefaultTag(ToAdd);
    insertMap(catMap,category,ToAdd);                       // añadido a mapa global de categorias
    return;     /** falta revisar que no se dupliquen un if*/
}

void catList(Map* catMap){
    cat* tempcat = firstKeyMap(catMap);
    printf("%s  \n",tempcat->name);
    while(tempcat!= NULL){
        tempcat = nextKeyMap(catMap);
        if(tempcat == NULL)
            break;
        printf("%s \n",tempcat->name);
    }
}

void deleteCat(char * category, Map * catMap){
    cat* ToDel = malloc(sizeof(cat));
    void* ToDelTag;
    char* ToDelFile = calloc(30,sizeof(char));
    ToDel = searchMap(catMap,category);
    if(ToDel == NULL){
        printf("Categoria no encontrada, revise datos ingresados\n");
        getchar();
        return;
    }
    printf("Esta accion es permanente, confirmar? y/n\n");
    char confirm = 'n';
    scanf("%c", &confirm);
    if(confirm == 'y'){
        if((ToDel->fileMap != NULL)&&(ToDel->tagMap != NULL)){
            ToDelTag = firstMap(ToDel->tagMap);
            while (ToDelTag != NULL){
               // listCleanup(ToDelTag);
                free(ToDelTag);
                ToDelTag = nextMap(ToDel->tagMap);
            }
            while (ToDelFile != NULL){
                free(ToDelFile);
                ToDelFile = nextMap(ToDel->fileMap);
            }
            removeAllMap(ToDel->fileMap);
            removeAllMap(ToDel->tagMap);
        }
        free(eraseKeyMap(catMap,category));

    }
    return;
}

cat* enterCat(char * category,Map* catMap) {
    system("cls");
    cat* aux = malloc(sizeof(cat));
    aux = searchMap(catMap,category);
    if(aux == NULL){
        printf("Categoria no encontrada, revise datos ingresados \n");
        return NULL;
    }
    printf("Ha ingresado exitosamente a la categoria %s \n\n", category);
    printf("Presione ENTER para continuar:\n");

    fflush(stdin);
    getchar();

    system("cls");
    return aux;
}

void addFile(char* filename, cat* auxCat){
    printf("Ingrese nombre etiqueta, ingrese enter para saltar este paso\n");
    char* tag = calloc(30,sizeof(char));
    fgets(tag,10,stdin);
    fgets(tag,30,stdin);
    if ((strlen(tag) > 0) && (tag[strlen (tag) - 1] == '\n'))
        tag[strlen (tag) - 1] = '\0';
    if(strcmp(tag,"\0") == 0){
       strcpy(tag,"untagged");
    }
    //auxtag se actualiza immediatamente a lo que ingrese el usuario o "untagged"
    //tag* auxtag //El linker no funciona, hay que revisar porque antes de continuar. esta variable se usa para acceder a la lista enlazada de la tag en cuestion
    /** if(auxtag == NULL){
        auxtag->file_list = list_create_empty;
        auxtag->name = malloc(30,sizeof(char));
        insertMap(auxCat->tagMap, tag, auxtag);*/
    char* auxDupped = calloc(30, sizeof(char));
    auxDupped = searchMap(auxCat->fileMap,filename);
    if(auxDupped != NULL){
        printf("Archivo ya existe, desea añadirlo a otra etiqueta? y/n");
        char confirm;
        scanf("%c", &confirm);
        if(confirm == 'y'){
            if(strcmp(tag,"untagged") == 0){
                printf("Ingrese una tag valida anted de proceder.");
                return;
            }
            //auxtag //acceder a la tag hacer operaciones de lista.
        }
        return;
    }else{
        insertMap(auxCat->fileMap,filename,filename);
        //auxtag acceder operaciones de lista.
        char* fileCheck = calloc(30,sizeof(char));
        fileCheck = searchMap(auxCat->fileMap,filename);
        if(fileCheck == NULL)
            printf("welp");
        else
        printf("archivo %s ingresado presione una tecla para continuar\n",fileCheck);
        getchar();
        return;
    }
}

void loadFile(char* filename, cat* auxCat){
    char* aux = calloc(30,sizeof(char));
    aux = searchMap(auxCat->fileMap,filename);
    if(aux != NULL){
        printf("Cargando archivo %s (no en realidad, es solo prueba de concepto) (presione cualquier tecla para continuar)",aux);
        getchar();
        return;
    }else{
        printf("Archivo no encontrado, intente nuevamente (presione cualquier tecla para proceder)");
        getchar();
        system("cls");
        return;
    }
}

void deleteFile(char* filename, cat* auxCat){
    char* aux = calloc(30,sizeof(char));
    char confirm = 'n';
    aux = searchMap(auxCat->fileMap,filename);
    if(aux != NULL){
        printf("Esta accion es permanente, desea continuar? y/n\n",aux);
        scanf("%c", &confirm);
        if (confirm == 'y'){
            eraseKeyMap(auxCat->fileMap,filename);
            //free(aux); lo rompe por algun motivo.
            printf("Archivo eliminado\n");
            getchar();
        }
        return;
    }else{
        printf("Archivo no encontrado, revise datos ingresados (presione cualquier tecla para proceder)\n");
        getchar();
        return;
    }
}

void exportcats(Map* catMap){
    FILE* fp = fopen("Files\\Categories-OUTPUT.csv","w");
    cat* catExporter = malloc(sizeof(cat));
    catExporter = firstKeyMap(catMap);
    while(catExporter != NULL){
        fprintf(fp,"%s,%s-tags,%s-data\n",catExporter->name,catExporter->name,catExporter->name);
        char * fileOpener = calloc(100,sizeof(char));
        strcat(fileOpener,"Files\\");
        strcat(fileOpener,catExporter->name);
        strcat(fileOpener,"-tags.csv");
        FILE* tagPointer = fopen(fileOpener,"w");
        /** cositas (es decir esportar la data)*/
        fclose(tagPointer);
        strcpy(fileOpener,"\0");
        strcat(fileOpener,"Files\\");
        strcat(fileOpener,catExporter->name);
        strcat(fileOpener,"-data.csv");
        FILE* dataPointer = fopen(fileOpener,"w");
        /** cositas*/
        fclose(dataPointer);
        strcpy(fileOpener,"\0");
        catExporter = nextKeyMap(catMap);
    }
    //FILE* tagPointer =
    //FIlE* dataPointer =
}
