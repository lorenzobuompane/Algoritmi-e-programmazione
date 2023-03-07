#include "pgList.h"

typedef struct nodePg_t *link;
struct nodePg_t {
    pg_t pg;
    link next;
};

struct pgList_s {
    int nPg;
    link headPg;
    link tailPg;
};

pgList_t pgList_init() {
    pgList_t tmp=malloc(sizeof(struct pgList_s));
    tmp->headPg=NULL;
    tmp->tailPg=NULL;
    tmp->nPg=0;
    return tmp;
}

void pgList_free(pgList_t pgList) {
    for (int i=0; i<pgList->nPg; i++) {
        pgList_remove(pgList, pgList->tailPg->pg.cod);
    }
    pgList->nPg=0;
    free(pgList);
}

void pgList_read(FILE *fp, pgList_t pgList) {
    acquisizionePg(fp, pgList);
}

void pgList_print(FILE *fp, pgList_t pgList, invArray_t invArray) {
    link x;
    for (x=pgList->headPg; x!=NULL; x=x->next)
        pg_print(fp, &x->pg, invArray);
}

void pgList_insert(pgList_t pgList, pg_t pg) {
    SortListIns(pgList, pg);
}

void pgList_remove(pgList_t pgList, char* cod) {
    SortListDel(pgList, cod);
}

pg_t *pgList_searchByCode(pgList_t pgList, char* cod) {
    link x;
    for (x=pgList->headPg; x!=NULL; x=x->next)
        if (strcmp(x->pg.cod, cod)==0)
            return &x->pg;
    return NULL;
}

///FUNZIONI AGGIUNTE

void acquisizionePg(FILE *fp, pgList_t tabPg) {
    pg_t tmp;
    link x;
    int i=0;
    while (pg_read(fp, &tmp)) {
        pgList_insert(tabPg, tmp);
    }
    for (x=tabPg->headPg; x->next!=NULL; x=x->next)
        i++;
    tabPg->nPg=i;
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

void SortListIns(pgList_t h, pg_t pg) {
    link x, p;
    if (h->headPg==NULL && h->tailPg==NULL) {               //LISTA VUOTA
        h->headPg=newNode(pg, h->headPg);
        h->tailPg=h->headPg;
        return;
    }
    if (strcmp(h->headPg->pg.cod, pg.cod)>0) {      //INSERIMENTO IN TESTA
        h->headPg = newNode(pg, h->headPg);
        return;
    }
    for (x=h->headPg->next, p=h->headPg; x!=NULL && strcmp(pg.cod, x->pg.cod)>0; p=x, x=x->next);
    if (x==NULL) {                                      //INSERIMENTO IN CODA
        p->next = newNode(pg, x);
        h->tailPg=p->next;
    } else p->next = newNode(pg, x);                    //INSERIMENTO IN MEZZO ALLA LISTA
    return;
}

void SortListDel(pgList_t h, char cod[LEN]) {
    link x, p;
    if (strcmp(h->headPg->pg.cod, cod)==0) {      //CANCELLAZIONE IN TESTA
        x=h->headPg;
        h->headPg=x->next;
        if (x->next==NULL)                              //UNICO ELEMENTO
            h->tailPg=NULL;
        pg_clean(&x->pg);
        free(x);
        //printf("ELIMINAZIONE COMPLETATA\n");
        return;
    }
    for (x=h->headPg->next, p=h->headPg; x!=NULL; p=x, x=x->next){
        if (strcmp(cod, x->pg.cod)==0){
            p->next=x->next;
            if (x->next==NULL)                          //ULTIMO ELEMENTO
                h->tailPg=p;                            //AGGIORNO CODA
            pg_clean(&x->pg);
            free(x);
            //printf("ELIMINAZIONE COMPLETATA\n");
            return;
        }
    }
    printf("CODICE NON VALIDO\n");
}

