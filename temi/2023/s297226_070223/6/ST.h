
#ifndef LAB9ES1_ST_H
#define LAB9ES1_ST_H
#define MAX 30
#include<stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct st_s *ST;
typedef struct item_s { char name[MAX+1]; int index;}item;

struct st_s{
    int n;
    item *item_l;
};

ST STinit(int E);
void STinsert( char id[], ST st, int i);
int STsearch(ST st, char* key);
char *STsearch_getname(ST st, int num_ord);
void STfree(ST st);

#endif //LAB9ES1_ST_H
