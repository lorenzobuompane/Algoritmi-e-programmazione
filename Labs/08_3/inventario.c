#include <stdio.h>
#include <stdlib.h>
#include "inventario.h"

void acquisizioneInv(tabInv_t *tabInv) {
    FILE *fp=fopen("inventario.txt", "r");
    fscanf(fp, "%d", &tabInv->nInv);
    tabInv->maxInv=tabInv->nInv;
    tabInv->vettInv=malloc((tabInv->nInv)*sizeof(inv_t));
    for (int i=0; i<tabInv->nInv; i++)
        fscanf(fp, "%s %s %d %d %d %d %d %d", tabInv->vettInv[i].nome, tabInv->vettInv[i].tipologia, &tabInv->vettInv[i].stat.hp, &tabInv->vettInv[i].stat.mp, &tabInv->vettInv[i].stat.atk, &tabInv->vettInv[i].stat.def, &tabInv->vettInv[i].stat.mag, &tabInv->vettInv[i].stat.spr);
    fclose(fp);
    return;
}
void stampaVettoreInv(tabInv_t *tabInv) {
    for (int i=0; i<tabInv->nInv; i++)
        stampaOggetto(tabInv->vettInv[i]);
}
void stampaOggetto(inv_t inventario) {
    printf("%s %s %d %d %d %d %d %d\n", inventario.nome, inventario.tipologia, inventario.stat.hp, inventario.stat.mp, inventario.stat.atk, inventario.stat.def, inventario.stat.mag, inventario.stat.spr);
}