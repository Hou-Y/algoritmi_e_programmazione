#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int t_in;
    int t_fin;
    int dur;
} att;

void attSel(int N, att *v);
void ordina(att *dati, int N);
int powerset(int pos, att *v, int *scelte, int fine, int partialsum, int save, int *vmax, int *max );

int main() {
    FILE *in;
    att *dati;
    int N, i;
    if ((in=fopen("../att1.txt","r"))==NULL){
        printf("Errore nell'apertura del file di lettura\n");
    }
    fscanf(in," %d", &N);
    dati=(att*)malloc(N*sizeof(att));
    for(i=0; i<N; i++){
        fscanf(in," %d %d", &(dati[i].t_in), &(dati[i].t_fin));
        dati[i].dur=dati[i].t_fin - dati[i].t_in;
    }
    ordina(dati, N);//oppure potrei usare una lista a farlo ordinato sin da subito
    attSel(N,dati);
    free(dati);
    return 0;
}

void ordina(att *dati, int N){//inserction
    int i,j;
    att altrotemp;
    for(i=1;i<N;i++){
        altrotemp=dati[i];
        j=i-1;
        while(  (j>=0 && altrotemp.t_in < dati[i].t_in)   ||   ( j>=0 && altrotemp.t_fin < dati[i].t_fin)  ){
            dati[j+1]=dati[j];
            j--;
        }
        dati[j+1]=altrotemp;
    }
}

void attSel(int N, att *v){//wrapper
    int scelte[N], i, max=0, num; //vettore parallelo ad att
    int *vmax=(int*)malloc(N*sizeof(int)); //viene distrutto uscita dalla funzione
    num = powerset(0, v, scelte, N, 0, 0, vmax, &max);
    if(num!=0)
        printf("Errore nella ricorsione\n");
    for(i=0;i<N; i++) {
        if (vmax[i] == 1)
            printf(" { %d %d } ", v[i].t_in, v[i].t_fin);
    }
    printf("\nDurata massima: %d\n\n", max);
    //con pruning a ogni passo?
    free(vmax);
}


int powerset(int pos, att *v, int *scelte, int fine, int partialsum, int save, int *vmax, int *max ){ //powerset
    int i;
    //salvo in puntatore att la la lista attualmente più lunga e alla fine passo quella
    if(pos >= fine ){ //quando non ha più combinazioni possibili
        if(partialsum>*max){
            *max=partialsum;
            for (i=0; i<fine; i++) {//qua voglio la stampa una singola volta, come faccio a capire che è la più lunga?
                //perchè alla prossima iterazione perdo il dato
                if (scelte[i] == 1)
                    vmax[i] = 1;
            }
        }
        return 0;
            //return 0;
    }
    if(pos==0 || (v[save].t_fin <= v[pos].t_in) ){//solo se sono disgiunti prova a prenderlo
        //fa il controllo relativo all'ultimo elemento preso per controllare compatibilità
        //basta controllare che quello precedente sia disgiunto con questo? NOPE, non sappiamo se è in ordine
        scelte[pos] = 1;
        save=pos;
        partialsum = powerset(pos+1, v, scelte, fine, partialsum+v[pos].dur, save, vmax, max);
    }
    scelte[pos] = 0;
    partialsum = powerset(pos+1, v, scelte, fine, partialsum, save, vmax, max);

    return partialsum;
}
/*ES1:
 * Non abbiamo vincoli
 * NON conviene verficare la non compatibilità alla fine (possiamo capirlo già dall'inizio)
 */