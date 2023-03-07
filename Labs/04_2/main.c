#include <stdio.h>

#define NVET 7
//#define NVET 8

int majority( int *a, int n);
void QuickSort(int *A, int N);
void QuickSortR( int *A, int l, int r );
int partition ( int *A, int l, int r );
void Swap(int *v, int n1, int n2);

        int main() {
    int maggioritario=-1;
    int vet[NVET]={3,3,9,4,7,5,3};      //N=7 con #maggioritario < N/2
//    int vet[NVET]={3,3,9,4,3,5,3};      //N=7 con #maggioritario > N/2
//    int vet[NVET]={0,1,0,2,3,4,0,5};    //N=8 con #maggioritario < N/2
//    int vet[NVET]={0,1,0,0,3,4,0,5};    //N=8 con #maggioritario = N/2
//    int vet[NVET]={0,1,0,0,3,4,0,0};    //N=8 con #maggioritario > N/2
/*
    //INSERISCO I DATI NEL VETTORE
    printf("Inserisci numero naturali nel vettore: \n");
    for (int i = 0; i < NVET; i++) {
        scanf("%d", &vet[i]);
    }
*/
    //CERCO E STAMPO MAGGIORITARIO
    maggioritario=majority(vet, NVET);
    if (maggioritario>=0)
        printf("Elemento maggioritario %d!", maggioritario);
    else printf("Nessun elemento maggioritario trovato!");

    return 0;
}
int majority( int *a, int N) {
    QuickSort(a, N);
/*
    for (int i = 0; i <N ; ++i) {
        printf("%d ", a[i]);
    }
*/
    if (a[0]==a[N/2])
        return a[0];
    return -1;
}

void QuickSort(int *A, int N) {
    int l=0, r=N-1;
    QuickSortR(A, l, r);
}

void QuickSortR( int *A, int l, int r ) {
    int q;
    if (r <= l)
        return;
    q = partition(A, l, r);
    QuickSortR(A, l, q-1);
    QuickSortR(A, q+1, r);
    return;
}

int partition ( int *A, int l, int r ) {
    int i, j;
    int x = A[r];
    i = l-1;
    j = r;
    for ( ; ; ) {
        while(A[++i]<x);
        while(A[--j]>x)
            if (j == l)
                break;
        if (i >= j)
            break;
        Swap(A, i, j);
    }
    Swap(A, i, r);
    return i;
}

void Swap(int *v, int n1, int n2) {
    int	temp;

    temp  = v[n1];
    v[n1] = v[n2];
    v[n2] = temp;
    return;
}