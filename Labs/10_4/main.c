#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

void sottoGrafo(Graph G);

int main() {
    Graph G;
    FILE *fin = fopen("grafo.txt", "r");
    if (fin == NULL)
        exit(1);


    G = GRAPHload(fin);
/*
    printSortV(G);
    printf("------------------------\n");
    printSortAdjV(G);
*/

   // sottoGrafo(G);


   G = GRAPHlistload(G);
   printLIST(G);


    printf("");

    return 0;
}

void sottoGrafo(Graph G) {
    char *str1 = malloc(MAXC * sizeof( char ));
    char *str2 = malloc(MAXC * sizeof( char ));
    char *str3 = malloc(MAXC * sizeof( char ));
    int sottografo;

    printSortV(G);
    printf("\nControllo esistenza sottografo nei tre nodi:\t[node1 node2 node3]\n");
    scanf("%s %s %s", str1, str2, str3);
    sottografo = threeNodeGraph(G, str1, str2, str3);

    if (sottografo)
        printf("Esiste un sottografo tra i nodi %s %s %s\n", str1, str2, str3);
    else if (sottografo==-1)
        return;
    else printf("Non esiste un sottografo tra i nodi %s %s %s\n", str1, str2, str3);
    return;
}