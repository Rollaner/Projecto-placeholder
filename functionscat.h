#ifndef functionscat_h
#define functionscat_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Map.h"
#include "list.h"

typedef struct cat cat;

typedef struct tag tag;

typedef struct fileStruct fileStruct;

void addDefaultTag(Map* tagMap);

long long stringHash(const void * key);

int stringEqual(const void * key1, const void * key2);

Map* loadCats ();

void catlist(Map* catMap);

void addCat(char * category,Map * catMap);

void deleteCat(char * category, Map * catMap);

void addFile(char* filename, cat* auxCat);

void loadFile(char* filename, cat* auxCat, list* recents);

void quickDelete(char* fielname, cat* auxCat);

void deleteFile(char* filename, cat* auxCat,list* recents);

cat* enterCat (char * category,Map* catMap);

void addTag (char * tags,cat* category);

void massTagging (char* tagName, cat* auxCat);

//void cat_taglist (cat* auxCat);

void taglist (char* tagName, cat* auxCat);

void deleteTag (char * name, cat* category);

cat* findLatest(Map* catMap, const char* fileName);

int recentList(list* latest);

void exportcats(Map* catMap);

void exportlatest(list* latest);

#endif // // functionscat_h //
