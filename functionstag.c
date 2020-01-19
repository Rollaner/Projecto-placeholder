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


void enterTag (char * tags);


void listCleanup(tag* Tag){
    char* aux = calloc(30, sizeof(char));
    aux = list_first(Tag->file_list);
    while(aux != NULL){
        free(aux);
        aux = list_next(Tag->file_list);
        }
    return;
}
