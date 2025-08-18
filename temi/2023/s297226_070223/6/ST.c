
#include "ST.h"


ST STinit(int E){
    ST tmp=malloc(sizeof(struct st_s));
    tmp->n=E;
    tmp->item_l=malloc(E*sizeof(struct item_s));
    return tmp;
}

void STinsert( char id[], ST st, int i){
    strcpy(st->item_l[i].name, id);
    st->item_l[i].index=i;
}

int STsearch(ST st, char* key){
    int i;
    for (i = 0; i  < st->n; i++)
        if (strcmp(key, st->item_l[i].name)==0)
            return i;
    return -1;
}

char *STsearch_getname(ST st, int num_ord){
    return (st->item_l[num_ord].name);
}

void STfree(ST st){
    free(st->item_l);
    free(st);
}