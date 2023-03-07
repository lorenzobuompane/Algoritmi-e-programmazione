#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pg.h"

void acquisizionePg(tabPg_t *tabPg) {
    FILE *fp=fopen("pg.txt", "r");
    char str[4*STR];
    pg_t tmp;
    link x;
    int i=0;
    while (fgets(str, 4*STR, fp)!=NULL) {
        sscanf(str, "%s %s %s %d %d %d %d %d %d", tmp.codice, tmp.nome, tmp.classe, &tmp.stat.hp, &tmp.stat.mp, &tmp.stat.atk, &tmp.stat.def, &tmp.stat.mag, &tmp.stat.spr);
        tmp.equip.inUso=0;
        SortListIns(tabPg, tmp);
    }
    for (x=tabPg->headPg; x->next!=NULL; x=x->next)
        i++;
    tabPg->nPg=i;
    fclose(fp);
    return;
}
link newNode(pg_t pg, link next) {
    link x = malloc(sizeof(struct nodePg_t));
    if (x==NULL)
        return NULL;
    else {
        x->pg=pg;
        x->next=next;
    }
    return x;
}
void SortListIns(tabPg_t *h, pg_t pg) {
    link x, p;
    if (h->headPg==NULL && h->tailPg==NULL) {               //LISTA VUOTA
        h->headPg=newNode(pg, h->headPg);
        h->tailPg=h->headPg;
        return;
    }
    if (strcmp(h->headPg->pg.codice, pg.codice)>0) {      //INSERIMENTO IN TESTA
        h->headPg = newNode(pg, h->headPg);
        return;
    }
    for (x=h->headPg->next, p=h->headPg; x!=NULL && strcmp(pg.codice, x->pg.codice)>0; p=x, x=x->next);
    if (x==NULL) {                                      //INSERIMENTO IN CODA
        p->next = newNode(pg, x);
        h->tailPg=p->next;
    } else p->next = newNode(pg, x);                    //INSERIMENTO IN MEZZO ALLA LISTA
    return;
}
void SortListDel(tabPg_t *h, char codice[COD]) {
    link x, p;


    if (strcmp(h->headPg->pg.codice, codice)==0) {      //CANCELLAZIONE IN TESTA
        x=h->headPg;
        h->headPg=x->next;
        if (x->next==NULL)                              //UNICO ELEMENTO
            h->tailPg=NULL;
        free(x);
        printf("ELIMINAZIONE COMPLETATA\n");
        return;
    }
    for (x=h->headPg->next, p=h->headPg; x!=NULL; p=x, x=x->next){
        if (strcmp(codice, x->pg.codice)==0){
            p->next=x->next;
            if (x->next==NULL)                          //ULTIMO ELEMENTO
                h->tailPg=p;                            //AGGIORNO CODA
            free(x);
            printf("ELIMINAZIONE COMPLETATA\n");
            return;
        }
    }

    printf("CODICE NON VALIDO\n");
}
void stampaListaPg(tabPg_t *tabPg) {
    link x;
    for (x=tabPg->headPg; x!=NULL; x=x->next)
        stampaPg(x->pg);
}
void stampaPg(pg_t pg) {
    printf("%s %s %s %d %d %d %d %d %d\n", pg.codice, pg.nome, pg.classe, pg.stat.hp, pg.stat.mp, pg.stat.atk, pg.stat.def, pg.stat.mag, pg.stat.spr);
}
void addPg(tabPg_t *tabPg) {
    pg_t tmp;
    link x;
    int prec=(tabPg->nPg);
    int i=0;
    printf("Inserisci:\n"
           "codice nome classe hp mp atk def mag spr\n");
    scanf("%s %s %s %d %d %d %d %d %d", tmp.codice, tmp.nome, tmp.classe, &tmp.stat.hp, &tmp.stat.mp, &tmp.stat.atk, &tmp.stat.def, &tmp.stat.mag, &tmp.stat.spr);
    tmp.equip.inUso=0;
    for (x=tabPg->headPg; x->next!=NULL; x=x->next) {
        if (strcmp(x->pg.codice, tmp.codice)==0) {
            printf("PERSONAGGIO ESISTENTE!\n");
            return;
        }
    }
    SortListIns(tabPg, tmp);
    for (x=tabPg->headPg; x->next!=NULL; x=x->next)
        i++;
    if (i==prec+1) {                                //CONTROLLO CHE L'AGGIUNTA SIA AVVENUTA CON SUCCESSO
        tabPg->nPg=i;
        printf("AGGIUNTA PERSONAGGIO AVVENUTA CON SUCCESSO!\n");
    } else printf("ERRORE AGGIUNTA PERSONAGGIO\n");
    return;
}
void deletePg(tabPg_t *tabPg) {
    char codice[COD];
    if (tabPg->headPg==NULL && tabPg->tailPg==NULL){            //LISTA VUOTA
        printf("LISTA VUOTA\n");
        return;
    }
    stampaListaPg(tabPg);
    printf("\nInserisci codice da eliminare:\n");
    scanf("%s", codice);
    SortListDel(tabPg, codice);
    return;
}
void addEquip(tabPg_t *tabPg, tabInv_t *tabInv){
    char codice[COD];
    char nome[STR];
    link x;
    stampaListaPg(tabPg);
    printf("Inserisci codice personaggio:\n");
    scanf("%s", codice);
    for (x=tabPg->headPg; x!=NULL; x=x->next) {
        if (strcmp(x->pg.codice, codice)==0)
            break;                                                              //x PERSONAGGIO SCELTO
    }
    if (x==NULL) {                                      //PERSONAGGIO INESISTENTE
        printf("Personaggio non esistente!\n");
        return;
    }
    if (x->pg.equip.inUso>=MAX_ELEMENT) {
        printf("Personaggio equipaggiato al massimo!\n");               //VETTORE EQUIPAGGIAMENTO PIENO
        return;
    }
    printf("\n");
    stampaVettoreInv(tabInv);
    printf("Inserire nome oggetto nell'inventario\n");
    scanf("%s", nome);                                                  //ogg INVENTARIO SCELTO
    for (int i=0; i<tabInv->nInv; i++) {
        if (strcmp(tabInv->vettInv[i].nome, nome)==0) {
            x->pg.equip.vettEq[x->pg.equip.inUso]=&(tabInv->vettInv[i]);
            (x->pg.equip.inUso)++;
            return;
        }
    }
    printf("Oggetto non esistente!\n");                                 //OGGETTO INESISTENTE
    return;
}
void deleteEquip(tabPg_t *tabPg, tabInv_t *tabInv) {
    char codice[COD];
    char nome[STR];
    link x;
    stampaListaPg(tabPg);
    printf("Inserisci codice personaggio:\n");
    scanf("%s", codice);
    for (x=tabPg->headPg; x!=NULL; x=x->next) {
        if (strcmp(x->pg.codice, codice)==0)
            break;                                                              //x PERSONAGGIO SCELTO
    }
    if (x==NULL) {                                      //PERSONAGGIO INESISTENTE
        printf("Personaggio non esistente!\n");
        return;
    }
    if (x->pg.equip.inUso==0) {                                                 //VETTORE EQUIPAGGIAMENTO VUOTO
        printf("Vettore equipaggiamento vuoto!\n");
        return;
    }
    printf("\n");
    for (int i=0; i<x->pg.equip.inUso; i++)
        stampaOggetto(*(x->pg.equip.vettEq[i]));
    printf("Inserire nome oggetto nell'inventario\n");
    scanf("%s", nome);                                                  //ogg INVENTARIO SCELTO
    for (int i=0; i<x->pg.equip.inUso; i++) {
        if (strcmp(x->pg.equip.vettEq[i]->nome, nome)){
            x->pg.equip.vettEq[i]=NULL;
            (x->pg.equip.inUso)--;
            return;
        }
    }
    printf("Oggetto non presente nel vettore equipaggiamento!\n");      //ogg NON PRESENTE IN VETTORE EQUIPAGGIAMENTO
}
void calcolaStatistiche(tabPg_t *tabPg) {
    stat_t tmp;
    link x;
    char codice[COD];
    stampaListaPg(tabPg);
    printf("Inserisci codice personaggio:\n");
    scanf("%s", codice);
    for (x=tabPg->headPg; x!=NULL; x=x->next) {
        if (strcmp(x->pg.codice, codice)==0)
            break;                                                              //x PERSONAGGIO SCELTO
    }
    if (x==NULL) {                                      //PERSONAGGIO INESISTENTE
        printf("Personaggio non esistente!\n");
        return;
    }
    //STATISTICHE DEL PERSONAGGIO
    tmp.hp=x->pg.stat.hp;
    tmp.mp=x->pg.stat.mp;
    tmp.atk=x->pg.stat.atk;
    tmp.def=x->pg.stat.def;
    tmp.mag=x->pg.stat.mag;
    tmp.spr=x->pg.stat.spr;
    //AGGIUNGO STATISTICHE EQUIPAGGIAMENTI
    for (int i=0; i<x->pg.equip.inUso; i++) {
        tmp.hp=tmp.hp+x->pg.equip.vettEq[i]->stat.hp;
        tmp.mp=tmp.mp+x->pg.equip.vettEq[i]->stat.mp;
        tmp.atk=tmp.atk+x->pg.equip.vettEq[i]->stat.atk;
        tmp.def=tmp.def+x->pg.equip.vettEq[i]->stat.def;
        tmp.mag=tmp.mag+x->pg.equip.vettEq[i]->stat.mag;
        tmp.spr=tmp.spr+x->pg.equip.vettEq[i]->stat.spr;
    }
    if (tmp.hp<1)
        tmp.hp=1;
    if (tmp.mp<1)
        tmp.mp=1;
    if (tmp.atk<1)
        tmp.atk=1;
    if (tmp.def<1)
        tmp.def=1;
    if (tmp.mag<1)
        tmp.mag=1;
    if (tmp.spr<1)
        tmp.spr=1;
    printf("\nStatistiche giocatore %s [%d oggetti equipaggiamento/i]:\n", x->pg.codice, x->pg.equip.inUso);
    printf("\thp: %d\n"
           "\tmp: %d\n"
           "\tatk: %d\n"
           "\tdef: %d\n"
           "\tmag: %d\n"
           "\tspr: %d\n", tmp.hp, tmp.mp, tmp.atk, tmp.def, tmp.mag, tmp.spr);
}


