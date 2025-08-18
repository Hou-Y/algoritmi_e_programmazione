#include "T.h" //aggiunto inclusione della libreria
#include <stdlib.h>
#include <stdio.h>

struct ti{nodo root; nodo z;};
//è stato usato 2 al posto di n, modificato da vettore di dimensione fissa a vettore dinamica
//spostato z con figli

static nodo fillnode(int rootogg, int howmany);

int fuesame(nodo t, int tmax, nodo z){
        int a, b;
        if(t==z)
            return tmax-1;
        if(t->ogg>=0){
            a=fuesame(t->figli[0],tmax+1,z );
            b=fuesame(t->figli[1], tmax+1,z );
        }
        else{
            a=fuesame(t->figli[0], 0, z);
            //modificato valore da tmax a zero e aggiunta una parentesi tonda
            b=fuesame(t->figli[1], 0, z);
        }
        if(a>b)
            tmax=a;
        else if(b>=a)
            tmax=b;
        return tmax;
}


int f(T t){
    int max; //tolta tm variabile inutilizzata
    //versione fatta durante l'esame funzionanate solo per alberi binari
    max= fuesame(t->root, 0, t->z);
    printf("con versione per alberi binari %d\n", max);
    //versione generalizzata
    return fu(t->root, 0 , t->z)-1; //sostituito root a link tipo passato alla funzione fu
}

T getTree(){
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
}

nodo fillnode(int rootogg, int howmany) {
    nodo node = (nodo) malloc(sizeof(struct node));
    node->ogg = rootogg;
    node->n=howmany;
    node->figli= (nodo*) malloc(howmany* sizeof(nodo));
    return node;
}

nodo nodesetNull(){
    nodo new=NULL;
    return new;
}

//aggiunto passaggio nodo z
int fu(nodo t, int tmax, nodo z){ //aggiunto passaggio nodo fittizio
    int a, b, i; //Aggiunto contatore i per ciclo di lunghezza variabile
    if(t==z)
        return tmax-1;
    for(i=0; i<t->n; i++){
        if(t->ogg>=0){
            //da confronto binario a ciclo
            b=fu(t->figli[i], tmax+1, z);
            if(b>tmax) tmax=b;}
        else{ //aggiunte parentesi tonde
            b=fu(t->figli[i], 0, z);
            if(b>tmax) tmax=b;

        }
    }//tolta comparazione tra a b
    return tmax;
}

