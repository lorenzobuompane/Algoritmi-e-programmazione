#include <stdio.h>
#include <stdlib.h>

typedef struct Vertex {
    int x , y;
} Vertex;

int acquisizioneFile(int *n, int *e, Vertex **grafo);
void acquisizioneNodi(int **nodi, int n);
void powerset(int pos, int *val, int *sol, int n, Vertex *grafo, int e);
int check(Vertex *grafo, int *sol, int e);

int main() {
    Vertex *grafo;
    int *nodi;
    int *sol;
    int N;
    int E;

    if (acquisizioneFile(&N, &E, &grafo)==0)
        return -1;

    printf("INSIEME DEGLI ARCHI:\n");
    for (int i=0; i<E; i++)
        printf("%d, %d\n", grafo[i].x, grafo[i].y);
    printf("\n");

    acquisizioneNodi(&nodi, N);
    sol=(int*)malloc(N* sizeof(int));

    powerset(0, nodi, sol, N, grafo, E);

    return 0;
}

int acquisizioneFile(int *n, int *e, Vertex **grafo) {
    FILE *fp = fopen("grafo.txt", "r");
    if (fp==NULL)
        return 0;
    Vertex *g;
    fscanf(fp, "%d %d", n, e);
    g=(Vertex *)malloc(*e * sizeof(struct Vertex));
    for (int i=0; i<*e; i++)
        fscanf(fp, "%d %d", &g[i].x, &g[i].y);
    *grafo=g;
    return 1;
}

void acquisizioneNodi(int **nodi, int n) {
    int *tmp=(int *)malloc(n* sizeof(int));
    for (int i=0; i<n; i++)
        tmp[i]=i;
    *nodi=tmp;
}

void powerset(int pos, int *val, int *sol, int n, Vertex *grafo, int e) {
    int i;

    if (pos >= n) {
        if (check(grafo, sol, e)==1) {
            printf("{ ");
            for (i = 0; i < n; i++)
                if (sol[i] != 0)
                    printf("%d ", i);
            printf("} \n");
        }
        return;
    }

    sol[pos] = 0;
    powerset(pos+1, val, sol, n, grafo, e);
    sol[pos] = 1;
    powerset(pos+1, val, sol, n, grafo, e);
    return;
}

int check(Vertex *grafo, int *sol, int e) {

    for (int i=0; i<e; i++) {
        if (sol[grafo[i].x]==0 && sol[grafo[i].y]==0)
            return 0;
    }
    return 1;
}