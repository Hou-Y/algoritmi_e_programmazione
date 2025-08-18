#include "pgList.h"

struct pgList_s{ //finisce la definizione della struct nel .c
    //il client deve arrangiarsi con solo i puntatori della struttura incompleta dentro il .h
    struct nodoPg_s * testa; //verso opposto di next
    int indice; //valore di ritorno della pg_read
    //pg_t item; accedo all'item tramite indice, item scorporato
    struct nodoPg_s * coda; //next è un puntatore (freccia nascosta, vedi pgList.h)
};

pgList_t pgList_init(){ // //creo un head per la lista dei personaggi
    pgList_t head; //head è un puntatore nonostante non lo abbia dichiarato con un * davanti per com'è fatta la struct
    head=malloc(sizeof(pgList_t));
    head->testa=NULL;
    head->coda=NULL;
    head->indice=0;
    //usando calloc, quello mi azzera anche i puntatori a NULL? Non ha pulito niente (forse)
    return head;
}

void pgList_read(FILE *fp, pgList_t pgList){
    //situazione iniziale: un singolo nodo (head)
    //ne creo uno nuovo
    pg_t pg;
    while(pg_read(fp, &pg)){ //ritorna 1 se letto con successo, quando arrivo a 0 ho finito il file
        //salvo il pg in un nuovo nodo e lo inserisco nella lista
        pgList_insert(pgList, pg);
    } //ora come ora il pgList->coda è vuota, riempirla con l'ultimo nodo, posso avere due puntatori allo stesso nodo!

}

void pgList_free(pgList_t pgList){
    //dentro questo dovrei chiamare anche il invArray free??
    //meglio modificare il gdr.c
    //dove sta la free dell'inventario?????????????
}


void pgList_insert(pgList_t pgList, pg_t pg){
    //inserimento in "testa" (dopo la testa)
    int check=0;
    nodoPg_t *temp=(nodoPg_t*)malloc(sizeof(nodoPg_t));
    if(temp==NULL)
        printf("Finita memoria in creazione nodo personaggio\n");
    if(pgList->testa==NULL)
        check=1;
    temp->character=pg;
    temp->next=pgList->testa; //pgList->testa non viene sostituita dall'ultimo input ricevuto
    pgList->testa=temp;
    pgList->indice++;
    if(check==1){
        pgList->coda=temp;
    }
}

void pgList_remove(pgList_t pgList, char* cod){
    nodoPg_t *i, *prev;
    int flag=0;
    for(i=pgList->testa; i!=NULL && !flag; prev=i, i=i->next){
        if( !strcmp(i->character.cod,cod) ){
            flag=1;
            if(i==pgList->testa)
                pgList->testa=i->next;
            else
                prev->next=i->next;
            i->next=NULL;
            free(i);
        }
    }
    //se scrivo le cose dopo al flag=1 fuori dal for c'è un i=i->next in più!
    pg_clean(&(i->character));
}

pg_t *pgList_searchByCode(pgList_t pgList, char* cod){
    //NON cancellare il nodo qua, cerca solo il codice e DOPO cancella
    nodoPg_t *i, *prev;
    //int flag=0;
    //for(i=pgList->testa; i!=NULL && !flag; prev=i, i=i->next){
    for(i=pgList->testa; i!=NULL; prev=i, i=i->next){
        if( !strcmp(i->character.cod,cod) ){
            //flag=1;
            return &(i->character);
        }
    }
    return NULL;
    /*if(i==pgList->testa)
        pgList->testa=i->next;
    else
        prev->next=i->next;
        */
}


void pgList_print(FILE *fp, pgList_t pgList, invArray_t invArray){
    nodoPg_t *j;
        //i problemi spuntano da quando chiami equipArray che devi farlo per indice
        for(j=pgList->testa; j!=NULL; j=j->next){
            pg_print(fp, &(j->character), invArray );
            stat_print(fp, &(j->character.eq_stat), 1);
            fprintf(fp, "\n");
        }
}