#ifndef functionstag_h
#define functionstag_h
#include "Map.h"
#include "list.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "functionscat.h"

typedef struct tag tag;

void addTag (char * category,Map * tagMap);

void deleteTag (char * tags, Map * tagMap);

void enterTag (char * tags);

void taglist(Map* catMap);


#endif //  functionstag_h
