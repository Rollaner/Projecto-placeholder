#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "functionscat.h"
//#include "functionstag.h"
#include "Map.h"

typedef struct cat{
    Map* tagMap;
    Map* fileMap;
};

/** actualmente solo se esta trabajando a nivel de categoria, por lo tanto las tags solo seran strings de momento */


void addCat(char * category,Map * catMap) {
    printf("hewwo");
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
