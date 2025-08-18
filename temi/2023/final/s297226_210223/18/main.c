#include <stdio.h>
#include "a.h"

int main(){
    FILE *inp, *pro;
    inc G;
    sol ris;
    int f;
    inp=fopen("../input.txt", "r");
    pro=fopen("../proposta.txt", "r");
    G=leggifile(inp);
    debugprint(G->madj, G);
    ris=getproposta(pro);
    f=check(G->madj, G, ris);
    if(f ) printf("Soluzione accettabile, totale: %d\n", f);
    else printf("Non accettabile\n");
    solve(G);
    freesol(ris);
    freeinc(G);
    return 0;
}
