
#include <stdio.h>
int gcd(int a, int b);
void swap (int *pa, int *pb);

int main(){
    int a,b, ris;
    printf("scrivi due numeri, verra' calcolato il loro massimo comun divisore\n");
    scanf("%d%d",&a,&b);
    ris=gcd(a,b);
    printf("MCD: %d",ris);
}

void swap (int *pa, int *pb) {
    int tmp = *pa;
    *pa=*pb;
    *pb=tmp;
}

int gcd(int a, int b){
    int aodd=0, bodd=0;
    if(b>a)//scambio
        swap(&a,&b);
    if(a%2!=0)
        aodd=1;
    if(b%2!=0)
        bodd=1;
    if(b==1 && aodd)//condizioni di terminazione
        return 1;
    if(b==0)
        return a;
    //else if( !aodd && bodd) //condizione non coperta
    else if( !aodd && !bodd){
        return 2*gcd(a/2, b/2);
    }
    else if(aodd && bodd){
        return gcd((a-b)/2,b);
    }
    else if( aodd && !bodd){
        return gcd(a, b/2);
    }
    else if( !aodd && bodd){
        return gcd(a/2, b);
    }
}