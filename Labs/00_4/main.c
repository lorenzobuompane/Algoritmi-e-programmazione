#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 20

void sottomatrice (int matrice[MAX][MAX], int nr, int nc, int dim, int indiciMAX[2], int mMAX[MAX][MAX]);

int main()
{
    int matrice[MAX][MAX];
    char nomefile[MAX];
    int nr;
    int nc;
    int dim;
    int min;

    FILE *fp;

    int mMAX[MAX][MAX];
    int indiciMAX[2];       //sommaMAX e dimMAX
        indiciMAX[0]=INT_MIN;
        indiciMAX[1]=0;

    //acquisizione nome file e apertura
    printf("Inserisci nome file:\n");
    scanf("%s", nomefile);
    fp=fopen(nomefile, "r");
    if (fp==NULL)
        return -1;

    //acquisizione dimensione matrice
    fscanf(fp, "%d", &nr);
    fscanf(fp, "%d", &nc);
    if (nr<nc)
        min=nr;
    else
        min=nc;

    //acquisizione matrice
    for (int i=0; i<nr; i++) {
        for (int j=0; j<nc; j++)
            fscanf(fp, "%d", &matrice[i][j]);
    }

    //stampa matrice letta
    printf("\nMatrice acquisita: \n");
    for (int i=0; i<nr; i++) {
        for (int j=0; j<nc; j++)
            printf("%d ", matrice[i][j]);
        printf("\n");
    }

    //ciclo sottomatrici
    do {
        //lettura dimensione
        printf("\nInserisci dimensione sottomatrice compresa tra 1 e %d:\n", min);
        scanf("%d", &dim);
        printf("\n");

        //controllo dimensione
        if (1<=dim && dim<=min) {
            //cerco sottomatrici
            sottomatrice (matrice, nr, nc, dim, indiciMAX, mMAX);
        }
        else
            printf("\nDimensione non corretta!\n");

        //stampo sottomatrice massima
        printf("\nStampo matrice di somma massima %d e dimensione %d:\n", indiciMAX[0], indiciMAX[1]);
        for (int i=0; i<indiciMAX[1]; i++) {
            for (int j=0; j<indiciMAX[1]; j++) {
                printf("%d ", mMAX[i][j]);
            }
            printf("\n");
        }
    }
    while (1<=dim && dim<=min);





    fclose(fp);


    return 0;
}

void sottomatrice (int matrice[MAX][MAX], int nr, int nc, int dim, int indiciMAX[2], int mMAX[MAX][MAX])
{
    int somma=0;
    int r=0;
    int c=0;

    //ciclo esterno: scandisco tutti i primi elemento della matrice dim X dim
    for (int i=0; i<=nr-dim; i++) {
        for (int j=0; j<=nc-dim; j++)
        {
            //ciclo interno sottomatrice
            for (int a=i; a<dim+i; a++) {
                for (int b=j; b<dim+j; b++) {
                    printf("%d ", matrice[a][b]);
                    somma=somma+matrice[a][b];
                }
                printf("\n");
            }
            printf("---\n");
            //controllo sottomatrice massima
            if (somma>indiciMAX[0]) {
                for (int a=i; a<dim+i; a++) {
                    for (int b=j; b<dim+j; b++) {
                        mMAX[r][c]=matrice[a][b];
                        c++;
                    }
                    r++;
                    c=0;
                }
                indiciMAX[0]=somma;
                indiciMAX[1]=dim;
            }
            r=0;
            c=0;
            somma=0;
        }
    }
}
