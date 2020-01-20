#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "functionscat.h"
#include "Map.h"
#include "list.h"

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

struct tag{
    list* file_list;
    char* nameTag;
};

struct fileStruct{
    Map* file_tagmap;
    char* name;
};

void addDefaultTag(Map* tagMap){
    tag* ToAdd = malloc(sizeof(tag));
    ToAdd->file_list = list_create_empty();
    ToAdd->nameTag = calloc(30,sizeof(char));
    strcpy(ToAdd->nameTag,"untagged");
    insertMap(tagMap,"untagged",ToAdd);
    return;

}

Map* loadCats(){
    Map* CatMap = createMap(stringHash,stringEqual);
    FILE* Catfile = fopen("Files\\Categories.csv","r");
    int i = 2;
    char* dataFile = calloc(50,sizeof(char));
    char* tagFile = calloc(50,sizeof(char));
    char* String = calloc(100,sizeof(char));    //<----string de datos de la categoria
    char* dataStream = calloc(210,sizeof(char)); // carga los datos del archivo -data
    char* tagStream = calloc(30,sizeof(char));
    char* dataTagStream = calloc(30,sizeof(char)); // para cargar tags de dataStream
    tag* auxTag = malloc(sizeof(tag));
    while(fgets(String,100,Catfile) != NULL){
        cat* catLoader = malloc(sizeof(cat));       /** inicializa variables de la categoria */
        catLoader->name = calloc(30, sizeof(char));
        catLoader->fileMap = createMap(stringHash,stringEqual);
        catLoader->tagMap = createMap(stringHash,stringEqual);
        strcpy(catLoader->name,get_csv_field(String,1));
        insertMap(CatMap,catLoader->name,catLoader);
        strcat(tagFile,"Files\\");
        strcat(tagFile,get_csv_field(String,2));
        strcat(tagFile,".csv");             //son para concatenar la ubicacion del archivo a cargar esto aplica a todos los strcat del programa
        FILE* tagLoader = fopen(tagFile,"r");
        while(fgets(tagStream,30,tagLoader)!= NULL){
            tag* tagStruct_loader = malloc(sizeof(tag));
            tagStruct_loader->file_list = list_create_empty();
            tagStruct_loader->nameTag = calloc(30,sizeof(char));
            strcpy(tagStruct_loader->nameTag,get_csv_field(tagStream,1));
            insertMap(catLoader->tagMap,tagStruct_loader->nameTag,tagStruct_loader);
        }
        fclose(tagLoader);
        strcpy(tagFile,"\0");
        strcat(dataFile,"Files\\");                 //ambos strcat son para
        strcat(dataFile,get_csv_field(String,3));  //compilar la string para ubicar el archivo
        strcat(dataFile,".csv");
        FILE* dataLoader = fopen(dataFile,"r");
        while(fgets(dataStream,150,dataLoader) != NULL){
            fileStruct* fileLoader = malloc(sizeof(fileStruct));        /**inicializa variables de archivo*/
            fileLoader->file_tagmap = createMap(stringHash,stringEqual);
            fileLoader->name = calloc(30,sizeof(char));
            strcpy(fileLoader->name,get_csv_field(dataStream,1));
            for(i= 2; get_csv_field(dataStream,i) != NULL; i++){
                strcpy(dataTagStream,get_csv_field(dataStream,i));
                auxTag = searchMap(catLoader->tagMap,dataTagStream);
                insertMap(fileLoader->file_tagmap,auxTag->nameTag,auxTag);
                list_push_back(auxTag->file_list,fileLoader);
            }
            insertMap(catLoader->fileMap,fileLoader->name,fileLoader);
        }
        fclose(dataLoader);
        strcpy(dataFile,"\0"); //resetea string para ubicar archivo
        //printf("%s \n",catLoader->name);
    }
    fclose(Catfile);
    return CatMap;
}

list* loadLatest(Map* catMap){
    list* latest_loader = list_create_empty();
    FILE* latestFile = fopen("Files\\Latest.csv","r");
    char* dataStream = calloc(50,sizeof(char));
    cat* auxCat; fileStruct* auxfile;
    while(fgets(dataStream,50,latestFile)!= NULL){
            auxCat = findLatest(catMap,get_csv_field(dataStream,1));
            if(auxCat != NULL){
                auxfile = searchMap(auxCat->fileMap,get_csv_field(dataStream,1));
                list_push_front(latest_loader,auxfile);
            }else{
                continue;
            }
    }
    fclose(latestFile);
    return latest_loader;
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
        return;
    }
    ToAdd->name = calloc(30,sizeof(char));                  // nombre para presentar categoria
    strcpy(ToAdd->name,category);
    addDefaultTag(ToAdd->tagMap);
    insertMap(catMap,ToAdd->name,ToAdd);                       // añadido a mapa global de categorias
    return;
}

void cat_taglist (cat* auxCat){
    tag* tempTag = firstMap(auxCat->tagMap);
    if(tempTag == NULL){
        printf("La categoria no posee etiquetas \n");
        return;
    }
    printf("Etiquetas de la categoria: \n");
    while(tempTag!= NULL){
        printf("%s  \n",tempTag->nameTag);
        tempTag = nextMap(auxCat->tagMap);
        if(tempTag == NULL)
            break;
    }
    return;
}

void taglist (char* tagName, cat* auxCat){
    tag* auxTag = searchMap(auxCat->tagMap,tagName);
    int i = 1;
    if(auxTag == NULL){
     printf("Tag ingresada no existe, revise datos\n");
     return;
    }
    fileStruct* auxFile = list_first(auxTag->file_list);
    while(auxFile != NULL){
        printf("%d) %s \n", i, auxFile->name);
        i++;
        auxFile = list_next(auxTag->file_list);
    }
    printf("Total de archivos con etiqueta %s: %d\n",auxTag->nameTag,i-1);
    return;
}

void catList(Map* catMap){
    printf("Lista categorias: \n");

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
    cat* ToDel = malloc(sizeof(cat));
    tag* ToDelTag = malloc(sizeof(tag));
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
        if(ToDel->tagMap != NULL){
            ToDelTag = firstMap(ToDel->tagMap);
            while (ToDelTag != NULL){
                free(ToDelTag);
                ToDelTag = NULL;
                ToDelTag = nextMap(ToDel->tagMap);
            }
            removeAllMap(ToDel->tagMap);
        }
        if(ToDel->fileMap != NULL){
            while (ToDelFile != NULL){
                free(ToDelFile);
                ToDelFile = NULL;
                ToDelFile = nextMap(ToDel->fileMap);
            }
            removeAllMap(ToDel->fileMap);
        }
        free(ToDel);
        ToDel = NULL;
        eraseKeyMap(catMap,category);
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

void addTag (char * tags,cat* category){
    tag* ToAdd = malloc(sizeof(tag));
    ToAdd->file_list = list_create_empty();
    tag* aux = malloc(sizeof(tag));
    aux = searchMap(category->tagMap,tags);
    if(aux != NULL){
        printf("tag %s ya existe, porfavor intente con otro nombre \n",aux->nameTag);
        return;
    }
    ToAdd->nameTag = calloc(30,sizeof(char));
    strcpy(ToAdd->nameTag,tags);
    insertMap(category->tagMap,ToAdd->nameTag,ToAdd);
    printf("tag '%s' agregada exitosamente!, presione enter para continuar", ToAdd->nameTag);
    return;
}

void massTagging (char* tagName, cat* auxCat){
    char* fileName = calloc(30,sizeof(char));
    tag* auxtag = searchMap(auxCat->tagMap,tagName);
    fileStruct* fileCheck = malloc(sizeof(fileStruct)); //para comprobar que la insercion fue exitosa
    if(auxtag == NULL){
        auxtag = malloc(sizeof(tag));
        auxtag->file_list = list_create(NULL);
        auxtag->nameTag = calloc(30,sizeof(char));
        strcpy(auxtag->nameTag,tagName);
        insertMap(auxCat->tagMap,auxtag->nameTag,auxtag);
    } // confirma que la tag no existe y en ese caso la crea.
    char confirmChar = 'y';
    while(confirmChar == 'y'){
        printf("Ingrese el nombre del archivo\n");
        fgets(fileName,30,stdin);
        if ((strlen(fileName) > 0) && (fileName[strlen (fileName) - 1] == '\n'))
            fileName[strlen (fileName) - 1] = '\0';
            fileStruct* auxDupped = calloc(30, sizeof(fileStruct));
        auxDupped = searchMap(auxCat->fileMap,fileName); //revisa que el archivo no exista, en caso de existir, toma su valor para modificarlo
        if(auxDupped != NULL){
            if(strcmp(tagName,"untagged") == 0){
                printf("El archivo ingresado ya existe, revise datos ingresados y/o ingrese una tag valida antes de proceder.\n");
                printf("Desea continuar agregando archivos? y/n\n");
                scanf("%c",&confirmChar);
                continue;
            }
            list_push_front(auxtag->file_list,auxDupped); //inserta archivo en la lista de la tag.
            insertMap(auxDupped->file_tagmap,auxtag->nameTag,auxtag); //inserta la tag en el mapa del archivo
            insertMap(auxCat->tagMap, auxtag->nameTag, auxtag); //ingresa auxtag al mapa de tags
            fileCheck = searchMap(auxCat->fileMap,fileName);
            if(fileCheck == NULL){
                printf("Operation Failed, return to menu\n");
            }
            else{
                printf("archivo %s ingresado exitosamente\n",fileCheck->name);
            }
        }
        else
        {
            fileStruct* toBeAdded = malloc(sizeof(fileStruct));
            toBeAdded->name = calloc(30,sizeof(char));
            strcpy(toBeAdded->name,fileName);
            toBeAdded->file_tagmap = createMap(stringHash,stringEqual);
            insertMap(auxCat->fileMap,toBeAdded->name,toBeAdded);   //crea un nuevo archivo y lo inserta al mapa de archivos
            list_push_back(auxtag->file_list,toBeAdded);
            insertMap(toBeAdded->file_tagmap,auxtag->nameTag,auxtag);
            insertMap(auxCat->tagMap, auxtag->nameTag, auxtag);
            fileCheck = searchMap(auxCat->fileMap,fileName);
            if(fileCheck == NULL){
                printf("Operation Failed, return to menu\n");
            }
            else{
                printf("archivo %s ingresado exitosamente\n",fileCheck->name);
            }
        }
        //addFile(fileName,auxCat); // requiere trabajo.
        printf("Desea continuar agregando archivos? y/n\n");
        scanf("%c",&confirmChar);
        getchar();
    }
    return;
}

void deleteTag (char * name, cat* category){

    tag* currentTag = searchMap(category->tagMap, name);
    tag* Untagged = searchMap(category->tagMap, "untagged");
    char confirmDelete = 'n';
    if(currentTag == NULL){
        printf("Tag no existe, revise datos ingresados\n");
        return;
    }
    else{
        tag* tagCleaner = malloc(sizeof(tag));
        fileStruct* fileAux = list_pop_front(currentTag->file_list);
        while(fileAux != NULL){
            if(strcmp(name,"untagged") == 0){
                printf("Esta operacion eliminara definitivamente cualquier archivo con esta etiqueta\n");
                printf("Confirme la operacion: y/n");
                scanf("%c", &confirmDelete);
                if(confirmDelete != 'y')
                    return;
                tagCleaner = eraseKeyMap(fileAux->file_tagmap,name);
                free(tagCleaner);
                tagCleaner = NULL;
                if(emptyMap(fileAux->file_tagmap)){
                    free(fileAux);
                    fileAux = NULL;
                }
                fileAux = list_pop_front(currentTag->file_list);
                continue;
            }
            tagCleaner = eraseKeyMap(fileAux->file_tagmap,name);
            free(tagCleaner);
            tagCleaner = NULL;
            if(emptyMap(fileAux->file_tagmap)){
                list_push_back(Untagged->file_list,fileAux);
                insertMap(fileAux->file_tagmap,"untagged",Untagged);
            }
            fileAux = list_pop_front(currentTag->file_list);
        }
        eraseKeyMap(category->tagMap,name);
        currentTag = NULL;
        free(currentTag);
    }
    printf("Operacion exitosa \n");
    return;
}

cat* findLatest(Map* catMap, const char* fileName){
    cat* recentCat = malloc(sizeof(cat));
    recentCat = firstMap(catMap);
    while(recentCat != NULL){
        if(searchMap(recentCat->fileMap,fileName) == NULL)
            recentCat = nextMap(catMap);
    }
    return recentCat;
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
        printf("Archivo ya existe, desea agregarlo a otra etiqueta? y/n");
        char confirm = 'n';
        scanf("%c", &confirm);
        confirm = tolower(confirm);
        if(confirm == 'y'){
            if(strcmp(tagName,"untagged") == 0){
                printf("Ingrese una tag valida antes de proceder.");
                return;
            }
            list_push_front(auxtag->file_list,auxDupped); //inserta archivo en la lista de la tag.
            insertMap(auxDupped->file_tagmap,auxtag->nameTag,auxtag); //inserta la tag en el mapa del archivo
            insertMap(auxCat->tagMap, auxtag->nameTag, auxtag); //ingresa auxtag al mapa de tags
        }
        return;
    }else{
        fileStruct* toBeAdded = malloc(sizeof(fileStruct));
        toBeAdded->name = calloc(30,sizeof(char));
        toBeAdded->file_tagmap = createMap(stringHash,stringEqual);
        insertMap(auxCat->fileMap,filename,toBeAdded);   //crea un nuevo archivo y lo inserta al mapa de archivos
        list_push_back(auxtag->file_list,toBeAdded);
        insertMap(toBeAdded->file_tagmap,auxtag->nameTag,auxtag);
        insertMap(auxCat->tagMap, auxtag->nameTag, auxtag);
        strcpy(toBeAdded->name,filename);
        fileStruct* fileCheck = malloc(sizeof(fileStruct)); //para comprobar que la insercion fue exitosa
        fileCheck = searchMap(auxCat->fileMap,filename);
        if(fileCheck == NULL)
            printf("Operation Failed, return to menu");
        else
        printf("archivo %s ingresado presione una tecla para continuar\n",fileCheck->name);
        return;
    }
}

int recentList(list* latest){
    int i = 1;
    fileStruct* filename_recents = malloc(sizeof(fileStruct));
    filename_recents = list_first(latest);
    if(filename_recents != NULL){
        printf("Tus 5 archivos mas recientes son: \n");
        while(filename_recents != NULL){
            printf("Archivo %d: %s \n",i,filename_recents->name);
            filename_recents = list_next(latest);
        }
    }else{
        printf("No hay archivos recentes. \n\n");
        return 0;
    }
    printf("\n");
    return 1;
}

void loadFile(char* filename, cat* auxCat, list* recents){
    fileStruct* aux = malloc(sizeof(fileStruct));
    fileStruct* recent_duplicate = malloc(sizeof(fileStruct));
    aux = searchMap(auxCat->fileMap,filename);
    if(aux != NULL){
        printf("Cargando archivo %s (presione enter para continuar)",aux->name);
        recent_duplicate = list_first(recents);
        while(recent_duplicate != NULL){
            if(recent_duplicate == aux){
                getchar();
                return;
            }
            recent_duplicate = list_next(recents);
        }
        list_push_front(recents,aux);
        if(list_size(recents) > 5){
            list_pop_back(recents);
        }
        return;
    }else{
        printf("Archivo no encontrado, intente nuevamente (presione enter para proceder)");
        return;
    }
}

void deleteFile(char* filename, cat* auxCat){
    char* aux = calloc(30,sizeof(char));
    char confirm = 'n';
    aux = searchMap(auxCat->fileMap,filename);
    if(aux != NULL){
        printf("Esta accion es permanente, desea continuar? y/n\n");
        scanf("%c", &confirm);
        if (confirm == 'y'){
            eraseKeyMap(auxCat->fileMap,filename);
            printf("Archivo eliminado\n");
        }
        return;
    }else{
        printf("Archivo no encontrado, revise datos ingresados (presione cualquier tecla para proceder)\n");
        return;
    }
}

void exportcats(Map* catMap){
    FILE* fp = fopen("Files\\Categories.csv","w");
    cat* catExporter = malloc(sizeof(cat));
    fileStruct* fileAux = malloc(sizeof(fileStruct));
    tag* tagAux = malloc(sizeof(tag));
    tag* tagListAux = malloc(sizeof(tag));
    catExporter = firstKeyMap(catMap);
    while(catExporter != NULL){
        fprintf(fp,"%s,%s-tags,%s-data\n",catExporter->name,catExporter->name,catExporter->name);
        char * fileOpener = calloc(100,sizeof(char));
        strcat(fileOpener,"Files\\");
        strcat(fileOpener,catExporter->name);
        strcat(fileOpener,"-tags.csv");
        FILE* tagPointer = fopen(fileOpener,"w");
        tagAux = firstMap(catExporter->tagMap);
        while(tagAux!=NULL){
            fprintf(tagPointer,"%s,\n",tagAux->nameTag);
            tagAux = nextMap(catExporter->tagMap);
        }
        fclose(tagPointer);
        strcpy(fileOpener,"\0");
        strcat(fileOpener,"Files\\");
        strcat(fileOpener,catExporter->name);
        strcat(fileOpener,"-data.csv");
        FILE* dataPointer = fopen(fileOpener,"w");
        fileAux = firstMap(catExporter->fileMap);
        while(fileAux!=NULL){
            fprintf(dataPointer,"%s,",fileAux->name);
            tagListAux = firstMap(fileAux->file_tagmap);
            while(tagListAux!= NULL){
                fprintf(dataPointer,"%s,",tagListAux->nameTag);
                tagListAux = nextMap(fileAux->file_tagmap);
            }
            fprintf(dataPointer,"\n");
            fileAux = nextMap(catExporter->fileMap);
        }
        fclose(dataPointer);
        strcpy(fileOpener,"\0");
        catExporter = nextKeyMap(catMap);
    }
    return;
}

void exportlatest(list* latestList){
    FILE* latest_exporter = fopen("Files//Latest.csv","w");
    fileStruct* auxfile = list_first(latestList);
    while(auxfile != NULL){
        fprintf(latest_exporter,"%s,\n",auxfile->name);
    }
    fclose(latest_exporter);
    return;
}
