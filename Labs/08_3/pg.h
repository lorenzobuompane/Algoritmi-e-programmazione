#ifndef INC_08_3_PG_H
#define INC_08_3_PG_H

#include "inventario.h"
#define COD 7
#define MAX_ELEMENT 8

//EQUIPAGGIAMENTO
typedef struct Tab_Equip {
    int inUso;
    inv_t *vettEq[MAX_ELEMENT];
} tabEquip_t;

//PERSONAGGIO
typedef struct Personaggio {
    char codice[COD];
    char nome[STR];
    char classe[STR];
    tabEquip_t equip;
    stat_t stat;
} pg_t;
typedef struct nodePg_t *link;
struct nodePg_t {
    pg_t pg;
    link next;
};
typedef struct Tab_pg {
    int nPg;
    link headPg;
    link tailPg;
} tabPg_t;

void acquisizionePg(tabPg_t *tabPg);
link newNode(pg_t pg, link next);
void SortListIns(tabPg_t *h, pg_t pg);
void SortListDel(tabPg_t *h, char codice[COD]);
void stampaListaPg(tabPg_t *tabPg);
void stampaPg(pg_t pg);
void addPg(tabPg_t *tabPg);
void deletePg(tabPg_t *tabPg);
void addEquip(tabPg_t *tabPg, tabInv_t *tabInv);
void deleteEquip(tabPg_t *tabPg, tabInv_t *tabInv);
void calcolaStatistiche(tabPg_t *tabPg);

#endif //INC_08_3_PG_H
