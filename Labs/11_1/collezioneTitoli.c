//
// Created by loren on 20/01/2020.
//

#include "collezioneTitoli.h"
#include <limits.h>

typedef struct Transazione* trans_t;

struct Transazione {
    tempo_t dataora;
    int valore;
    int numero;
    trans_t TRANSnext;
};

struct collTitoli {
    title_t TITLEhead;
    int TITLEnum;
};

struct titolo {
    char name[MAXC];
    trans_t TRANShead;
    int TRANSnum;
    BSTquot_t BSThead;
    title_t TITLEnext;
};

collTitle_t LISTinit() {
    collTitle_t list = malloc(sizeof(struct collTitoli));
    list->TITLEhead=NULL;
    list->TITLEnum=0;
    return list;
}

collTitle_t LISTinsTitle(collTitle_t c, char name[MAXC]) {
    title_t x, p;
    if (c->TITLEhead == NULL || strcmp(name, c->TITLEhead->name) < 0) {
        c->TITLEhead = LISTnewnode(name, c->TITLEhead);
        c->TITLEnum++;
        return c;
    }

    for (x=c->TITLEhead->TITLEnext, p=c->TITLEhead; x != NULL && strcmp(x->name, name) < 0; p=x, x=x->TITLEnext);
    p->TITLEnext = LISTnewnode(name, x);
    c->TITLEnum++;
    return c;
}

title_t LISTnewnode(char name[MAXC], title_t next) {
    title_t t = malloc(sizeof(*t));
    t->BSThead = NULL;
    t->TRANShead = NULL;
    t->TRANSnum=0;
    strcpy(t->name, name);
    t->TITLEnext=next;
    return t;
}

int checkTitolo(title_t list, char name[MAXC]) {
    for (title_t t=list; t!=NULL; t=t->TITLEnext)
        if (strcmp(t->name, name)==0)
            return 1;
    return 0;
}

collTitle_t TITLEaddfromFile(collTitle_t c, char nomefile[MAXC]) {
    int n, nt;
    char name[MAXC];
    struct Transazione t;
    FILE *fp = fopen(nomefile, "r");

    fscanf(fp, "%d", &n);

    for (int i=0; i<n; i++) {
        fscanf(fp, "%s %d", name, &nt);
        if (!checkTitolo(c->TITLEhead, name)) {
            c=LISTinsTitle(c, name);
        }
        addTransNumber(c, name, nt);
        for (int j=0; j<nt; j++) {
            fscanf(fp, "%d/%d/%d %d:%d %d %d", &t.dataora.data.aa, &t.dataora.data.mm, &t.dataora.data.gg, &t.dataora.ora.hh, &t.dataora.ora.mm, &t.valore, &t.numero);
            c=LISTinsTrans(name, c, t.dataora, t.valore, t.numero);
        }
    }
    fclose(fp);

    return c;
}

void addTransNumber(collTitle_t c, char name[MAXC], int nt) {
    for (title_t t=c->TITLEhead; t != NULL; t=t->TITLEnext)
        if (strcmp(t->name, name)==0) {
            t->TRANSnum += nt;
            return;
        }
}

collTitle_t LISTinsTrans(char name[MAXC], collTitle_t c, tempo_t dataora, int valore, int numero) {
    title_t t;
    trans_t n = malloc(sizeof(struct Transazione));
    for (t=c->TITLEhead; t != NULL; t=t->TITLEnext)
        if (strcmp(t->name, name)==0)
            break;

    n->dataora=dataora;
    n->valore=valore;
    n->numero=numero;
    n->TRANSnext=t->TRANShead;
    t->TRANShead=n;
    return c;
}

collTitle_t TITLEfilesadd(collTitle_t c, char n1[MAXC], char n2[MAXC], char n3[MAXC]) {
    c = TITLEaddfromFile(c, n1);
    c = TITLEaddfromFile(c, n2);
    c = TITLEaddfromFile(c, n3);

    QUOTupdate(c);
    return c;
}

void stampaLista(collTitle_t c){
    title_t t;

    for (t=c->TITLEhead; t != NULL; t=t->TITLEnext) {
        stampaTitolo(t);
    }
}

void stampaTitolo(title_t t) {
    trans_t tr;
    printf("%s:\n", t->name);
    for (tr=t->TRANShead; tr != NULL; tr=tr->TRANSnext)
        printf("\t %d/%d/%d %d:%d %d %d\n", tr->dataora.data.aa, tr->dataora.data.mm, tr->dataora.data.gg, tr->dataora.ora.hh, tr->dataora.ora.mm, tr->valore, tr->numero);

}

void QUOTupdate(collTitle_t list) {
    title_t title = list->TITLEhead;
    trans_t trans, t;
    quot_t q;
    float v=0;
    float n=0;

    if (title == NULL)
        return;

    while (title!=NULL) {
        trans = title->TRANShead;
        while (trans!=NULL) {
             if (!BSTdateExist(title->BSThead, trans->dataora.data)) {
                 t=trans;
                 q.data=t->dataora.data;
                 while (t!=NULL) {
                     if (DATEcmp(t->dataora.data, q.data)==0) {
                         v+=(float)(t->valore*t->numero);
                         n+=(float)t->numero;
                     }
                     t=t->TRANSnext;
                 }
                 q.QUOTgiornaliera=(v)/n;
                 title->BSThead=BSTinsert(title->BSThead, q);
                 v=0;
                 n=0;
             }
            trans = trans->TRANSnext;
        }
        title = title->TITLEnext;
    }


}


void ricercaTitolo(collTitle_t c, char str[MAXC]) {
    title_t tmp;
    if (!checkTitolo(c->TITLEhead, str)) {
        printf("Titolo non trovato!\n");
        return;
    }
    for (tmp=c->TITLEhead; tmp!=NULL; tmp=tmp->TITLEnext)
        if (strcmp(str, tmp->name)==0) {
            stampaTitolo(tmp);
            return;
        }

}

void ricercaQuotazione(collTitle_t c, char str[MAXC], data_t d) {
    title_t tmp;
    if (!checkTitolo(c->TITLEhead, str)) {
        printf("Titolo non trovato!\n");
        return;
    }
    for (tmp=c->TITLEhead; tmp!=NULL; tmp=tmp->TITLEnext)
        if (strcmp(str, tmp->name)==0) {
            stampaTitolo(tmp);
            if (BSTdateExist(tmp->BSThead, d))
                BSTstampaQuotazione(tmp->BSThead, d);
            else
                printf("Data non trovata nel titolo scelto!\n");
            return;
        }
}



void ricercaQuotazioniData(collTitle_t c, char str[MAXC], data_t d1, data_t d2) {
    title_t tmp;
    float min = INT_MAX;
    float max = INT_MIN;
    if (!checkTitolo(c->TITLEhead, str)) {
        printf("Titolo non trovato!\n");
        return;
    }
    for (tmp = c->TITLEhead; tmp != NULL; tmp = tmp->TITLEnext)
        if (strcmp(str, tmp->name) == 0) {
            stampaTitolo(tmp);
            BSTsearch(tmp->BSThead, d1, d2, &min, &max);
        }
    if (min==INT_MAX || max==INT_MIN)
        printf("Nessun dato valido!\n");
    else
        printf("MINIMO : %f\nMASSIMO : %f\n", min, max);
}

void ricercaQuotazioniALL(collTitle_t c, char str[MAXC]) {
    title_t tmp;
    float min = INT_MAX;
    float max = INT_MIN;
    if (!checkTitolo(c->TITLEhead, str)) {
        printf("Titolo non trovato!\n");
        return;
    }
    for (tmp = c->TITLEhead; tmp != NULL; tmp = tmp->TITLEnext)
        if (strcmp(str, tmp->name) == 0) {
            stampaTitolo(tmp);
            BSTsearchALL(tmp->BSThead, &min, &max);
        }
    if (min==INT_MAX || max==INT_MIN)
        printf("Nessun dato valido!\n");
    else
        printf("MINIMO : %f\nMASSIMO : %f\n", min, max);
}

void bilanciamento(collTitle_t c, char str[MAXC], int soglia) {
    title_t title = c->TITLEhead;
    int min=INT_MAX;
    int max=INT_MIN;
    int rapporto;
    while (title!=NULL) {
        if (strcmp(str, title->name)==0) {
            BSTcamminoHEAD(title->BSThead, &min, &max);
            printf("%s \nmin: %d, max; %d\n", title->name, min, max);
            if (min==0 && max!=0)
                rapporto=INT_MAX;
            else if (min==0 && max==0)
                rapporto=-1;
            else rapporto = max/min;
            if (rapporto>soglia) {
/*
                printf("\n-----------\n");
                BSTprintIN(title->BSThead);
                printf("\n-----------\n");
*/
                title->BSThead = BSTbalance(title->BSThead);
                min=INT_MAX;
                max=INT_MIN;
                BSTcamminoMINMAX(title->BSThead, &min, &max, 0);
                printf("BILANCIO\nmin: %d, max; %d\n\n", min, max);
/*
                printf("\n-----------\n");
                BSTprintIN(title->BSThead);
                printf("\n-----------\n");
*/
                return;
            } else
                printf("NON BILANCIO\n\n");
        }
        title=title->TITLEnext;
    }
}

