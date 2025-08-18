#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct{//locuzione logica per
    char color;
    int val;
}tubo;

typedef struct{
    int indice;
    int rotat;
}tab;

void stampaBoard(int col, int rig, tab * maxmark);
void leggiTes(tubo **tes, int *T);
void leggiBoard(int *col, tab **board, int *tempr, int *mark);
int disp_sempl(int pos, int r, int c, tab *board, tubo ** tes, int *mark, int T, int maxsum, tab *maxmark);

int main() {
    int T,i, col, rig, max=0;
    tubo *tes[2]; //indice 0 per dritto, 1 per ruotato come nella board
    tab *board, *maxmark;//posizione 0 per dritto, 1 per orizzontale
    int *mark;
    //uso il booleano per capire quale indice del vettore usare (0 1)
    leggiTes(tes,&T);
    mark =malloc(T * sizeof(int)); //0 non preso, 1 preso
    for(i=0;i<T;i++){ //vettore per capire se il tassello è dentro la board
        mark[i]=-2;
    }
    leggiBoard(&col, &board, &rig, mark);
    maxmark=malloc(col*rig * sizeof(int)); //configurazione della board con valore massimo
    //stesse dimensioni della board
    /*for(i=0;i<T; i++){
        printf(" %d %d\n", tes[0][i].val, tes[1][i].val);
    }*/
    max=disp_sempl(0, rig, col, board, tes, mark, T, max, maxmark);
    printf("Valore massimo: %d\n", max);
    stampaBoard( col, rig, maxmark);
    //stampa nello stesso formato del board di input
    free(tes[1]); free(tes[0]);
    free(board);
    free(mark);
    free(maxmark); //sigtrap
    //tes è nello stack ma *tes è nel heap
    //*tes[2] crea un vettore lungo 2 (y) di puntatori, la larghezza (x) è ignota
    //mette i dati in due vettori paralleli, in 0 verticale, in 1 orizzontale
}

void stampaBoard( int col, int rig, tab *maxmark){
    int i;
    for(i=0; i< col*rig; i++){
        printf("%d/%d  ", maxmark[i].indice, maxmark[i].rotat);
        if(i%col==col-1)
            printf("\n");
    }
}

int how_many_points(tab *board, int r, int c, tubo **tes){
    int points=0, i, j, flag, tmpcount=0, k;
    char flagcolor;
    //orizzontale (rotazione originale)
    for(i=0; i<r; i++){//per il numero di righe (sto guardando il valore delle orizzontali)
        flag=1;
        flagcolor=tes[board[i*c].rotat][board[i*c].indice].color;
        for(j=0; j<c && flag; j++){ //per ogni elemento di una riga
            k=i*c+j; //indice del vettore unidimensionale
            tmpcount+=tes[board[k].rotat][board[k].indice].val;
            if(tes[board[k].rotat][board[k].indice].color!=flagcolor)
                flag=0;
        }
        if(flag)
            points+=tmpcount;
    }
    //verticale (girato)
    for(j=0; j<c; j++){
        flag=1; tmpcount=0;
        flagcolor=tes[(board[j].rotat+1)%2][board[j].indice].color;
        //primo elemento di ogni colonna
        for(i=j; i<r*c && flag; i+=c){
            tmpcount+=tes[(board[i].rotat+1)%2][board[i].indice].val;
            if(tes[(board[i].rotat+1)%2][board[i].indice].color!=flagcolor)
                flag=0;
        }
        if(flag)
            points+=tmpcount;
    }
    return points;
}

int disp_sempl(int pos, int r, int c, tab *board, tubo ** tes, int *mark, int T, int maxsum, tab *maxmark){
    int i, k, partialsum;
    if(pos>=r*c){ //riempito l'intero board
        //fai il calcolo del punteggio alla fine
        partialsum=how_many_points(board, r, c, tes);
        if(partialsum> maxsum){
            maxsum=partialsum;
            for (i=0; i<r*c; i++) {
                //se il tessello è stato marcato (dentro la board)
                maxmark[i].indice = board[i].indice;
                maxmark[i].rotat= board[i].rotat;
            }
        }
        return maxsum;
    }
    if(board[pos].indice != -1){
        return disp_sempl(pos+1, r, c, board, tes, mark, T, maxsum, maxmark );
    }
    for(k=0; k< T; k++){
        if(mark[k]==-2){
            board[pos].indice=k;
            board[pos].rotat=mark[k]=0; //potrei usare la rotazione della board come mark?
            maxsum=disp_sempl(pos+1, r, c, board, tes, mark, T, maxsum, maxmark );
            board[pos].rotat=mark[k]=1;
            maxsum=disp_sempl(pos+1, r, c, board, tes, mark, T, maxsum, maxmark );
            //smarco
            mark[k]=-2;
            board[pos].indice=board[pos].rotat=-1;
        }
    }
    return maxsum;
}

void leggiTes(tubo **tes, int *T){
    FILE *in;
    int i;
    if ((in = fopen("../tiles.txt", "r")) == NULL) {
        printf("Errore nell'apertura del file di lettura\n");
    }
    fscanf(in, " %d", T);
    *tes=(tubo*)malloc((*T) *sizeof(tubo)); //così inizializzo solo il primo vettore
    tes[1]=malloc( *T  * sizeof(tubo));//ora anche il secondo vettore punta
    for(i=0;i<*T;i++){
        fscanf(in, " %c %d %c %d", &(tes[0][i].color), &(tes[0][i].val), &(tes[1][i].color), &(tes[1][i].val) );
        //ruotato in 0 è la verticale che uso all'indice 0
        //ruotato in 1 uso indice 1 (orizzontale)
    }
    fclose(in);
}

void leggiBoard(int *col, tab ** board, int *tempr, int *mark) {
    FILE *in;
    tab *tbo;
    int i, k;
    if ((in = fopen("../board.txt", "r")) == NULL) {
        printf("Errore nell'apertura del file di lettura\n");
    }
    fscanf(in, " %d %d", tempr, col);
    //calloc array di caratteri riempie di /0
    k=*tempr * (*col);
    tbo=malloc(k  * sizeof(tab));
    for(i=0;i< k;i++){
        fscanf(in, "%d/%d ", &(tbo[i].indice), &(tbo[i].rotat));
        //cerco il tassello corrispettivo nel tiles e lo elimino dalle scelte possibili
        if(tbo[i].indice != -1){ //se è già nel board lo marco
            mark[tbo[i].indice]=tbo[i].rotat;
            //dentro il vettore mark ci sta 1 oppure 0 a seconda della rotazione del tessello nella board
        }
    }
    *board=tbo;
}
