#ifndef GRAPH_H
#define GRAPH_H

#include "ST.h"

typedef struct edge {
    int v;
    int w;
    int wt;
} Edge;
typedef struct graph *Graph;
typedef struct node* link;

int GRAPHcountV(FILE *fin);
Graph GRAPHinit(int V);
Graph GRAPHload(FILE *fin);
void GRAPHinsertE(Graph G, int id1, int id2, int wt);
static void  insertE(Graph G, Edge e);
void printSortV(Graph G);
void printSortAdjV(Graph G);
int threeNodeGraph(Graph G, char *n1, char *n2, char *n3);
///------------ LIST ------------
Graph GRAPHlistinit(Graph G);
static link NEW(int v, int wt, link next);
Graph GRAPHlistload(Graph G);
void GRAPHlistinsertE(Graph G, int id1, int id2, int wt);
static void  listinsertE(Graph G, Edge e);
void printLIST(Graph G);
///------------------------------


#endif
