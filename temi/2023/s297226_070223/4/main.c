#include <stdio.h>
#include <stdlib.h>
#include "T.h"

int main() {
    int a;
    T t=getTree();
    a=f(t);
    printf("cammino più lungo %d\n" , a);
    return 0;
}

/*T getTree(){
    T t = malloc(sizeof(T));
    t->root= fillnode(1,2);
    t->root->figli[0]= fillnode(-12,2);
    t->root->figli[1]= fillnode(0,1);
    t->root->figli[0]->figli[0] = fillnode(2,0);
    t->root->figli[0]->figli[1] = fillnode(-3, 1);
    t->root->figli[1]->figli[0] = fillnode(6,0);
    t->root->figli[0]->figli[1]->figli[0] = fillnode(7,0);
    t->z=nodesetNull();
    return t;
}*/
