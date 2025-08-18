

#ifndef INC_4PTI_2023_1_T_H
#define INC_4PTI_2023_1_T_H


typedef struct node {int ogg; struct node **figli; int n;} *nodo;
//vettore di figli al posto di link
//scambiato z con n
typedef struct ti *T;

int fu(nodo t, int tmax, nodo z);
int fuesame(nodo t, int tmax, nodo z);
int f(T t);
T getTree(); //aggiunta funzione per inizializzazione albero
nodo nodesetNull();

#endif //INC_4PTI_2023_1_T_H
