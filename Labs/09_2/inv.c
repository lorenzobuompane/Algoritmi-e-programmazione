#include "inv.h"

void stat_read(FILE *fp, stat_t *statp) {
    fscanf(fp, "%d %d %d %d %d %d", &statp->hp, &statp->mp, &statp->atk, &statp->def, &statp->mag, &statp->spr);
    return;
}

void stat_print(FILE *fp, stat_t *statp, int soglia) {
    if (statp->hp<soglia)
        fprintf(fp, "%d ", soglia);
    else fprintf(fp, "%d ", statp->hp);
    if (statp->mp<soglia)
        fprintf(fp, "%d ", soglia);
    else fprintf(fp, "%d ", statp->mp);
    if (statp->atk<soglia)
        fprintf(fp, "%d ", soglia);
    else fprintf(fp, "%d ", statp->atk);
    if (statp->def<soglia)
        fprintf(fp, "%d ", soglia);
    else fprintf(fp, "%d ", statp->def);
    if (statp->mag<soglia)
        fprintf(fp, "%d ", soglia);
    else fprintf(fp, "%d ", statp->mag);
    if (statp->spr<soglia)
        fprintf(fp, "%d ", soglia);
    else fprintf(fp, "%d ", statp->spr);
    return;
}

void inv_read(FILE *fp, inv_t *invp) {
    fscanf(fp, "%s %s", invp->nome, invp->tipo);
    stat_read(fp, &invp->stat);
    return;
}

void inv_print(FILE *fp, inv_t *invp) {
    fprintf(fp, "%s %s ", invp->nome, invp->tipo);
    stat_print(fp, &invp->stat, 1);
    printf("\n");
    return;
}

stat_t inv_getStat(inv_t *invp) {
    return invp->stat;
}

stat_t stat_init() {
    stat_t tmp;
    tmp.hp=0;
    tmp.mp=0;
    tmp.atk=0;
    tmp.def=0;
    tmp.mag=0;
    tmp.spr=0;
    return tmp;
}