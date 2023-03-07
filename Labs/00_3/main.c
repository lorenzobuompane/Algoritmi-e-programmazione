#include <stdio.h>
#include <stdlib.h>
#define NMAX 30

void ruota (int v[], int N, int P, int dir);

int main()
{
    int N;
    int P=1;
    int dir;
    int v[NMAX];

    //dimensione
    printf("Inserire dimenzione del vettore:\n");
    scanf("%d", &N);
    if (N>NMAX)
        return -1;

    //vettore
    printf("Inserisci vettore di %d valori:\n", N);
    for (int i=0; i<N; i++)
        scanf("%d", &v[i]);

    //ruota
    do {
        printf("Inserisci posizioni da ruotare:\n");
        scanf("%d", &P);
        if (P!=0) {
            printf("Inserisci direzione (-1 = DX\t1 = SX):\n");
            scanf("%d", &dir);
            ruota(v, N, P, dir);
        }
    }
    while (P==0);

    //stampo vettore
    printf("\nStampo vettore ruotato:\t");
    for (int i=0; i<N; i++)
        printf("%d ", v[i]);

    return 0;
}


void ruota (int v[], int N, int P, int dir)
{
    int copia[N];
    //DX
    if (dir==-1) {
        for (int i=0; i<N; i++) {
            if ((i+P)<N)
                copia[i+P]=v[i];
            else
                copia[(i+P)-N]=v[i];
        }
    }
    //SX
    else if (dir==1) {
        for (int i=0; i<N; i++) {
            if ((i-P)<0)
                copia[(i-P)+N]=v[i];
            else
                copia[i-P]=v[i];
        }
    }
    for (int i=0; i<N; i++)
        v[i]=copia[i];
}
