#include "invArray.h"

struct invArray_s{
    //ho copie infinite di ogni oggetto
    int maxInv;
    inv_t *vettInv;
    //da qualche parte il numero di elementi dentro l'array
};

invArray_t invArray_init(){
    invArray_t head;
    head=malloc(1 * sizeof(invArray_t));
    head->maxInv=0;
    return head;
}

void invArray_free(invArray_t invArray){
    free(invArray->vettInv);
    free(invArray);
}

void invArray_read(FILE *fp, invArray_t invArray){
    int i;
    fscanf(fp, " %d", &(invArray->maxInv));
    (invArray->vettInv)=malloc((invArray->maxInv)* sizeof(struct inv_s));
    for(i=0;i<invArray->maxInv; i++){
        inv_read(fp, &(invArray->vettInv[i]));
        //invArray puntatore al vettore vettInv (in questo caso primo elemento del vettore vettInv)
        //ma ogni oggetto è uno slot nel vettore == NON posso passare il primo elemento a meno che non voglia
        //salvarmi anche l'indice corrente e fare un ciclo fino allo slot desiderato
        //inv_read(fp, invArray->vettInv); sarebbe come passare  &(invArray->vettInv[0])
        //e ricordati di mallocarla prima di tentare di darle un valore
    }
}

void invArray_print(FILE *fp, invArray_t invArray){
    int i;
    for(i=0; i<invArray->maxInv; i++){
        inv_print(fp, &(invArray->vettInv[i]));
    }
}

void invArray_printByIndex(FILE *fp, invArray_t invArray, int index){
    inv_print(fp, &(invArray->vettInv[index]));
}

inv_t *invArray_getByIndex(invArray_t invArray, int index){
    return &(invArray->vettInv[index]);
}

int invArray_searchByName(invArray_t invArray, char *name){
    int i;
    for(i=0; i<invArray->maxInv; i++){
        if(!strcmp(name, invArray->vettInv[i].nome))
            return i;
    }
    return -1;
}