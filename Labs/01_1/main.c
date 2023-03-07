#include <stdio.h>
#include <stdlib.h>

#define n 4
#define m 11

int main()
{
    int campionato[n][m];
    int classifica[n];
    int punti=0;
    int indice=-1;

    //apertura file
    FILE *fp;
    fp=fopen("campionato.txt", "r");
    if (fp==NULL)
        return -1;
    //lettura file
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            fscanf(fp, "%d", &campionato[i][j]);
        }
    }
    //azzero classifica
    for (int i=0; i<n; i++) {
        classifica[i]=0;
    }
    //ciclo le giornate
    for (int j=0; j<m; j++) {
        //calcolo la classifica aggiornata alla j-esima giornata
        for (int i=0; i<n; i++) {
            classifica[i]=classifica[i]+campionato[i][j];
        }
        //calcolo capolista
        punti=classifica[0];
        indice=0;
        for (int i=1; i<n; i++) {
            if (classifica[i]>punti) {
                punti=classifica[i];
                indice=i;
            }
        }
        //stampa capolista di giornata
        printf("La capolista della giornata %d e' la squadra numero %d con %d punti\n", j+1, indice+1, punti);
    }
    printf("\nLA SQUADRA %d E' CAMPIONE CON %d PUNTI!!\n", indice+1, punti);

    return 0;
}


