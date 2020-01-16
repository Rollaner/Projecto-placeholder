#include "Map.h"
#include "list.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "functionstag.h"

struct tag{
    list* file_list;
    char* nameTag;
};

void addTag (char * tags,Map * tagMap){
    tag* ToAdd = malloc(sizeof(tag));
    ToAdd->fileMap = createMap(stringHash,stringEqual);
    insertMap(tagMap,tags,ToAdd);
    ToAdd->name = calloc(30,sizeof(char));
    ToAdd->name = tags;
    return;

}

void deleteTag (char * name, Map * tagMap){

    tag* currentTag = searchMap(tagMap, name);

    if(currentTag == NULL){
     printf("Error de datos\n");
    }
    else{
        tag* currentTag = list_pop_front(currentTag->tagMap);
        catMap* currentCat = searchMap(catMap, currentCat->catName);
        while (currentTag != NULL){
            eraseKeyMap(currentCat->tagMap->currentTag->name);

            if(strcmp(currentTag->tagMap,currentCat->name)!= 0)
                eraseKeyMap(tagMap,currentTag->name);
                currentTag = list_pop_front(currentTag->tagMap);
            }

        eraseKeyMap(catMap,currentCat->name);
    }

}

void enterTag (char * tags);

void taglist (Map* tagMap){

    tag* tempTag = firstMap(tagMap);
    printf("%s  \n",tempTag->name);
    while(tempTag!= NULL){
        tempTag = nextMap(tagMap);
        if(tempTag == NULL)
            break;
        printf("%s \n",tempTag->name);
    }

}


void listCleanup(tag* Tag){
    char* aux = calloc(30, sizeof(char));
    aux = list_first(Tag->file_list);
    while(aux = NULL){
        free(aux);
        aux = list_next(Tag->file_list);
        }
    return;
}
