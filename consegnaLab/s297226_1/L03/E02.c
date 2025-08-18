#include<stdio.h>
#include<stdlib.h>
#define MAX (255+1)

typedef struct{
    char nomestr[MAX];
    int key;
}istanza;

typedef struct{//per ogni amico
    istanza *namelist; //la lista di canzoni scelta dall'amico
    int nScelte;
} tab;

void Princ_mol(int pos, tab *canzoni,int *ris,int N);

int main(){
    setbuf(stdout, 0);
    FILE *in;
    int N, i, n,j;
    tab *tabella;
    //versione con solo int per poi accedere all'altra struttura tramite ris
    int *ris;
    //indice:  amico n
    //valore: canzone scelta dall'amico n
    if ((in=fopen("../brani.txt","r"))==NULL){
        printf("Errore nell'apertura del file di lettura\n");
        return 1;
    }
    fscanf(in,"%d",&N);
    tabella=(tab*)malloc(N*sizeof(tab));
    ris=(int*)malloc(N*sizeof(int));
    for(i=0;i<N;i++){
        fscanf(in,"%d", &(tabella[i].nScelte));
        tabella[i].namelist=(istanza*)malloc((tabella[i].nScelte)*sizeof(istanza));
        for(j=0;j<tabella[i].nScelte;j++){
            fscanf(in, "%s",tabella[i].namelist[j].nomestr);
            tabella[i].namelist[j].key=j;
        }
    }
    fclose(in);
    //stampa
    /*for(i=0;i<N;i++){
        printf("Amico: %d\n",i);
        for(j=0;j<5;j++){
            printf("%d  ",tabella[i].namelist[j].key);
            printf( "%s  \n ",tabella[i].namelist[j].nomestr);
        }
    }*/
    printf("Combinazioni possibili:\n");
    Princ_mol(0,tabella, ris, N);
    for(i=0;i<N;i++)
        free(tabella[i].namelist);
    free(ris);
    free(tabella);
    return 0;
}

void Princ_mol(int pos, tab * canzoni,int *ris,int N){
    int i;
    if(pos >= N){
        for(i=0 ;i<N ;i++)
            printf(" %s ",canzoni[i].namelist[(ris[i])].nomestr) ;
        printf("\n");
    }
    for(i=0;i<canzoni[pos].nScelte;i++){
        ris[pos ]=canzoni[pos].namelist[i].key;
        Princ_mol(pos+1,canzoni, ris, N);
    }
}
