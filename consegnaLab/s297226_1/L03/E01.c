
#include<stdio.h>
#include<stdlib.h>

int majority( int *a, int N);
int mergemaj(int n1,int n2, int a[], int N);
int countmax(int n1, int n2, int a[], int N);
int main(){ //sembra funzioni, servono più test case
    setbuf(stdout, 0);
    int N=1,i, ris;
    int *p=(int*)malloc(N*sizeof(int));
    printf("Quanti elementi ha il vettore?\n");
    scanf("%d",&N);
    printf("Scrivi il vettore:\n");
    p=(int*)realloc(p,N*sizeof(int));
    for(i=0;i<N;i++){
        scanf("%d",&p[i]);
        //printf("%d    ", *(p+i)); //printa ogni valore del vettore
        //printf("%d      ", p[i]); //printa stessa cosa di sopra
    }
    ris=majority(p,N);
    if (ris!=(-1))
        printf("Elemento maggioritario: %d\n",ris);
    else
        printf("Non ha elemento maggioritario\n");
}

int majority( int *a, int N){ //puntatore
    int n1,n2, part;
    if(N<=1)
        return a[0]; //dereferenziazione
   else{
        part=(N)/2;
        n2=majority((a+part),N-(part)); //parte dietro
        n1=majority(a,part); //parte davanti
        }
    return mergemaj(n1,n2, a, N);
}

int mergemaj(int n1,int n2, int a[], int N){
    if (n1==n2)
        return n1;
   else if((n1==-1 && n2==-1) || (n1!=-1 && n2!=-1 && N%2==0)) //se due soluzioni diverse con lunghezza pari
        return -1;
   else if (n2==-1)
        return n1;
   else if(n1==-1)
        return n2;
   else if(n1!=-1 && n2!=-1) //due valori diversi con lunghezza dispari
       return countmax(n1,n2,a, N); //quando è soluzione di sottovettori di dimensione maggiore di 1 e dispari devo attivare una funzione conta
}

int countmax(int n1, int n2, int a[], int N){ //ritorna il valore con più istanze
    int cn1=0,cn2=0;
    for(int i=0;i<(N); i++){
        if(a[i]==n1)
            cn1++;
        if(a[i]==n2)
            cn2++;
    }
     if (cn1>cn2)
         return n1;
     return n2;
}