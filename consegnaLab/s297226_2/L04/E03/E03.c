/*
Zaf  -> Zaf/Rub Rest
Topaz -> Zaf/Rub Change
Sme-> Sme/Topaz Rest
Rub -> Sme/Topaz Change

visualizzi la composizione di una collana a lunghezza massima che rispetti le regole di cui sopra
 * */

//mi riduco ad avere lo stesso numero in tutte e quattro i tipi di gemme e applico a ripetizione il paradigma
//sottraggo da tutte le pietre il valore con numero minore, e applico le disposizioni alle pietre rimanenti
//ci sarà un tipo di pietra con valore iniziale 0 dopo la sottrazione

#include <stdio.h>
#include<stdlib.h>

typedef enum{
    zaf, rub, top, sme
}n_pietre;

int multiplo_comune(int pietre[], int max);
int comb_rip(int posCurr, int *mark, int *sol, int numero_pietre, int lunghezza_k, int save_pietra);
int bueno(int pietra_prec, int pietraCurr);

/* 1Z 1R 1T 1S  t-> Z->R->S->T (ordine di scelta, posso farlo partire da qualunque tipo di pietra e usarle tutte)
 * unico limite sta nella pietra di arrivo e partenza
 *            z->  R->S->T->Z (alternando rest/change si possono usare tutte le pietre in numero uguale)
 *            r->  S->T->Z->R
 *            s->  T->Z->R->S
 * */

int main(){
    FILE *in;
    int casetest, i, j, pietre[4], max, nmax;
    setbuf(stdout, 0);
    //lista con al posto
    //0 zaffiro
    //1 rubino
    //2 topazio
    //3 smeraldo
    if ((in=fopen("../easy_test_set.txt","r"))==NULL){
        printf("Errore nell'apertura del file di lettura\n");
    }
    fscanf(in," %d",&casetest);
    for(i=0;i<casetest;i++){
        max=0;
        for(j=0;j<4; j++){
            fscanf(in," %d", &pietre[j]);
            max+=pietre[j];
        }
        printf("TEST #%d\n zaffiro = %d, rubino = %d, topazio = %d, smeraldo = %d, TOT=%d\n", i+1, pietre[zaf], pietre[rub], pietre[top], pietre[sme], max);
        nmax=multiplo_comune(pietre,max);
        printf("\nCollana massima di lunghezza %d\n", nmax);
        //volendo posso riutilizzare max
        //chiede solo la lunghezza massima, non gli serve come è stata ottenuta
        //potrebbe essere la prima parte di programmazione dinamica
    }
    fclose(in);
    return 0;
}

int minimo(int a, int b){
    if(a<=b)
        return a;
    else
        return b;
}

int multiplo_comune(int pietre[], int max){//wrapper
    //partire dalla fine diminuendo di uno ogni volta e alla prima soluzione valida che trovi lo stampi, è sicuro di essere
    //quello più lungo
    //prima diminuisci del valore più piccolo tra le 4 pietre e lo salvi in com e trovi la disposizione ripetuta più lunga
    //se ci sono 4 pietre, uno per tipo riesco a usarle tutte, poi la sequenza specifica ci arriviamo dopo partendo
    //dall'ultima pietra restituita dalle disposizioni e lo iteriamo per il numero com salvato precedentemente
    int i, j,k, currmax, com=minimo(minimo(pietre[zaf],pietre[rub]), minimo(pietre[top], pietre[sme]));
    int *take;
    for(i=0;i<4;i++)
        pietre[i]-=com;
    currmax=com*4;
    take=(int*)calloc((max-currmax), sizeof(int));
    //partendo dal valore massimo possibile cerco se si trovano collane con quella lunghezza e a ogni passo decremento
    i=max-currmax;
    while (i>0 && !comb_rip(0, pietre, take, 4, i, -2) ){
        i--;
    }
    //non usare 0 in save_pietra in quanto è il simbolo dello zaffiro
    currmax=currmax+i;
    for(j=0;j<i;j++){
        if(take[j]==zaf)
            printf(" Z->");
        else if (take[j]== rub)
            printf(" R->");
        else if( take[j]==top)
            printf(" T->");
        else if( take[j]==sme)
            printf(" S->");
    }
    //diminuisco j PRIMA di utilizzarlo, il valore modificato di j viene carryato negli else if dopo
    if(take[(--j)]==zaf){
        for(k=0;k<com; k++)
            printf(" R-> S-> T-> Z ");

    }
    else if(take[(j)]==rub){
        for(k=0;k<com; k++)
            printf(" S-> T-> Z-> R ");
    }
    else if(take[(j)]==top){
        for(k=0;k<com; k++)
            printf(" Z-> R-> S-> T ");
    }
    else if(take[(j)]==sme){
        for(k=0;k<com; k++)
            printf(" T-> Z-> R-> S ");
    }
    free(take);
    return currmax;
    //per avere il numero effettivo di pietre devo moltiplicare com*4
}

int comb_rip(int posCurr, int *mark, int *sol, int numero_pietre, int lunghezza_k, int save_pietra) {//rivedi lezioni registrate
    //k è la lunghezza corrente che sto cercando per le disposizioni/permutazioni
    //all'i-esimo elemento di sol sta l'indice che indica quale pietra metto
    //salva la pietra precedente in save
    //giocare un enum per non ricordare a mente correlazione pietra/indice
    int i;
    if (posCurr >= lunghezza_k) {
        //arriva fino a qua solo se nelle scelte precedenti ha preso almeno una pietra (in ogni scelta precedente)
        return 1;
        //anzichè tentare di tornare un massimo torno un flag
        //torna alla funzione chiamante ovvero al disp_rip qua sotto e NON alla funzione dentro multiplo comune
        //come propagare l'1 fino alla prima funzione chiamante?
        //lo ritorno alla chiamata precedente che lo torna a quello precedente eccetera

    }
    for (i = 0; i < 4; i++) {
        if(mark[i]>0 && bueno(save_pietra, i)){
            sol[posCurr] = i;
            mark[i]--;
            if(comb_rip(posCurr+1, mark, sol, numero_pietre, lunghezza_k, i))
                //questo propaga l'1 fino alla prima funzione chiamante
                return 1;
            mark[i]++;
        }
    }
    //se siamo giunti alla fine significa che nessuna scelta andava bene: ci sono ancora pietre che non potevamno prendere per raggiungere
    // la lunghezza k
    return 0;
}

int bueno(int pietra_prec, int pietraCurr){
    if(pietra_prec<0)
        return 1;
    if((pietra_prec== zaf || pietra_prec == top) && (pietraCurr== zaf || pietraCurr== rub))
        return 1;
    if((pietra_prec== rub || pietra_prec == sme) && (pietraCurr== top || pietraCurr== sme))
        return 1;
    return 0;
}
