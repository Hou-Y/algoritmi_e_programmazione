#include "pg.h"

int pg_read(FILE *fp, pg_t *pgp){
    if(fscanf(fp, " %s %s %s ", pgp->cod, pgp->nome, pgp->classe)==3){
        // i pg hanno due set di stat dentro quale metto? eq_stat sono le statistihe con equipaggiamento
        pgp->equip=(equipArray_init());
        stat_read(fp, &(pgp->b_stat));
        pgp->eq_stat=pgp->b_stat; //funge
        return 1;
    }
    return 0;
    //funzioni per lettura di statistiche
    //torna un intero, 1 se c'è ancora da leggere, 0 se ho terminato la lettura file
}

void pg_clean(pg_t *pgp){
    //cosa pg ha allocato dinamicamente
    equipArray_free(pgp->equip);
}

void pg_print(FILE *fp, pg_t *pgp, invArray_t invArray){
    fprintf(fp," %s %s %s ",
            pgp->cod, pgp->nome,  pgp->classe);
}

void pg_updateEquip(pg_t *pgp, invArray_t invArray){
    int indice, i;
    inv_t *ogg;
    stat_t ogg_stat;
    //appena equipaggia fai calcoli bonus malus
    equipArray_update(pgp->equip, invArray);
    indice=equipArray_inUse(pgp->equip);
    pgp->eq_stat=pgp->b_stat;
    for(i=0; i<indice; i++){
        ogg= invArray_getByIndex(invArray, equipArray_getEquipByIndex(pgp->equip, i));
        ogg_stat=inv_getStat(ogg);
        pgp->eq_stat.atk+=ogg_stat.atk;
        pgp->eq_stat.def+=ogg_stat.def;
        pgp->eq_stat.hp+=ogg_stat.hp;
        pgp->eq_stat.mag+=ogg_stat.mag;
        pgp->eq_stat.mp+=ogg_stat.mp;
        pgp->eq_stat.spr+=ogg_stat.spr;
    }
}