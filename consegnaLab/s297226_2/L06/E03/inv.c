#include "inv.h"

void stat_read(FILE *fp, stat_t *statp){
    fscanf(fp, " %d %d %d %d %d %d",
           &(statp->hp),
           &(statp->mp),
           &(statp->atk),
           &(statp->def),
           &(statp->mag),
           &(statp->spr)    );
}

void stat_print(FILE *fp, stat_t *statp, int soglia){
    //un metodo più compatto o più veloce rispetto a questo?
    statp->hp >=soglia ? fprintf(fp, " %d ", statp->hp) : fprintf(fp, " %d ", 1);
    statp->mp >=soglia ? fprintf(fp, " %d ", statp->mp) : fprintf(fp, " %d ", 1);
    statp->atk >=soglia ? fprintf(fp, " %d ", statp->atk) : fprintf(fp, " %d ", 1);
    statp->def >=soglia ? fprintf(fp, " %d ", statp->def) : fprintf(fp, " %d ", 1);
    statp->mag >=soglia ? fprintf(fp, " %d ", statp->mag) : fprintf(fp, " %d ", 1);
    statp->spr >=soglia ? fprintf(fp, " %d ", statp->spr) : fprintf(fp, " %d ", 1);
    //fprintf(fp, " %d %d %d %d %d %d ", (statp->hp), (statp->mp), (statp->atk), (statp->def), (statp->mag), (statp->spr));
}

void inv_read(FILE *fp, inv_t *invp){
    fscanf(fp, " %s %s ", invp->nome, invp->tipo);
    stat_read(fp, &(invp->stat));
}

void inv_print(FILE *fp, inv_t *invp){
    fprintf(fp, "\n%s %s ", invp->nome, invp->tipo);
    stat_print(fp, &(invp->stat), 1);
}

stat_t inv_getStat(inv_t *invp){
    //dato un puntatore a un oggetto ne estraggo la struct delle statistiche?
    return invp->stat;
}
