#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#define MAX (30+1)
//versione senza tentativo di normalizzazione in minuscolo

typedef enum{
    r_date, r_partenza, r_capolinea, r_codice, r_ricercalin, r_ricercadic, r_newfile, r_fine, r_errore
}comando_e;
typedef struct {
    char codTratta[MAX];
    char partenza[MAX];
    char destinazione[MAX];
    char data[8+3+1];
    char orapartenza[6+2+1];
    int ritardo;
}Tab;

int leggiComando();
void menuParola(Tab autom[], int c, int N);
void stampa(int N, Tab *pautom[]);
void ordinaDate(Tab *pautom[], int N);
void ordinaPartenza(Tab *pautom[],int N);
void ordinaArrivo(Tab *pautom[],int N);
void ordinaCodice(Tab *pautom[], int inizio, int fin);
int ricercaLineare(Tab *partenza[], int N, Tab *indici[]);
void ricercaDicotomica(Tab *partenza[],int inizio, int N, char parola[]);
int partition(Tab *pautom[], int inizio, int fin);
int newfile(Tab **autome);
int newfile(Tab **autome){
    int i;
    int N;
    FILE *in;
    Tab *automezzo;
    char nome[MAX];
    printf("Nome del file:\n");
    scanf("%s",nome);
    if ((in=fopen(nome,"r"))==NULL){
        printf("Errore nell'apertura del file di lettura\n");
    }
    fscanf(in,"%d",&N);
    automezzo=(Tab*)malloc(N*sizeof(Tab)); //nel heap, non viene distrutto finita la funzione
    for(i=0;i<N;i++){
        fscanf(in,"%s %s %s %s %s %*s %d",automezzo[i].codTratta, automezzo[i].partenza,
               automezzo[i].destinazione, automezzo[i].data, automezzo[i].orapartenza,&automezzo[i].ritardo);
    }
    *autome=automezzo;
    return N;
}
int main() {
    setbuf(stdout, 0); //permette di stampare tutto ciò che stampa il programma
    int command=-1,N=0;
    int i;
    Tab *automezzo;
    N=newfile(&automezzo);
    while(command!=r_fine){//date in formato anno/mese/giorno e orario in formato ore:minuti:secondi perfetti per stringcompare
        printf(" (MENU)  Scrivi in minuscolo:\n"
               "\"date\" per ordinare il vettore per date e orario\n" //inserction
               " \"partenza\" per ordinare per stazione di partenza\n" //shell
               "\"capolinea\" per ordinare per stazione di arrivo\n" // shell
               "\"cod\" per ordinare per codice di tratta\n" //quick sort?
               "\"lineare\" per cercare una tratta per stazione di partenza (anche parziale) in modo lineare\n"
               "\" dicotomica \" per cercare per stazione di partenza in maniera dicotomica\n"
               "\"new\" per scegliere un altro file \n"
               " \"fine\" per terminare il programma.\n");
        command=leggiComando();
        if(command==r_newfile){
            free(automezzo);
            N=newfile(&automezzo);//ora N ha il valore del file corrente
        }
        menuParola(automezzo,command, N);
    }
    return 0;
}

int leggiComando(){
    int c;
    char comando[12];
    char tabella[8][12] = {
            "date", "partenza", "capolinea",  "cod", "lineare", "dicotomica",  "new", "fine"
    };
    scanf("%s",comando);
    c=r_date;
    while(c<r_errore && strcmp(comando,tabella[c])!=0)
        c++;
    return (c);
}

void  menuParola(Tab autom[], int c, int N) {
    //Parameter is never used: capire come mai autom[] lo dà come parametro non usato quando viene usato nello switch
    Tab *orddata[N];//vettore di puntatori
    Tab *ordpartenza[N];
    Tab *ordarrivi[N];
    Tab *ordcod[N];
    Tab *ttindici[N];
    int i,fin;
    char paroladic[MAX];
    for(i=0;i<N;i++)
        ordpartenza[i]=&autom[i]; //aggancio puntatori a struct
    char rule='Y';
    switch (c) {
        case r_date:
            for(i=0;i<N;i++)
                orddata[i]=&autom[i]; //aggancio puntatori a struct
            ordinaDate(orddata, N);
            printf("Vorresti stampare il vettore ordinato per data e ora? Y/N\n");
            scanf("  %c", &rule);
            if(rule=='Y'){
                stampa(N,orddata);
            }
            break;
        case r_partenza:
            //aggancio pre modifica
            ordinaPartenza(ordpartenza,N);
            printf("Vorresti stampare il vettore ordinato per partenze? Y/N\n");
            scanf("  %c", &rule);
            if(rule=='Y')
                stampa(N,ordpartenza);
        case r_capolinea:
            for(i=0;i<N;i++)
                ordarrivi[i]=&autom[i]; //aggancio puntatori a struct
            ordinaArrivo(ordarrivi,N);
            printf("Vorresti stampare il vettore ordinato per arrivi? Y/N\n");
            scanf("  %c", &rule);
            if(rule=='Y')
                stampa(N,ordarrivi);
            break;
        case r_codice:
            for(i=0;i<N;i++)
                ordcod[i]=&autom[i]; //aggancio puntatori a struct
            ordinaCodice(ordcod, 0, N-1);
            printf("Vorresti stampare il vettore ordinato per codice tratta? Y/N\n");
            scanf("  %c", &rule);
            if(rule=='Y')
                stampa(N,ordcod);
            break;
        case r_ricercalin:
            fin=ricercaLineare(ordpartenza, N, ttindici);
            printf("Vorresti stampare le tratte trovate dalla ricerca lineare? Y/N\n");
            scanf("  %c", &rule);
            if(rule=='Y')
                stampa(fin,ttindici);
            break;
        case r_ricercadic:
            for(i=0;i<N;i++)
                ordpartenza[i]=&autom[i];
            ordinaPartenza(ordpartenza,N);
            printf("Inserisci il nome della stazione di partenza che cerchi, anche parziale (includi maiuscole, underscore etc..)\n");
            scanf("%s", paroladic);
            printf("Lista di tratte trovate:\n");
            ricercaDicotomica(ordpartenza, 0,N, paroladic); //sia ricerca lineare che dicotomica usa stesso vettore di indici
            break;
        case r_errore:
            printf("Si e' verificato un errore nella ricerca del comando, scrivi un comando corretto\n");
            break;
        default:printf("Termino il programma\n");
    }
}

void ordinaDate(Tab *pautom[], int N){
    //inserction sort (selection sort non stabile)
    int i,j;
    Tab *altrotemp;
    for(i=1;i<N;i++){
        altrotemp=pautom[i];
        j=i-1;
        while(  (j>=0 && strcmp(altrotemp->data,pautom[j]->data)<0)   ||   ( j>=0 && (strcmp(altrotemp->orapartenza,pautom[j]->orapartenza)<0) && (strcmp(altrotemp->data,pautom[j]->data)==0) )   ){
            pautom[j+1]=pautom[j];
            j--;
        }
        pautom[j+1]=altrotemp;
    }
}

void ordinaPartenza(Tab *pautom[],int N){
    //shell sort
    int h=1;
    int i,j;
    Tab *copytemp;
    while(h<N/3){
        h=3*h+1;
    }
    while (h>0){
        for(i=h;i<N;i++){
            j=i;
            copytemp=pautom[i];
            while(j>=h && strcmp(  copytemp->partenza, pautom[j-h]->partenza   )<0){
                pautom[j]=pautom[j-h];
                j-=h; // ==j=j-h;
            }
            pautom[j]=copytemp;
        }
        h=h/3;
    }
}

void ordinaArrivo(Tab *pautom[],int N){
    //shell sort
    int h=1;
    int i,j;
    Tab *copytemp;
    while(h<N/3){
        h=3*h+1;
    }
    while (h>0){
        for(i=h;i<N;i++){
            j=i;
            copytemp=pautom[i];
            while(j>=h && strcmp(copytemp->destinazione, pautom[j-h]->destinazione)<0){
                pautom[j]=pautom[j-h];
                j-=h; // ==j=j-h;
            }
            pautom[j]=copytemp;
        }
        h=h/3;
    }
}

void ordinaCodice(Tab *pautom[], int inizio, int fin){
    //quicksort wrapper
    int q;
    if(inizio>=fin)
        return;
    q=partition(pautom, inizio, fin);
    ordinaCodice(pautom,inizio, q-1);
    ordinaCodice(pautom,q+1,fin);
}

int ricercaLineare(Tab *partenza[], int N, Tab *indici[]){
    int i, k=0;
    char search[MAX];
    printf("Inserisci il nome della stazione di partenza che cerchi, anche parziale (includi maiuscole, underscore etc..)\n");
    scanf("%s", search);
    for(i=0;i<N;i++){
        if(strstr(partenza[i]->partenza,search)!=NULL) {
            indici[k] = partenza[i];
            k++;
        }
    }
    return k;
}

void ricercaDicotomica(Tab *partenza[],int inizio, int N, char parola[]){
    int i=(inizio+N)/2;
    int dx=N, sx=inizio, lung=(int)strlen(parola);
    int k=1;
    if(strstr(partenza[i]->partenza, parola)!=NULL){
        stampa(1,&partenza[i]);
        while(strstr(partenza[i-k]->partenza, parola)!=NULL){
            stampa(1,&partenza[i-k]);
            k++;
        }
        k=1;
        while(strstr(partenza[i+k]->partenza, parola)!=NULL){
            stampa(1,&partenza[i+k]);
            k++;
        }
    }
    else if (strncmp(partenza[i]->partenza, parola, lung)>0)
        ricercaDicotomica(partenza, inizio, i,parola);
    else if(strncmp(partenza[i]->partenza,parola, lung)<0)
        ricercaDicotomica(partenza,i,N,parola);
    else if(sx>=dx){
        printf("fine valori trovati\n");
        return;
    }
}
int partition(Tab *pautom[], int inizio, int fin){
    Tab *pivot=pautom[inizio], *temp; //scelgo come pivot il primo elemento disordinato sul vettore in cui lavoro
    int j=fin+1, i=inizio+1;
    while(i<j){
        while(strcmp(pautom[i]->codTratta,pivot->codTratta)<0){
            i++;
        }
        //++i == prima incremento i e poi lo uso, da capire come con questa versione non ordina
        while(strcmp(pautom[--j]->codTratta,pivot->codTratta)>0);
        temp=pautom[i];
        pautom[i]=pautom[j];
        pautom[j]=temp;
    }
    temp=pautom[i];
    pautom[i]=pautom[inizio];
    pautom[inizio]=temp;
    return i;
}

void stampa(int N, Tab *pautom[]){
    int i;
    for(i=0;i<N;i++){
        printf("codice %s da %s a %s il %s che parte in ora %s \n",pautom[i]->codTratta, pautom[i]->partenza,
               pautom[i]->destinazione, pautom[i]->data, pautom[i]->orapartenza);
    }
}

