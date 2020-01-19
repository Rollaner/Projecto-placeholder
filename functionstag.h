#ifndef functionstag_h
#define functionstag_h
#include "Map.h"
#include "list.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct tag tag;

typedef struct fileStruct fileStruct;

void addDefaultTag(Map* tagMap);

void enterTag (char * tags);

void taglist(Map* catMap);


void listCleanup(tag* Tag);


#endif //  functionstag_h
