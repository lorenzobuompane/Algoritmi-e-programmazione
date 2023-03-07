#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include "Graph.h"

struct graph {
    int V;              ///numero VERTICI
    int E;              ///numero ARCHI
    int **madj;         ///matrice delle adiacenze
    link *ladj;         ///lista delle adiacenze
    ST tab;             ///tabella di simboli
};

struct node {
    int wt;
    int v;
    link next;
};

static Edge EDGEcreate(int v, int w, int wt) {
    Edge e;
    e.v = v;
    e.w = w;
    e.wt = wt;
    return e;
}
int **MATRIXinit(int r, int c, int val) {
    int i, j;
    int **t = malloc( r * sizeof( int * ));
    if (t == NULL) {
        printf("Matrix R allocation error\n");
        return NULL;
    }

    for (int i=0; i<r; i++) {
        t[i] = malloc( c * sizeof( int ));
        if (t[i] == NULL) {
            printf("Matrix C allocation error\n");
            return NULL;
        }
    }
    for (i=0; i < r; i++)
        for (j=0; j < c; j++)
            t[i][j] = val;                  ///metto tutto a peso massimo

    return t;
}
int GRAPHcountV(FILE *fin) {
    int v=0;
    int l=0;
    int maxSTR = 5 * MAXC;
    char str[maxSTR];
    char buf[2*MAXC];
    char bufELAB[MAXC];
    char bufRETE[MAXC];
    char **vett;
    while (fgets(str, maxSTR, fin)!=NULL) {
        l++;
    }
    rewind(fin);
    vett = malloc( 2*l * sizeof( char * ));
    for (int i=0; i<2*l; i++)
        vett[i]="";
    while (fgets(str, maxSTR, fin)!=NULL) {
        sscanf(str, "%s %s %*s %*s", bufELAB, bufRETE);
        strcpy(buf, bufELAB);
        strcat(buf, bufRETE);
        for (int j=0; j<2*l; j++) {
            if (strcmp(buf, vett[j])==0)
                break;
            if (strcmp(vett[j], "")==0) {
                v++;
                vett[j] = strdup(buf);
                break;
            }
        }
        sscanf(str, "%*s %*s %s %s", bufELAB, bufRETE);
        strcpy(buf, bufELAB);
        strcat(buf, bufRETE);
        for (int j=0; j<2*l; j++) {
            if (strcmp(buf, vett[j])==0)
                break;
            if (strcmp(vett[j], "")==0) {
                v++;
                vett[j] = strdup(buf);
                break;
            }
        }
    }
    for (int i=0; i<2*l; i++)
        free(vett[i]);
    free(vett);
    rewind(fin);
    return v;
}
Graph GRAPHinit(int V) {
    Graph G = malloc(sizeof( struct graph ));
    if (G == NULL) {
        printf("Graph allocation error\n");
        return NULL;
    }
    G->V = V;
    G->E = 0;
    G->madj = MATRIXinit(V, V, INT_MAX);
    if (G->madj == NULL) {
        return NULL;
    }
    G->tab = STinit(V);
    if (G->tab == NULL) {
        return NULL;
    }
    return G;
}
Graph GRAPHload(FILE *fin) {
    int V, id1, id2, wt;
    char label1ELAB[MAXC], label1RETE[MAXC];
    char label2ELAB[MAXC], label2RETE[MAXC];
    Graph G;

    V = GRAPHcountV(fin);
    G = GRAPHinit(V);

    rewind(fin);            ///riavvolgo il file

            ///ACQUISIZIONE DI TUTTI I VERTICI E INSERIMENTO NELLA MATRICE
    while (fscanf(fin, "%s %s %s %s %d", label1ELAB, label1RETE, label2ELAB, label2RETE, &wt)==5) {
        STinsert(G->tab, label1ELAB, label1RETE);
        STinsert(G->tab, label2ELAB, label2RETE);
        id1 = STsearch(G->tab, label1ELAB, label1RETE);
        id2 = STsearch(G->tab, label2ELAB, label2RETE);
        if (id1 >= 0 && id2 >= 0)
            GRAPHinsertE(G, id1, id2, wt);
    }
    return G;
}
void GRAPHinsertE(Graph G, int id1, int id2, int wt) {
    insertE(G, EDGEcreate(id1, id2, wt));
}
static void  insertE(Graph G, Edge e) {
    int v = e.v;
    int w = e.w;
    int wt = e.wt;
    if (G->madj[v][w] == INT_MAX)
        G->E++;
    G->madj[v][w] = wt;
    G->madj[w][v] = wt;
}
void printSortV(Graph G) {
    int *vettOrd;
    int N = STreturnN(G->tab);

    vettOrd = NodeIndexSort(G->tab);

    for (int i=0; i<N; i++) {
        printf("%s\n", STsearchByIndex(G->tab, vettOrd[i]));
    }
}
void printSortAdjV(Graph G) {
    int *vettOrd = NodeIndexSort(G->tab);
    int N = STreturnN(G->tab);
    char **b;
    int min;
    char *str;
    int count=0;
    int i, k;

    b=malloc(N * sizeof(char *));

    for (k=0; k<N; k++) {
        i = vettOrd [k];
        printf("Vertici adiacenti a %s:\n", STsearchByIndex(G->tab, i));
        for (int j=0; j<G->V; j++) {
            if (G->madj[i][j]!=INT_MAX) {
                b[count] = strdup( STsearchByIndex(G->tab, j) );
                count ++;
            }
        }

        for (int i=0; i<count-1; i++) {
            min = i;
            for (int j=i+1; j<=count-1; j++) {
                if (strcmp(b[min], b[j]) > 0)
                    min = j;
            }
                str = strdup(b[i]);
                b[i] = strdup(b[min]);
                b[min] = strdup(str);
        }

        for (int i=0; i<count; i++) {
            printf("   %s\n", b[i]);
        }
        count = 0;
    }
}
int threeNodeGraph(Graph G, char *n1, char *n2, char *n3) {
    int id1 = STsearchElab(G->tab, n1);
    int id2 = STsearchElab(G->tab, n2);
    int id3 = STsearchElab(G->tab, n3);

    if (id1==-1 || id2!=-1 || id3!=-1) {
        printf("Uno o piùnodi non sono stati trovati\n");
        return -1;
    }

    if (G->madj[id1][id2]!=INT_MAX && G->madj[id1][id3]!=INT_MAX && G->madj[id2][id3]!=INT_MAX)
        return 1;
    return 0;
}
///------------ LIST ------------
Graph GRAPHlistinit(Graph G) {
    int V = G->V;
    G->ladj = malloc( V * sizeof( link ));
    for (int i = 0; i < V; i++) {
        G->ladj[i]=NULL;
    }
    return G;
}
static link NEW(int v, int wt, link next) {
    link x = malloc(sizeof *x);
    if (x == NULL)
        return NULL;
    x->v = v;
    x->wt = wt;
    x->next = next;
    return x;
}
Graph GRAPHlistload(Graph G) {
    int V = STreturnN(G->tab);
    G = GRAPHlistinit(G);
    for (int i=0; i<V; i++) {
        for (int j=i+1; j<V; j++) {
            if (G->madj[i][j]!=INT_MAX) {
                GRAPHlistinsertE(G, i, j, G->madj[i][j]);
            }
        }
    }
    return G;
}
void GRAPHlistinsertE(Graph G, int id1, int id2, int wt) {
    listinsertE(G, EDGEcreate(id1, id2, wt));
}
static void  listinsertE(Graph G, Edge e) {
    int v = e.v;
    int w = e.w;
    int wt = e.wt;

    G->ladj[v] = NEW(w, wt, G->ladj[v]);
    G->ladj[w] = NEW(v, wt, G->ladj[w]);
    G->E++;
}
void printLIST(Graph G) {
    int V = STreturnN(G->tab);
    link x;
    for (int i=0; i<V; i++) {
        printf("Nodi adiacenti a %s: \n", STsearchElabByIndex(G->tab, i));
        for (x=G->ladj[i]; x!=NULL; x=x->next) {
            printf("%s\n", STsearchElabByIndex(G->tab, x->v));
        }
        printf("\n");
    }

}