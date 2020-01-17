#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "functionstag.h"
#include "functionscat.h"
#include "functionstag.c"
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
    addDefaultTag(ToAdd);
    insertMap(catMap,category,ToAdd);                       // añadido a mapa global de categorias
    return;     /** falta revisar que no se dupliquen un if*/
}

void catList(Map* catMap){
    printf("Lista categorias: \n");

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
    tag* ToDelTag;
    fileStruct* ToDelFile = calloc(30,sizeof(char));
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

                ToDelTag = NULL;
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
    char* tagName = calloc(30,sizeof(char));
    tag* auxtag = malloc(sizeof(tag));
    fgets(tagName,30,stdin);
    if ((strlen(tagName) > 0) && (tagName[strlen (tagName) - 1] == '\n'))
        tagName[strlen (tagName) - 1] = '\0';
    if(strcmp(tagName,"\0") == 0){
       strcpy(tagName,"untagged");
    }
    auxtag = searchMap(auxCat->tagMap,tagName); //para cerciorarse que la tag no exista, si existe se actualiza adentro de ella
    if(auxtag == NULL){
        auxtag = malloc(sizeof(tag));
        auxtag->file_list = list_create(NULL);
        auxtag->nameTag = calloc(30,sizeof(char));
        strcpy(auxtag->nameTag,tagName);
    }       //para este punto ya existe una tag, solo falta insertarla en el mapa.
    fileStruct* auxDupped = calloc(30, sizeof(fileStruct));
    auxDupped = searchMap(auxCat->fileMap,filename); //revisa que el archivo no exista, en caso de existir, toma su valor para modificarlo
    if(auxDupped != NULL){
        printf("Archivo ya existe, desea añadirlo a otra etiqueta? y/n");
        char confirm = 'n';
        scanf("%c", &confirm);
        confirm = tolower(confirm);
        if(confirm == 'y'){
            if(strcmp(tagName,"untagged") == 0){
                printf("Ingrese una tag valida antes de proceder.");
                return;
            }
            list_push_front(auxtag->file_list,auxDupped); //inserta archivo en la lista de la tag.
            insertMap(auxDupped->file_tagmap,tagName,auxtag); //inserta la tag en el mapa del archivo
            insertMap(auxCat->tagMap, tagName, auxtag); //ingresa auxtag al mapa de tags
        }
        return;
    }else{
        fileStruct* toBeAdded = malloc(sizeof(fileStruct));
        toBeAdded->name = calloc(30,sizeof(char));
        toBeAdded->file_tagmap = createMap(stringHash,stringEqual);
        insertMap(auxCat->fileMap,filename,toBeAdded);   //crea un nuevo archivo y lo inserta al mapa de archivos
        list_push_back(auxtag->file_list,toBeAdded);
        insertMap(toBeAdded->file_tagmap,tagName,auxtag);
        insertMap(auxCat->tagMap, tagName, auxtag);
        strcpy(toBeAdded->name,filename);
        fileStruct* fileCheck = malloc(sizeof(fileStruct)); //para comprobar que la insercion fue exitosa
        fileCheck = searchMap(auxCat->fileMap,filename);
        if(fileCheck == NULL)
            printf("Operation Failed, return to menu");
        else
        printf("archivo %s ingresado presione una tecla para continuar\n",fileCheck->name);
        getchar();
        return;
    }
}

void loadFile(char* filename, cat* auxCat, list* recents){
    char* aux = calloc(30,sizeof(char));
    aux = searchMap(auxCat->fileMap,filename);
    if(aux != NULL){
        printf("Cargando archivo %s (presione cualquier tecla para continuar)",aux);
        list_push_front(recents,filename);
        getchar();
        return;
    }else{
        printf("Archivo no encontrado, intente nuevamente (presione cualquier tecla para proceder)");
        getchar();
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
    char* fileAux = calloc(30,sizeof(char));
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
        fileAux = firstKeyMap(catExporter->fileMap);
        while(fileAux!=NULL){
            fprintf(dataPointer,"%s,\n",fileAux);
            fileAux = nextKeyMap(catExporter->fileMap);
        }
        fclose(dataPointer);
        strcpy(fileOpener,"\0");
        catExporter = nextKeyMap(catMap);
    }
    //FILE* tagPointer =
    //FIlE* dataPointer =
    return;
}
