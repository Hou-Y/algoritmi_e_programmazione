#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 50+1
typedef struct itemoso item;
struct itemoso{
    char cod[5+1]; // includo terminatore stringa /0
    char nome[MAX], cognome[MAX];
    int data; //tengo sia la versione char che la versione int
    char datac[8+2+1];
    char via[MAX], city[MAX];
    int cap;
};

typedef struct node nodo;
struct node{
    item dato;
    nodo *next; //puntatore al prossimo elemento
};

typedef enum{
    tastiera, file, ric_cod,canc_date, stampa, fin, errore
}c_omando;

int leggiComando();
void menuParola(nodo **autom, int c);
int dateConverter(int gg, int mm, int aa);
void fromTastiera(nodo **autom);
nodo *createNode(nodo *prox, item curr);
nodo *put_one_in( nodo *autom, item x);
void display(nodo *autom);
void fromFile(nodo **autom,char nome[]);
void freeAll(nodo *inizio);
void ricCod(nodo *autom);
item canCod(char *nome, nodo **start, int *flag);
void canDate(nodo *autom);

int main() {
    setbuf(stdout, 0);
    int command=-1;
    struct node *testa=NULL;
    while(command!=fin) {
        printf(" (MENU)  Scrivi in minuscolo:\n"
               "\"tastiera\" per aggiungere un singolo nuovo elemento alla lista da tastiera\n"
               " \"file\" per aggiungere nuovi elementi alla lista da file\n"
               "\"codice\" per trovare un elemento tramite codice ed eventualmente cancellarlo\n"
               "\"date\" per cancellare tutti gli elementi comprese tra due date lette da tastiera nel formato gg/mm/aaaa\n"
               "\"stampa\" per stampare su file la lista corrente\n"
               " \"fine\" per terminare il programma.\n");
        command = leggiComando();
        menuParola(&testa,command);
    }
    freeAll(testa);
    return 0;
}

int leggiComando(){
    int c;
    char comando[9];
    char tabella[6][9] = {
            "tastiera", "file", "codice",  "date", "stampa", "fine"
    };
    scanf("%s",comando);
    c=tastiera;
    while(c<errore && strcmp(comando,tabella[c])!=0)
        c++;
    return (c);
}

void fromTastiera(nodo **autom){
    item x;
    int gg,mm,aa;
    printf("Scrivi: codice, nome, cognome, data di nascita (formato gg/mm/aaaa), via, citta' e CAP.\n");
    scanf("%s %s %s %s %s %s %d",
          x.cod,
          x.nome,
          x.cognome,
          x.datac,
          x.via,
          x.city,
          &(x.cap) );
    sscanf(x.datac,"%d/%d/%d", &gg, &mm, &aa);
    x.data=dateConverter(gg,mm,aa);
    *autom=put_one_in( *autom, x);
}

nodo *put_one_in( nodo *autom, item x){
    struct node *curr;
    if(autom==NULL || x.data <=(*autom).dato.data )
        return createNode(autom,x);//attaccamento in coda per il primo nodo creato
    for(curr=autom; (curr!=NULL  && curr->next!=NULL && (x).data>=(*(curr->next)).dato.data); curr=curr->next ){}
    curr->next=createNode(curr->next,x);
    return autom;
}

nodo *createNode(nodo *prox, item curr){//nodo successivo
    nodo *temp=(nodo*)malloc(sizeof(nodo));
    if(temp==NULL){
        return NULL;
    }
    temp->dato=curr;
    temp->next=prox;
    return temp;
}

int dateConverter(int gg, int mm, int aa){
    //anno*10000+mese*100+giorno
    return aa*10000+mm*100+gg;
}

void display(nodo *autom){
    FILE *out;
    nodo *i;
    if ((out=fopen("../ris.txt","w"))==NULL){
        //if ((in=fopen(nome,"r"))==NULL){
        printf("Errore nell'apertura del file di lettura\n");
    }
    for(i=autom;i!=NULL; i=i->next){
        fprintf(out,"%s %s %s %s %s %s %d\n",
                i->dato.cod,
                i->dato.nome,
                i->dato.cognome,
                i->dato.datac,
                i->dato.via,
                i->dato.city,
                i->dato.cap
        );
    }
    fclose(out);
}

void fromFile(nodo **autom,char nome[]){
    FILE *in;
    item info;
    int gg, mm, aa;
    //if ((in=fopen("../anag1.txt","r"))==NULL){
    if ((in=fopen(nome,"r"))==NULL){
        printf("Errore nell'apertura del file di lettura\n");
    }
    //da fare controllo se codici duplicati, nel caso siano presenti non leggerli proprio e saltare al prossimo record
    while (fscanf(in,"%s %s %s %s %s %s %d",
                  info.cod,
                  info.nome,
                  info.cognome,
                  info.datac,
                  info.via,
                  info.city,
                  &(info.cap) )==7) {
        sscanf(info.datac, "%d/%d/%d", &gg, &mm, &aa);
        info.data=dateConverter(gg,mm,aa);
        *autom=put_one_in( *autom, info);
    }
    fclose(in);
}

void ricCod(nodo *autom){
    char nome[5+1];
    item delete;
    int flag=0;
    printf("Inserisci il codice che stai cercando\n");
    scanf("%s", nome);
    delete=canCod(nome, &autom, &flag);
    if(flag==1){
        printf("Elemento cancellato:\n");
        printf("%s %s %s %d %s %s %d\n",
               delete.cod,
               delete.nome,
               delete.cognome,
               delete.data,
               delete.via,
               delete.city,
               delete.cap);
    }
}

item canCod(char *nome, nodo **start, int *flag) {
    item delete;
    char scelta = 'Y';
    nodo *i = *start, *prev;
    while (i != NULL && *flag == 0) {
        if (strcmp(i->dato.cod, nome) == 0) {
            *flag = 1;
            printf("Codice trovato, vorresti eliminarlo? Y/N\n");
            scanf(" %c", &scelta);
            if (scelta == 'Y') {
                if (i == *start) {
                    *start = i->next;
                    //se elemento cercato è in testa il puntatore slitta all'elemento dopo
                } else //se è in mezzo oppure in coda ho anche bisogno del puntatore->next del nodo precedente
                    prev->next = i->next;
                delete = i->dato;
                i->next = NULL;
                free(i);
                return delete;
            }
        }
        prev = i;
        i = i->next;
    }
    if (*flag == 0) {
        printf("Codice non trovato\n");
    }
    return (*start)->dato;
}

nodo *retCan(nodo **autom, int datafin, int datain){
    //free nel canData
    nodo *trav=*autom, *nextrav=*autom, *ncancel=NULL, **sntrv=NULL;
    if(*autom==NULL)
        return NULL;
    if((*autom)->dato.data>datafin)
        return NULL;

    while((nextrav!=NULL) && nextrav->dato.data<datain ){
        if(nextrav!=*autom)
            trav=trav->next;
        nextrav=nextrav->next;
    }
    ncancel=nextrav;//trav è il puntatore salvato che deve puntare fino a dopo la parte tagliata
    for(sntrv=&nextrav; ((*sntrv)!=NULL && (*sntrv)->dato.data<=datafin); nextrav=*sntrv, sntrv=&((*sntrv)->next)){}
    trav->next=*sntrv;
    if(nextrav!=NULL)
        nextrav->next=NULL;
    return ncancel;
}

void canDate(nodo *autom){
    int datain, datafin, gg, mm ,aa;
    char tmp[8+2+1];
    nodo *canceled;
    printf("scrivi data di inizio\n");
    scanf("%s", tmp);
    sscanf(tmp,"%d/%d/%d", &gg, &mm,  &aa );
    datain=dateConverter(gg,mm,aa);
    printf("scrivi la data di fine\n");
    scanf("%s", tmp);
    sscanf(tmp,"%d/%d/%d", &gg, &mm,  &aa );
    datafin=dateConverter(gg,mm,aa);
    canceled=retCan(&autom, datafin, datain);
    display(canceled);
    printf("Sul file ris.txt sono stati stampati le entrate appena cancellate\n");
    freeAll(canceled);
}

void menuParola(nodo **autom, int c){
    char nome[MAX];
    switch (c) {
        case tastiera:
            fromTastiera(autom);
            break;
        case file:
            printf("Srivi il nome del file:\n");
            scanf("%s", nome);
            fromFile(autom, nome);
            break;
        case ric_cod:
            ricCod(*autom);
            break;
        case canc_date:
            canDate(*autom);
            break;
        case stampa:
            display(*autom);
            break;
        case errore:
            printf("Si e' verificato un errore nella ricerca del comando, scrivi un comando corretto\n");
            break;
        case fin:
            printf("Chiusura programma\n");
            break;
    }
}

void freeAll(nodo *inizio){
    nodo *temp;//versione iterativa, come farne una ricorsiva?
    while(inizio!=NULL){
        temp=inizio;
        inizio=inizio->next;
        free(temp);
    }
}

