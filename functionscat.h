#ifndef functionscat_h
#define functionscat_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Map.h"

typedef struct cat cat;

//Map* loadCats (FILE* catfile);

void addCat (char * category,Map * catMap);

void deleteCat (char * category, Map * catMap);

void enterCat (char * category);

#endif // // functionscat_h //
