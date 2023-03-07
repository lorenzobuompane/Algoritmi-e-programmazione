#ifndef INC_28012020_GRAPH_H
#define INC_28012020_GRAPH_H

#include <stdio.h>

typedef struct edge {
    int v;
    int w;
} Edge;

typedef struct graph *Graph;

Graph GRAPHinit(int V);
void  GRAPHfree(Graph G);
Graph GRAPHload(FILE *fin);
void  GRAPHinsertE(Graph G, int id1, int id2);
void  GRAPHremoveE(Graph G, int id1, int id2);
void  GRAPHedges(Graph G, Edge *a);

void GRAPHkcore(Graph G, int k);
void GRAPHjedgesconnected(Graph G, int j);



#endif //INC_28012020_GRAPH_H
