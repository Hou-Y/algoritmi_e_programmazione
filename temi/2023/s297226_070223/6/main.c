
//formattazione sistemata
#include <stdio.h>
#include <stdlib.h>
#include "ST.h"

void wrap(int **M, int N, int E); //aggiunto numero di archi
int disp(int pos, int **M, int *tm, int mark[], int start, int k, int N);
ST getgrafo(int *N, int *E, int ***grafo);
void intMATprint(int **G, int r, int c);

int main() {
    setbuf(stdout,0);
    int N,E;
    int **M;
    ST sym;
    sym=getgrafo(&N,&E, &M);
    intMATprint(M ,N,N );
    wrap(M, N, E);
    return 0;
}

//aggiunto input
ST getgrafo(int *N, int *E, int ***grafo){
    FILE *in;
    ST table;
    int i, tnodo, tnodo2;
    char t[30], t1[30];
    if ((in=fopen("../matrix.txt","r"))==NULL){
        printf("Errore nell'apertura del file di lettura\n");
    }
    fscanf(in," %d %d",N,E);
    table=STinit(*N);
    *grafo=(int**) malloc(*N * sizeof(int*));
    for(i=0;i<*N;i++){
        (*grafo)[i]=( int*) calloc(*N , sizeof(int));
        fscanf(in, "%s", t);
        STinsert( t, table, i);
        if ((*grafo)[i] == NULL) {
            printf("Memoria piena\n");
            exit(42);
        }
    }
    for(i=0;i<*E;i++){
        fscanf(in," %s %s",t, t1);
        tnodo = STsearch(table, t);
        tnodo2 = STsearch(table, t1);
        (*grafo)[tnodo][tnodo2]=1;
        (*grafo)[tnodo2][tnodo]=1;
    }
    fclose(in);
    return table;
}

int findpath(int **M, int group int in, int N){
    //tolto il passaggio del vettore di soluzioni e di start
    //aggiunto il passaggio di N
    int i;
    for(i=0; i<N; i++){//sostituito v[i] con il suo indice i
        if(M[in][i]>0){ //tolta una parentesi dopo [v[i]]
            if(M[i][group]>0) //tolto ; di troppo
                return 1;
        }
    }
    return 0;
}
int control(int **M, int group, int *tsol, int N, int start, int pos, int *mark){
    //aggiunto il * per il corretto passaggio di tsol
    //aggiunto passaggio di mark
    int i; //tolto variabile j inutilizzata
    for(i=0; i<N; i++){ //sostituito , davanti a i++ con ;
        //sostituito condizione di fine ciclo da start a i e l'indice di tsol al valore dentro tsol nell'if
        //aggiunta condizione di appartenenza del gruppo
        if( M[i][group]==0 && mark[i]!=-1 && tsol[i]==pos){
            if(!findpath(M, group, tsol, start, tsol[i], N, pos)) //aggiunto passaggio di N e di pos
                return 0;
        } //tolta una parentesi di troppo
    }
    return 1;
}

int disp(int pos, int **M, int *tm, int mark[], int start, int k, int N) {
    //aggiunto passaggio di N , tolto N dentro mark[]
    int i;
    if (pos >= k) {
        for (i = 0; i < N; i++) {
            if (mark[i] == -1)//se non ho preso ogni città
                return 0;
        }
        return 1;
    }//aggiunte graffe
    for (i = 0; i < N; i++) { //aggiunto passaggio di pos dentro la funzione control
        if (control(M, i, tm, N, start, pos, mark) && mark[i] == -1) {
            tm[i] = pos;
            mark[i] = 1;
            if (disp(pos, M, tm, mark, start + 1, k, N))
                return 1;//Tolta parentesi inutile
        } else if (mark[i] == -1) {
            mark[i] = 1;
            tm[i]=pos+1; //aggiunta selezione di tm[i]
            //sostituito ; dopo pos+1 con ,
            if (disp(pos + 1, M,tm, mark, 0, k, N))  //tolto mark[i]=1, scritto precedentemente nella posizione sbagliata
                //e non più rimossa dopo aver modificato
                return 1;
        }
        mark[i] = -1;
    }
}
void wrap(int **M, int N, int E){
    //tolto sol variabile inutilizzata
    int i, flag=0;
    int mark[N];
    int *tm=malloc(N*sizeof(int));
    for(i=0; i<N; i++) { mark[i]=-1;}
    for(i=0; i<N && !flag; i++)
    {
        if (disp(0, M, tm, mark, 0, i, N)) {
            flag = 1;
        }

    }
    if(E==0 ) printf("%d\n", N); //aggiunto caso particolare
    else printf("%d\n", i-1);
    //debug
    for(i=0; i<N; i++)
        printf("indice %d in gruppo %d\n", i, tm[i]);
}

void intMATprint(int **G, int r, int c){
    int i, j;
    for(i=0; i<r; i++){
        for(j=0; j<c; j++){
            printf(" %d", G[i][j]);
        }
        printf("\n");
    }
}
