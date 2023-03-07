#include <stdio.h>
#include "Graph.h"

int main( int argc, char **argv) {
    FILE *fin = fopen(argv[1], "r");        ///grafo.txt
    Graph G;
    int k=-1, j=-1;

    if (fin==NULL)
        return -1;

    printf("-> INIZIALIZZO E CARICO DA FILE IL GRAFO\n");
    G = GRAPHload(fin);
    if (G==NULL)
        return -2;
    fclose(fin);

    printf("\n");

    printf("-> K-CORE\n");
    while (k<0) {
        printf("Inserire il numero k>=0:\n");
        scanf("%d", &k);
    }
    GRAPHkcore(G, k);

    printf("\n");

    printf("-> J-EDGE-CONNECTED\n");
    while (j<1) {
        printf("Inserire il numero j:\n");
        scanf("%d", &j);
    }
    GRAPHjedgesconnected(G, j);

    printf("\n");

    printf("-> LIBERO LO SPAZIO ALLOCATO\n");
    GRAPHfree(G);

    return 0;
}
