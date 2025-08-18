#include <stdio.h>
#include<stdlib.h>

typedef enum{
    zaf, rub, top, sme
}n_pietre;

void free4d(int ****pietre, int ripet[]);
void malloc5d(int *****pietre, int ripet[]);
int wrap_mem(int ****pietre[], int ripet[]);
int FS(int *****pietre, int ripet[]);
int FT(int *****pietre, int ripet[]);
int FR(int *****pietre, int ripet[]);
int FZ(int *****pietre, int ripet[]);
int max( int a, int b);

int main() {
    FILE *in;
    int casetest, i, j,k, ripet[4], max, nmax;
    int ****pietre[4];
    //4 caselle per struttura più esterna (sequenze con le 4 pietre iniziali)
    setbuf(stdout, 0);
    //lista con al posto
    //0 zaffiro
    //1 rubino
    //2 topazio
    //3 smeraldo
    if ((in = fopen("../easy_test_set.txt", "r")) == NULL) {
        printf("Errore nell'apertura del file di lettura\n");
    }
    fscanf(in, " %d", &casetest);
    for (i = 0; i < casetest; i++) {
        max = 0;
        for (j = 0; j < 4; j++) {
            fscanf(in, " %d", &ripet[j]);
            max += ripet[j];
        }
        printf("TEST #%d\n zaffiro = %d, rubino = %d, topazio = %d, smeraldo = %d, TOT=%d\n", i + 1, ripet[zaf],
               ripet[rub], ripet[top], ripet[sme], max);
        malloc5d(pietre, ripet);
        //pietre è già un vettore, così manda già l'indirizzo della prima "cella"
        nmax = wrap_mem(pietre, ripet);
        printf("Collana massima di lunghezza %d\n", nmax);
        for(k=0;k<4;k++)
            free4d(pietre[k], ripet);
    }
    fclose(in);
    return 0;
}

void free4d(int ****pietre, int ripet[]) {
    int i,j,k;
    for(i=0;i<ripet[zaf]+1; i++){
        for(j=0;j<ripet[rub]+1; j++){
            for(k=0;k<ripet[top]; k++){
                free(pietre[i][j][k]);
            }
            free(pietre[i][j]);
        }
        free(pietre[i]);
        //non ho bisogno di liberare pietre in quanto dentro allo stack verrà cancellato al termine di main
    }
}


int max( int a, int b){
    if(a>b)
        return a;
    return b;
}

int wrap_mem(int ****pietre[], int ripet[]) {
    //ogni pisetra ha uno strato in ogni tabella quadridimensionale?
    //oppure dovrei fare la malloc alla fine?
    int maxzaf, maxrub, maxtop, maxsme, realmax;
    maxzaf=FZ(pietre, ripet);
    maxrub=FR(pietre, ripet);
    maxtop=FT(pietre, ripet);
    maxsme=FS(pietre, ripet);
    realmax= max(max(maxzaf, maxrub), max(maxtop, maxsme));
    return realmax;
}

int FZ(int *****pietre, int ripet[]){
    //disposizioni ripetute
    //se il valore è già stato calcolato ritorna la soluzione, altrimenti
    //propagare il massimo fino alla funzione chiamante, come?
    int tmax1, tmax2, sol;
    if(pietre[zaf]  [ripet[zaf]]  [ripet[rub]]  [ripet[top]] [ripet[sme]] >0 ){
        return pietre[zaf]  [ripet[zaf]]  [ripet[rub]]  [ripet[top]] [ripet[sme]];
    }
        //sottrai una pietra e calcola il nuovo valore?
    else if(ripet[zaf]>0){ //se posso ancora aggiungere pietre
        ripet[zaf]--; //controllo soluzione aggiungendo un altra pietra
        tmax1=FZ(pietre, ripet);
        tmax2=FR(pietre, ripet);
        sol=max(tmax1, tmax2)+1;
        ripet[zaf]++;
        return sol;
    }
    return 0;
}

int FR(int *****pietre, int ripet[]){
    //disposizioni ripetute
    //se il valore è già stato calcolato ritorna la soluzione, altrimenti
    //propagare il massimo fino alla funzione chiamante, come?
    int tmax1, tmax2, sol;
    if(pietre[rub]  [ripet[zaf]]  [ripet[rub]]  [ripet[top]] [ripet[sme]] >0 ){
        return pietre[rub]  [ripet[zaf]]  [ripet[rub]]  [ripet[top]] [ripet[sme]];
    }
        //sottrai una pietra e calcola il nuovo valore?
    else if(ripet[rub]>0){ //se posso ancora aggiungere pietre
        ripet[rub]--; //controllo soluzione aggiungendo un altra pietra
        tmax1=FT(pietre, ripet);
        tmax2=FS(pietre, ripet);
        sol=max(tmax1, tmax2)+1;
        ripet[rub]++;
        return sol;
    }
    return 0;
}

int FT(int *****pietre, int ripet[]){
    //disposizioni ripetute
    //se il valore è già stato calcolato ritorna la soluzione, altrimenti
    //propagare il massimo fino alla funzione chiamante, come?
    int tmax1, tmax2, sol;
    if(pietre[top]  [ripet[zaf]]  [ripet[rub]]  [ripet[top]] [ripet[sme]] >0 ){
        return pietre[top]  [ripet[zaf]]  [ripet[rub]]  [ripet[top]] [ripet[sme]];
    }
        //sottrai una pietra e calcola il nuovo valore?
    else if(ripet[top]>0){ //se posso ancora aggiungere pietre
        ripet[top]--; //controllo soluzione aggiungendo un altra pietra
        tmax1=FZ(pietre, ripet);
        tmax2=FR(pietre, ripet);
        sol=max(tmax1, tmax2)+1;
        ripet[top]++;
        return sol;
    }
    return 0;//per NON ritrovarsi con la somma cumulativa
}

int FS(int *****pietre, int ripet[]){
    //disposizioni ripetute
    //se il valore è già stato calcolato ritorna la soluzione, altrimenti
    //propagare il massimo fino alla funzione chiamante, come?
    int tmax1, tmax2, sol;
    if(pietre[sme]  [ripet[zaf]]  [ripet[rub]]  [ripet[top]] [ripet[sme]] >0 ){
        return pietre[sme]  [ripet[zaf]]  [ripet[rub]]  [ripet[top]] [ripet[sme]];
    }
        //sottrai una pietra e calcola il nuovo valore?
    else if(ripet[sme]>0){ //se posso ancora aggiungere pietre
        ripet[sme]--; //controllo soluzione aggiungendo un altra pietra
        tmax1=FT(pietre, ripet);
        tmax2=FS(pietre, ripet);
        sol=max(tmax1, tmax2)+1;
        ripet[sme]++;
        return sol;
    }
    return 0;
}


void malloc5d(int *****pietre, int ripet[]){
    int i,nz,nr,nt;
    for(i=0;i<4;i++){
        if((pietre[i]=(int****)malloc((ripet[zaf]+1) * sizeof(int***)))==NULL){
            printf("Memoria esaurita\n");
        }
        //per evitare indici negativi 
        for(nz=0;nz<ripet[zaf]+1;nz++){
            pietre[i][nz]=(int***)malloc((ripet[rub]+1) * sizeof(int**));
            for(nr=0;nr<ripet[rub]+1;nr++){
                pietre[i][nz][nr]=(int**)malloc((ripet[top]+1) * sizeof(int*));
                        for(nt=0;nt<ripet[top]+1; nt++){
                            pietre[i][nz][nr][nt]=(int*)calloc(ripet[sme]+1, sizeof(int));
                        }
            }
        }
    }
}