#include "Map.h"
#include "list.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "functionscat.h"

struct tag{
    Map* catMap;
    Map* fileMap;
    char* nameTag;
};

typedef struct tag tag;

void addTag (char * category,Map * tagMap);

void deleteTag (char * tags, Map * tagMap);

void enterTag (char * tags);
