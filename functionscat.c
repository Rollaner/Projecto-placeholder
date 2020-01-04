#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "functionscat.h"
//#include "functionstag.h"
#include "Map.h"

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

struct cat{
    Map* tagMap;
    Map* fileMap;
    char* name;
};

/** actualmente solo se esta trabajando a nivel de categoria, por lo tanto las tags solo seran strings de momento */


void addCat(char * category,Map * catMap) {
    cat* ToAdd = malloc(sizeof(cat));
    ToAdd->fileMap = createMap(stringHash,stringEqual);
    ToAdd->tagMap = createMap(stringHash,stringEqual);
    insertMap(catMap,category,ToAdd);
    ToAdd->name = calloc(30,sizeof(char));
    ToAdd->name = category;
    return;
}

void deleteCat(char * category, Map * catMap) {
    printf("dis is test");
    return;
}

void enterCat(char * category) {
    printf(":3");
    return;
}
