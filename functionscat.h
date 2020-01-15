#ifndef functionscat_h
#define functionscat_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Map.h"

typedef struct cat cat;

long long stringHash(const void * key);

int stringEqual(const void * key1, const void * key2);

Map* loadCats ();

void catlist(Map* catMap);

void addCat (char * category,Map * catMap);

void deleteCat (char * category, Map * catMap);

void enterCat (char * category); /**que es category?*/


#endif // // functionscat_h //
