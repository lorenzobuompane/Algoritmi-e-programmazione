#include <stdio.h>
#include <stdlib.h>

#define N 10

int main()
{
    int v[N];
    int i=0;
    int j=0;
    int nMax=0;
    int n=0;

    printf("Inserire vettore:\n");
    for (i=0; i<N; i++){
        scanf("%d", &v[i]);
    }
    printf("Acquisizione completata \n\n");

    for (i=0; i<N; i++){
        if (v[i]!=0 && i!=N-1)
            n++;

        else {
            if (v[i]!=0)
                n++;
            if (n>nMax){
                nMax=n;
            }
            n=0;
        }
    }

    n=0;

    for (i=0; i<N; i++){

        if (v[i]!=0 && i!=N-1)
            n++;

        else {
            if (v[i]!=0)
                n++;
            if (n==nMax) {
                for(j=i-nMax; j<i; j++)
                    if (v[i]!=0)
                        printf("%d ", v[j+1]);
                    else
                        printf("%d ", v[j]);
                printf("\n");
            }
            n=0;
        }
    }
    return 0;
}
