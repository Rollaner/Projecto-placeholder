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


void deleteTag (char * name, Map * tagMap){

    tag* currentTag = searchMap(tagMap, name);
    tag* Untagged = searchMap(tagMap, "untagged");
    fileStruct* fileAux = list_pop_front(currentTag->file_list);
    if(currentTag == NULL){
     printf("Error de datos\n");
    }
    else{
        //while(fileAux != NULL){
            //if()

        //}
        eraseKeyMap(tagMap,name);
        free(currentTag);
        currentTag = NULL;
    }
}

void enterTag (char * tags);

void taglist (Map* tagMap){

    tag* tempTag = firstMap(tagMap);
    printf("%s  \n",tempTag->nameTag);
    while(tempTag!= NULL){
        tempTag = nextMap(tagMap);
        if(tempTag == NULL)
            break;
        printf("%s \n",tempTag->nameTag);
    }

}


void listCleanup(tag* Tag){
    char* aux = calloc(30, sizeof(char));
    aux = list_first(Tag->file_list);
    while(aux != NULL){
        free(aux);
        aux = list_next(Tag->file_list);
        }
    return;
}
