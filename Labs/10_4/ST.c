#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ST.h"

struct node {
    char *elab;
    char *rete;
};

struct symboltable {
    ID *a;               ///nome nodo: elab rete
    int maxN;            ///massimo caratteri stringa
    int N;               ///numero VERTICI
};

ST STinit(int maxN) {
    ST st;
    st = malloc(sizeof(struct symboltable));
    if (st == NULL) {
        printf("Symbol Table allocation error\n");
        return NULL;
    }
    st->a = calloc(maxN, sizeof( ID ));         ///alloco il vettore di maxN
    if (st->a == NULL) {
        printf("Symbol Table Vector allocation error\n");
        free(st);
        return NULL;
    }
    for (int i=0; i<maxN; i++) {
        st->a[i] = malloc(sizeof(ID));
        st->a[i]->elab = malloc(MAXC * sizeof( char ));
        st->a[i]->rete = malloc(MAXC * sizeof( char ));
        if (st->a[i]->elab == NULL || st->a[i]->rete == NULL) {
            printf("Symbol Table Elab or Rete allocation error\n");
            for (int j=i; j==0; j--) {
                free(st->a[j]->elab);
                free(st->a[j]->rete);
            }
            free(st->a);
            free(st);
            return NULL;
        }
    }
    st->maxN = maxN;
    st->N = 0;
    return st;
}
void STinsert(ST st, char *elab, char *rete) {
    int found=0;
    for (int i=0; i<st->N; i++) {
        if (strcmp(elab, st->a[i]->elab)==0 && strcmp(rete, st->a[i]->rete)==0) {       ///controllo che non ci sia già il vertice
            found = 1;
        }
    }
    if (found==0) {
        strcpy(st->a[st->N]->elab, elab);         ///inserisco nella i-esima posizione, ovvero a N
        strcpy(st->a[st->N]->rete, rete);
        st->N++;
    }
}

///------------ SEARCH BY NAME ------------
int STsearch(ST st, char *elab, char *rete) {
    int i;
    for (i=0; i<st->N; i++)
        if (st->a[i]!=NULL && strcmp(elab, st->a[i]->elab)==0 && strcmp(rete, st->a[i]->rete)==0)
            return i;
    return -1;
}
int STsearchElab(ST st, char *elab) {
    int i;
    for (i=0; i<st->N; i++)
        if (st->a[i]!=NULL && strcmp(elab, st->a[i]->elab)==0)
            return i;
    return -1;
}
int STsearchRete(ST st, char *rete) {
    int i;
    for (i=0; i<st->N; i++)
        if (st->a[i]!=NULL && strcmp(rete, st->a[i]->rete)==0)
            return i;
    return -1;
}
///----------------------------------------

///------------ SEARCH BY INDEX ------------
char * STsearchByIndex(ST st, int i) {
    if (i < 0 || i >= st->N)
        return NULL;
    return STreturnStrByElabRete(STsearchElabByIndex(st, i), STsearchReteByIndex(st, i));
}
char * STsearchElabByIndex(ST st, int i) {
    if (i < 0 || i >= st->N)
        return NULL;
    return (st->a[i]->elab);
}
char * STsearchReteByIndex(ST st, int i) {
    if (i < 0 || i >= st->N)
        return NULL;
    return (st->a[i]->rete);
}
///----------------------------------------

int STreturnN(ST st) {
    return st->N;
}
char * STreturnStrByElabRete (char * elab, char * rete) {
    char *str = malloc(2*MAXC+1 * sizeof( char ));
    strcpy(str, elab);
    strcat(str, " ");
    strcat(str, rete);
    return str;
}

///------------ VETTORE DI ORDINAMENTO ------------
//ritorno un vettore con gli indici dei dei nodi in ordine alfabetico
int * NodeIndexSort(ST st) {
    int * sort = malloc( st->N * sizeof( int ));
    int min=0;
    ID buf;
    ID *b = malloc(st->N* sizeof(ID));

    for (int i=0; i<st->N; i++){
        b[i] = malloc(sizeof( ID ));
        b[i]->elab = malloc(MAXC * sizeof( char ));
        b[i]->rete = malloc(MAXC * sizeof( char ));
        b[i]->elab = st->a[i]->elab;
        b[i]->rete = st->a[i]->rete;
    }

    for (int i=0; i<st->N-1; i++) {
        min = i;
        for (int j=i+1; j<=st->N-1; j++) {
            if (strcmp(b[min]->elab, b[j]->elab) > 0) {
                min = j;
            }
        }
            buf = b[i];
            b[i] = b[min];
            b[min] = buf;
    }
    for (int i=0; i<st->N; i++) {
        sort[i]=STsearch(st, b[i]->elab, b[i]->rete);
    }
    return sort;
}
///------------------------------------------------