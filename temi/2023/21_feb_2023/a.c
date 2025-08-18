
#include "a.h"
#include <stdlib.h>
#include <stdio.h>

static int ** malloc2d(int R, int C, int val);
static int min(int a, int b);

inc leggifile(FILE *in){//
    inc G;
    int i, j;
    fscanf(in, " %d", &(G->T));
    G->tv=malloc(G->T*sizeof(int));
    for(i=0; i<G->T; i++){fscanf(in, " %d", &(G->tv[i]));}
    fscanf(in, "%d", &(G->P));
    G->pv=malloc(G->P*sizeof(int));//prima con la sintassi di un fscanf
    G->madj=malloc2d( G->P, G->P, -1);
    for(i=0; i<G->P; i++){fscanf(in, " %d", &(G->pv[i]) );}
    for(i=0; i<G->P; i++){
        for(j=0; j<G->P; j++) //messo ) al posto del ;
            fscanf(in, " %d" , &(G->madj[i][j]));
    }
    return G;
}

static int **malloc2d(int R, int C, int val){
    //prima static in malloc2d
    int **mat;
    int i,j;
    mat=malloc(R*sizeof(int*));
    for(i=0; i<R; i++){
        mat[i]=malloc(C*sizeof(int)); //prima *mat
    }
    for(i=0; i<R; i++)
        for(j=0; j<C; j++)
            mat[i][j]=val;
    return mat;
}

static int min(int a, int b){
    if(a<b)
        return a;
    else
        return b;
}

sol getproposta(FILE *in ){
    sol ris; int i, j;
    //prima sol=malloc....
    ris=malloc(sizeof(struct sol_s));
    fscanf(in, " %d %d ", &(ris->T), &(ris->N));
    ris->assign=malloc(ris->T*sizeof(assigns));
    for(i=0; i<ris->T; i++){
        fscanf(in , " %d", &(ris->assign[i].n));
        ris->assign[i].pvs=malloc(ris->assign[i].n*sizeof(int)); //ris->assign[i]->pvs
        ris->assign[i].resa=0;
        for(j=0; j<ris->assign[i].n; j++){ //assign[i].h
            fscanf(in, " %d" , &(ris->assign[i].pvs[j]));} /*sostituito indice da i a j*/
    }
    return ris;
}

int check(int **sin, inc G, sol ris){ //prima int G
    int *flag=calloc(ris->N, sizeof(int));
    int sum=0;
    int i,j;
    if(ris->T != G->T) return 0;
    if(ris->N != G->P) return 0;
    for(i=0; i< ris->T; i++){
        for(j=0; j<ris->assign[i].n; j++){
            if(flag[ris->assign[i].pvs[j]]==1){ return 0;} //prima flag[ris->assign[i].pvs[j]
            ris->assign[i].resa +=G->pv[ris->assign[i].pvs[j]];
            flag[ris->assign[i].pvs[j]]=1;
            if(j>0)
                ris->assign[i].resa+=sin[ris->assign[i].pvs[j-1]][ris->assign[i].pvs[j]];
            } //aggiunta graffa

            if((float)ris->assign[i].resa>= (float)75* (float)(G->tv[i])/(float)100)
            printf("resa assignment %d è di %d\n", i, min(ris->assign[i].resa, G->tv[i])); //aggiunto il minimo
            else { ris->assign[i].resa=0; printf("resa vale zero \n");}
            sum+=min(ris->assign[i].resa, G->tv[i]); //aggiunto il minimo
        }
        free(flag); //aggiunta deallocazione di flag
        return sum;
    }


int calcolaresa(int **sin, inc G, int *sol){
    //typo calcolareas
    int *resa, i,j, k=0, s, totresa=0 ;
    int *vectsin; //
    vectsin=calloc(G->P, sizeof(int));
    resa=calloc(G->T, sizeof(int));
    for(i=0; i<G->P; i++){
        resa[sol[i]]+=G->pv[i];
        if(sol[i]==0){
            vectsin[k]=i; k++;
        }
    }
    for(s=1; s<k; s++)
        resa[0]+=sin[vectsin[s-1]][vectsin[s]]; //sostituito k con s dentro le quadre
    for(i=1; i<G->T; i++){
        k=0;
        for(j=0; j<G->P; j++){
            if(sol[j]==i)
            {vectsin[k]=j; k++;} /*indice sostituito da i a k*/
        }
        for(s=1; s<k; s++) /*come nella parte sopra*/
            resa[i]+=sin[vectsin[s-1]][vectsin[s]];
    }
    for(i=0; i<G->T; i++){
        if((float)resa[i]>=(float) 75*G->tv[i]/(float)100) //scambiato da G->pv a G->tv
            totresa+=min(resa[i], G->tv[i]); //prima sommava direttamente la resa
    }
    return totresa;
}

void copyvect(int *dest, int *source, int n){
    int i;
    for(i=0; i<n; i++){
        dest[i]=source[i];
    }
}

void solve(inc G){
    int i, best=0;
    int *rr, *tmpr;
    rr=malloc(G->P*sizeof(int));
    tmpr=malloc(G->P*sizeof(int));
    /*sol ris=malloc(sizeof(struct sol_s));
    ris->assign=malloc(G->T*sizeof(assigns));
    for(i=0; i<G->T; i++){
        //non scritto .pvs
        ris->assign[i].pvs=malloc(G->P*sizeof(int)); //aggiunto .pvs dopo ris->assign[i]
    }
    */
    solve_r(0,G->T, rr, tmpr, &best, 0, G->P, G );
    //aggiunta stampa e deallocazione dei vettori rr e tmpr
    printf("Soluzione ottima di valore %d\n", best);
    for(i=0; i<G->P; i++)
        printf("lavoratore %d in mansione numero %d \n", i, rr[i]);
    free(tmpr);
    free(rr);
}

void solve_r(int pos, int n, int* rr, int *tmpr, int *best, int curmax, int k, inc G ){
    int i;
    if(pos>=k){
        curmax=calcolaresa(G->madj, G, tmpr);
        if(curmax> *best){
            *best=curmax;
            copyvect(rr, tmpr, k);
        }
        return;
    }
    for(i=0; i<n; i++){
        tmpr[pos]=i;
        solve_r(pos+1, n, rr, tmpr, best, curmax, k ,G); //typo da currmax a curmax
    }
}

void freesol(sol ris){
    int i;
    for(i=0; i<ris->T; i++){
        free(ris->assign[i].pvs);
    }
    free(ris->assign);
    free(ris);
}

void freeinc(inc G){
    int i;
    free(G->tv);
    free(G->pv);
    for(i=0; i<G->P; i++)
        free(G->madj[i]);
    free(G->madj);
}

void debugprint(int **sin, inc G){
    int i, j;
    printf("numero di Task %d, numero di persone P %d\n", G->T, G->P);
    printf("Vettore degli incarichi:\n");
    for(i=0; i<G->T; i++){
        printf(" %d ", G->tv[i]);
    }
    printf("\nVettore delle esperienze:\n");
    for(i=0; i<G->P; i++){
        printf(" %d ", G->pv[i]);
    }
    printf("\nMatrice delle sinergie: \n");
    for(i=0; i<G->P; i++){
        for (j=0; j<G->P; j++)
            printf(" %d", sin[i][j]);
        printf("\n");
    }
}

