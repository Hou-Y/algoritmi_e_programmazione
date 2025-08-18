#include <stdio.h>
#include <stdlib.h>

void f(int **M, int r, int c, float ***NEW);
void malloc2dP(int***mat, int nr, int nc, FILE *in);
void MATprint(float **G, int r, int c);
void intMATprint(int **G, int r, int c);

int main() {
    int **M;
    int r,c;
    float **prova;
    FILE *in;
    in=fopen("../matrix.txt", "r");
    fscanf(in, "%d %d", &r, &c);
    malloc2dP(&M, r, c, in);
    //debug
    //intMATprint(M, r,c );
    //
    f(M, r, c, &prova);
    //debug
    //MATprint(prova, r, c);
    //
    return 0;
}

void f(int **M, int r, int c, float ***NEW) { //modificato tipo di puntatore alla nuova matrice
    float **NM;
    int i,j,k, n,s, startn, finn, starts, fins;
    int su, giu;
    float t;
    NM=malloc(r*sizeof(float)); //invertito ordine
    for(i=0; i<r; i++){
        NM[i]=malloc(c*sizeof(float));
        //modificato da *NM che mallocava solo la prima riga a NM[i]
        //per mallocare ogni rica
    }
    for(i=0; i<r; i++){ //tolte variabili dx sx non usate
        su=1; giu=1;
        //valore di inizializzazione di k reso una costante
        for(j=0; j<c; j++){//spostata inizializzazione di k dentro al ciclo interno
            t=0;k=9; startn=i-1; starts=j-1; finn=i+1; fins=j+1; //aggiunta inizializzazione di t a zero
            if(i==0){
                k=k-3; //sostituito quantità sottratto da k a costanti
                su=0;
                startn=0;
            }
            if(i==r-1){//scambia tra r e c tra questo e il prossimo if
                k=k-3;
                giu=0;
                finn=i;}
            if(j==c-1){
                if(giu==0 && su==0) k=k-1;
                else if(giu==0 || su ==0) k=k-2;
                else k=k-3;
                fins=j;
            }
            if(j==0){
                if(giu==0 && su==0) k=k-1;
                else if(giu==0 || su ==0) k=k-2;
                else k=k-3;
                starts=0;}
            for(n=startn; n<=finn; n++) //condizione di terminazione da < a <=
                for( s=starts; s<=fins; s++)
                        t=t+M[n][s];
            //aggiornato il nome tmp a t
            NM[i][j]=(float)t/(float)k;
        }
    }
    *NEW=NM; //invertito ordine di operazione
}

void malloc2dP(int***mat, int nr, int nc, FILE *in){
    int **rig, i,j;
    rig=(int**)malloc(nr*sizeof(int*));
    for(i=0;i<nr;i++){
        rig[i]=(int *)malloc(nc*sizeof(int));
        for(j=0;j<nc;j++)
            fscanf(in,"%d", &rig[i][j]);
    }
    *mat=rig;
}

void MATprint(float **G, int r, int c){
    int i, j;
    for(i=0; i<r; i++){
        for(j=0; j<c; j++){
            printf(" %.2f", G[i][j]);
        }
        printf("\n");
    }
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
