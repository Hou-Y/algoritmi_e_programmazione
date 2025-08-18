#include<stdio.h>
#include<stdlib.h>
#define filea "../mat.txt"
#define fileb "../stampa.txt"

void malloc2dP(int***mat, int nr, int nc, FILE *in);
void separa(int **mat, int nr, int nc,int **white, int **black );
int main(){
    FILE *in, *out;
    int nr,nc,i;
    int **mat, *bianco, *nero;
    if ((in=fopen(filea,"r"))==NULL){
        printf("Errore nell'apertura del file di lettura\n");
        return 1;
    }
    if ((out=fopen(fileb,"w"))==NULL){
        printf("Errore nell'apertura del file di scrittura\n");
        return 2;
    }
    fscanf(in,"%d%d",&nr,&nc);
    malloc2dP(&mat,nr,nc, in);
    // stampa
    /*for(int i=0;i<nr;i++){
        for(int j=0;j<nc;j++)
            printf("%d ",mat[i][j]);
        printf("\n");
    }*/
    separa(mat, nr, nc,&bianco, &nero );
    fprintf(out,"A sinistra il vettore dei neri, a destra il vettore dei bianchi (matrice ha casella che parte dal nero)\n\n");
    for(i=0;i<nr*nc/2;i++){
        fprintf(out,"%d       %d\n",nero[i], bianco[i]);
    }
    if(nc%2!=0 || nr%2!=0)
        fprintf(out,"%d\n", nero[i]); //uscito dal for la i è incrementata
    fclose(in);
    fclose(out);
}

void malloc2dP(int***mat, int nr, int nc, FILE *in){
    int **rig, i,j;
    rig=(int**)malloc(nr*sizeof(int*));//nel heap
    for(i=0;i<nr;i++){
        rig[i]=(int *)malloc(nc*sizeof(int));
        for(j=0;j<nc;j++)
            fscanf(in,"%d", &rig[i][j]);
    }
    *mat=rig;//viene dato l'indirizzo per accedere a mat ma per modificare mat hai bisogno della dereferenziazione
}

void separa(int **mat, int nr, int nc,int **white, int **black ){
    //la lunghezza finale è calcolabile a priori == (nr*nc)/2
    *white=(int*)malloc(nr*nc/2*sizeof(int));
    //scelgo black come casella (0,0)
    if(nr%2!=0 || nc%2!=0) // se uno tra nr o nc è dispari black ha una casella aggiuntiva
        *black=(int*)malloc((nr*nc/2)+1*sizeof(int));
    else
        *black=(int*)malloc(nr*nc/2*sizeof(int));
    int i,j, k=0;
    for(i=0;i<nr;i++){
        for (j=0;j<nc;j++){
            if((i+j)%2==0)
                (*black)[k]=mat[i][j];//precedenza operatori
            else if((i+j)%2!=0){
                (*white)[k]=mat[i][j];
                k++;//
            }
        }
    }
}

