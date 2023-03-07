#include <stdlib.h>
#include <stdio.h>
#include "ST.h"
#include "Graph.h"

#define MAXC 11

struct graph {
    int V;
    int E;
    int **madj;
    ST tab;
    int *vett;
    int *grado;
};

static int **MATRIXint(int r, int c, int val);
static void  insertE(Graph G, Edge e);
static Edge  EDGEcreate(int v, int w);
static void  removeE(Graph G, Edge e);


static int **MATRIXint(int r, int c, int val) {
    int i, j;
    int **t = malloc(r * sizeof(int *));
    if (t==NULL)
        return NULL;

    for (i=0; i < r; i++) {
        t[i] = malloc(c * sizeof(int));
        if (t[i]==NULL)
            return NULL;
    }
    for (i=0; i < r; i++)
        for (j=0; j < c; j++)
            t[i][j] = val;
    return t;
}

static void  insertE(Graph G, Edge e) {
    int v = e.v, w = e.w;

    if (G->madj[v][w] == 0)
        G->E++;
    G->madj[v][w] = 1;
    G->madj[w][v] = 1;
    G->grado[v]++;
    G->grado[w]++;
}

static Edge EDGEcreate(int v, int w) {
    Edge e;
    e.v = v;
    e.w = w;
    return e;
}

static void  removeE(Graph G, Edge e) {
    int v = e.v, w = e.w;
    if (G->madj[v][w] == 1)
        G->E--;
    G->madj[v][w] = 0;
    G->madj[w][v] = 0;
    G->grado[v]--;
    G->grado[w]--;
}



////////////////////////////////////////////


Graph GRAPHinit(int V) {
    Graph G = malloc(sizeof *G);
    if (G == NULL)
        return NULL;
    G->V = V;
    G->E = 0;
    G->madj = MATRIXint(V, V, 0);
    if (G->madj == NULL)
        return NULL;
    G->tab = STinit(V);
    if (G->tab == NULL)
        return NULL;
    G->vett = malloc(V* sizeof(int));
    if (G->vett==NULL)
        return NULL;
    for (int i=0; i<V; i++)
        G->vett[i]=1;        ///inizializzo il vettore che viene usato nella k-core a 1 (preso), quando viene eliminato sarà messo a 0
    G->grado = malloc(V* sizeof(int));
    if (G->grado==NULL)
        return NULL;
    for (int i=0; i<V; i++)
        G->grado[i]=0;       ///inizializzo il vettore con i gradi a 0
    return G;
}

void GRAPHfree(Graph G) {
    int i;
    for (i=0; i<G->V; i++)
        free(G->madj[i]);
    free(G->madj);
    STfree(G->tab);
    free(G->vett);
    free(G->grado);
    free(G);
}

Graph GRAPHload(FILE *fin) {
    int V, i, id1, id2;
    char label1[MAXC], label2[MAXC];
    Graph G;

    fscanf(fin, "%d", &V);
    G = GRAPHinit(V);

    for (i=0; i<V; i++) {
        fscanf(fin, "%s", label1);
        STinsert(G->tab, label1, i);
    }

    while(fscanf(fin, "%s %s", label1, label2) == 2) {
        id1 = STsearch(G->tab, label1);
        id2 = STsearch(G->tab, label2);
        if (id1 >= 0 && id2 >=0)
            GRAPHinsertE(G, id1, id2);
    }
    return G;
}

void GRAPHinsertE(Graph G, int id1, int id2) {
    insertE(G, EDGEcreate(id1, id2));
}

void GRAPHremoveE(Graph G, int id1, int id2) {
    removeE(G, EDGEcreate(id1, id2));
}

void  GRAPHedges(Graph G, Edge *a) {
    int v, w, E = 0;
    for (v=0; v < G->V; v++)
        for (w=v+1; w < G->V; w++)
            if (G->madj[v][w] == 1)
                a[E++] = EDGEcreate(v, w);
}

//////////////////////////////////////

static Graph GRAPHkcoreremove(Graph G, int i);
static int CHECKkcore(Graph G, int k);
static int EXISTkcore(Graph G);
static void PRINTkcore(Graph G);
static void GRAPHrestore(Graph G);


static Graph GRAPHkcoreremove(Graph G, int i) {
    G->vett[i]=0;
    G->grado[i]=-1;
    for (int j=0; j<G->V; j++) {
        if (G->madj[i][j]==1)
            G->grado[j]--;
    }
    return G;
}

static int CHECKkcore(Graph G, int k) {
    for (int i=0; i<G->V; i++) {
        if (G->grado[i]<k && G->vett[i]!=0)
            return 0;
    }
    return 1;
}

static int EXISTkcore(Graph G) {
    for (int i=0; i<G->V; i++) {
        if (G->grado[i]!=-1)
            return 1;
    }
    return 0;
}

static void PRINTkcore(Graph G) {
    for (int i=0; i<G->V; i++) {
        if (G->vett[i]==1)
            printf("%s\n", STsearchByIndex(G->tab, i));
    }
}

static void GRAPHrestore(Graph G) {
    for (int i=0; i<G->V; i++) {
        G->vett[i]=1;
        G->grado[i]=0;
    }
    for (int i=0; i<G->V; i++) {
        for (int j=i+1; j<G->V; j++) {
            if (G->madj[i][j]==1) {
                G->grado[i]++;
                G->grado[j]++;
            }
        }
    }
}


void GRAPHkcore(Graph G, int k) {
    while (CHECKkcore(G, k)==0) {
        for (int i=0; i<G->V; i++) {
            if (G->grado[i]<k && G->vett[i]!=0) {
                G = GRAPHkcoreremove(G, i);
            }
        }
    }
    if (EXISTkcore(G)==1) {
        printf("Stampo vertici del %d-core:\n", k);
        PRINTkcore(G);
    }
    else
        printf("Non esiste un %d-core\n", k);

    GRAPHrestore(G);
}


//////////////////////////////////////////
static void comb_sempl(Graph G, int pos, Edge *val, Edge *remove, int E, int j, int start, int *flag);
static int CHECKjedgesconnected(Graph G, Edge *remove, int j);
static int GRAPHcc(Graph G);
static void dfsRcc(Graph G, int v, int id, int *cc);

static void comb_sempl(Graph G, int pos, Edge *val, Edge *remove, int E, int j, int start, int *flag) {
    int i;

    if (*flag==1)
        return;

    if (pos==j) {
        if (CHECKjedgesconnected(G, remove, j)>1) {
            (*flag)=1;
        }
        return;
    }

    for (i=start; i<E; i++) {
        if (*flag==0) {
            remove[pos] = val[i];
            comb_sempl(G, pos+1, val, remove, E, j, i+1, flag);
        }
    }
}

static int CHECKjedgesconnected(Graph G, Edge *remove, int j) {
    for (int i=0; i<j; i++) {
        GRAPHremoveE(G, remove[i].v, remove[i].w);
    }

    int id=GRAPHcc(G);

    for (int i=0; i<j; i++)
        GRAPHinsertE(G, remove[i].v, remove[i].w);
    return id;      ///1 = una componente connessa 2 = due componenti connesse
}

static int GRAPHcc(Graph G) {
    int v, id = 0, *cc;
    cc = malloc(G->V * sizeof(int));
    if (cc == NULL)
        return -1;

    for (v = 0; v < G->V; v++)
        cc[v] = -1;

    for (v = 0; v < G->V; v++)
        if (cc[v] == -1)
            dfsRcc(G, v, id++, cc);

    free(cc);
    return id;
}

static void dfsRcc(Graph G, int v, int id, int *cc) {
    int j;
    cc[v]=id;
    for (j=0; j<G->V; j++) {
        if (G->madj[v][j]==1)
            if (cc[j]==-1)
                dfsRcc(G, j, id, cc);
    }
}

void GRAPHjedgesconnected(Graph G, int j) {
    Edge *a;
    Edge *remove;
    int flag=0;

    a=malloc(G->E * sizeof(Edge));
    remove=malloc(j * sizeof(Edge));

    GRAPHedges(G, a);

    if (j!=1) {
        printf("Verifico l'esistenza di insiemi di archi di cardinalita' minore di %d in grado di sconnetterlo\n\n", j);
        for (int i=1; i<j; i++) {
            comb_sempl(G, 0, a, remove, G->E, i, 0, &flag);
            if (flag==0)
                printf("%d-edge-connected: NO\n", i);
            if (flag==1) {
                printf("%d-edge-connected: SI\n"
                       "Esiste un insieme di archi j1 < %d (j1 = %d) in grado di disconnettere G\n", i, j, i);
                for (int k=0; k<i; k++) {
                    printf("%s-%s\n", STsearchByIndex(G->tab, remove[k].v), STsearchByIndex(G->tab, remove[k].w));
                }
                break;
            }
        }
    }

    if (flag==0) {
        comb_sempl(G, 0, a, remove, G->E, j, 0, &flag);
        if (flag == 1) {
            printf("%d-edge-connected: SI\n"
                   "Insieme di archi di cardinalita' %d che sconnette G\n", j, j);
            for (int i = 0; i < j; i++) {
                printf("%s-%s\n", STsearchByIndex(G->tab, remove[i].v), STsearchByIndex(G->tab, remove[i].w));
            }
        } else
            printf("%d-edge-connected: NO\n", j);;
    }
}