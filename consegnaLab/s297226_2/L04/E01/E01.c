#include<stdio.h>
#include<stdlib.h>

    //1 se il nodo e il nodo in posizione (indice di Connessioni) sono connessi
    //0 se il nodo e il nodo in posizione (indice di Connessioni) sono connessi

void getgrafo(int *N, int *E, int ***grafo);
int vertexcover(int **grafo, int pos, int *sol, int n, int co);
int sight(int **grafo, int *sol, int n);

int main(int argv, char *argc[]){
    setbuf(stdout, 0);
    int N, E, i;
    int **grafo, *ris;//lista di nodi
    getgrafo(&N,&E,&grafo);
    //stampa
    /*for(int i=0;i<N;i++){
        for (int j=0;j<E;j++){
            printf(" %d ", grafo[i][j]);
        }
        printf("\n");
    }*/
    ris=(int*)malloc(N*sizeof(int));
    printf("Vertex cover:\n");
    vertexcover(grafo,0,ris,N,0);
    free(ris);
    for(i=0;i<N;i++){
        free(grafo[i]);
    }
    free(grafo);
}

void getgrafo(int *N, int *E, int ***grafo){
    FILE *in;
    int i, tnodo, tnodo2;
    if ((in=fopen("../grafo.txt","r"))==NULL){
        printf("Errore nell'apertura del file di lettura\n");
    }
    fscanf(in," %d %d",N,E);
    *grafo=(int**) malloc(*N * sizeof(int*)); //*N dereferenziazione
    //indice di grafo è il valore del nodo
    //supponendo i nodi siano numerati partendo da 0 a N-1 ordinatamente (senza saltare valori)
    for(i=0;i<*N;i++){
        (*grafo)[i]=( int*) calloc(*N , sizeof(int));
        if ((*grafo)[i] == NULL) {
            printf("Memoria piena\n");
            exit(42);
        }
        //parentesi tonde
        //voglio un vettore azzerato o almeno avere la certezza di non avere degli 1
    }
    for(i=0;i<*E;i++){
        fscanf(in," %d %d",&tnodo, &tnodo2); //Data argument not used by format string
        (*grafo)[tnodo][tnodo2]=1;
        (*grafo)[tnodo2][tnodo]=1; //la connessione è una proprietà riflessiva, matrice simmetrica
        //PRECEDENZA di operatori
        //tnodo è il  nodo corrente connesso a (tnodo2)
        //anche se ci fossero più archi dai due stessi nodi, nulla cambierebbe dal punto di vista del vertex cover
    }
    fclose(in);
}

int vertexcover(int **grafo, int pos, int *sol, int n, int count){ //powerset
    int i;
    //per ogni riga
    //se vedo tutto (indici colonna con 1 tranne quello con indice riga==indice colonna) comprende tutti i nodi sight()
    //aggiungi anche se la soluzione corrente va bene
    //arrivato alla fine backtrack e prendi un altro valore
    if(pos >= n ){ //senza pruning
        if(sight(grafo, sol, n)){
            printf("{ ");
            for (i=0; i<n; i++){
                if (sol[i]!=0)
                    printf("%d ", i);
            }
            printf("} \n");
        }
        return count+1;
    }
    sol[pos] = 0;
    count = vertexcover(grafo,pos+1, sol, n, count);
    sol[pos] = 1;
    count = vertexcover(grafo,pos+1, sol, n, count);
    return count;
}

int sight(int **grafo, int *sol, int n){
    int i,j, *vedo;
    vedo=(int*)calloc(n,sizeof(int));
    for(i=0;i<n;i++){
        if(sol[i]==1){
            vedo[i]=1;
            for(j=0;j<n;j++)
                vedo[j]+=grafo[i][j];
        }
    }
    for(i=0;i<n;i++){
        if(vedo[i]==0){
            free(vedo);
            return 0;
        }
    }
    free(vedo);
    return 1;
}