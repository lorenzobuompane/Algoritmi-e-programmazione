#include "pg.h"

int pg_read(FILE *fp, pg_t *pgp) {
    char str[LEN];
    if (fgets(str, LEN, fp)!=NULL) {
        sscanf(str, "%s %s %s %d %d %d %d %d %d", pgp->cod, pgp->nome, pgp->classe, &pgp->b_stat.hp, &pgp->b_stat.mp, &pgp->b_stat.atk, &pgp->b_stat.def, &pgp->b_stat.mag, &pgp->b_stat.spr);
        pgp->equip=equipArray_init();
        pgp->eq_stat=pgp->b_stat;
        return 1;
    }
    return 0;
    /*
    pgp->eq_stat.hp=pgp->b_stat.hp;
    pgp->eq_stat.mp=pgp->b_stat.mp;
    pgp->eq_stat.atk=pgp->b_stat.atk;
    pgp->eq_stat.def=pgp->b_stat.def;
    pgp->eq_stat.mag=pgp->b_stat.mag;
    pgp->eq_stat.spr=pgp->b_stat.spr;
     */
}

void pg_clean(pg_t *pgp) {
    equipArray_free(pgp->equip);
}

void pg_print(FILE *fp, pg_t *pgp, invArray_t invArray) {
    fprintf(fp, "%s %s %s ", pgp->cod, pgp->nome, pgp->classe);
    stat_print(fp, &pgp->eq_stat, 1);
    printf("\n");
    //fprintf(fp, "%d %d %d %d %d %d\n", pgp->eq_stat.hp, pgp->eq_stat.mp, pgp->eq_stat.atk, pgp->eq_stat.def, pgp->eq_stat.mag, pgp->eq_stat.spr);
    if (equipArray_inUse(pgp->equip)>0){
        equipArray_print(fp, pgp->equip, invArray);
    }
}

void pg_updateEquip(pg_t *pgp, invArray_t invArray) {
    stat_t tmp=stat_init();
    stat_t ogg;
    int index;
    equipArray_update(pgp->equip, invArray);
    ///RICALCOLA STATISTICHE
    for (int i=0; i<EQUIP_SLOT; i++) {
        index=equipArray_getEquipByIndex(pgp->equip, i);
        if (index!=-1) {
            ogg=inv_getStat(invArray_getByIndex(invArray, index));
            tmp=addStat(tmp, ogg);
        }
    }
    pgp->eq_stat=addStat(pgp->b_stat, tmp);
}

stat_t addStat(stat_t tmp, stat_t ogg) {
    tmp.hp+=ogg.hp;
    tmp.mp+=ogg.mp;
    tmp.atk+=ogg.atk;
    tmp.def+=ogg.def;
    tmp.mag+=ogg.mag;
    tmp.spr+=ogg.spr;
    return tmp;
}