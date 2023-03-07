#include <stdio.h>
#include <stdlib.h>

int ** malloc2dR(int nr, int nc);
void mallocVettori(int nr, int nc, int **b, int **n);
void acquisizioneFile(FILE *fp, int ** mat, int nr, int nc);
void stampaMatrice(int ** mat, int nr, int nc);
void stampaVettore(char colore[10], int dim, int *vet);
void separa(int **mat, int nr, int nc, int *b, int *n);
void free2d(int **mat, int nr);

int main() {

    FILE *fp=fopen("mat.txt", "r");
    if (fp==NULL)
        return -1;

    int nr, nc;
    int **mat;
    int *b;
    int *n;

    fscanf(fp, "%d %d", &nr, &nc);
    mat=malloc2dR(nr, nc);
    acquisizioneFile(fp, mat, nr, nc);
    stampaMatrice(mat, nr, nc);
    mallocVettori(nr, nc, &b, &n);
    separa(mat, nr, nc, b, n);
    stampaVettore("Bianchi", ((nr*nc)-((nr*nc)/2)), b);
    stampaVettore("Neri", ((nr*nc)/2), n);
    free2d(mat, nr);
    free(b);
    free(n);

    return 0;
}

int ** malloc2dR(int nr, int nc) {
    int **mat;
    mat=(int **)malloc(nr* sizeof(int *));
    for (int i=0; i<nr; i++)
        mat[i]=(int *)malloc(nc* sizeof(int));
    return mat;
}

void acquisizioneFile(FILE *fp, int ** mat, int nr, int nc) {
    for (int i=0; i<nr; i++)
        for (int j=0; j<nc; j++)
            fscanf(fp, "%d", &mat[i][j]);
}

void stampaMatrice(int ** mat, int nr, int nc) {
    for (int i=0; i<nr; i++) {
        for (int j=0; j<nc; j++)
            printf("%d ", mat[i][j]);
        printf("\n");
    }
}

void mallocVettori(int nr, int nc, int **b, int **n) {
    int dim = nr*nc;
    *n=(int *)malloc((nr*nc)/2* sizeof(int));
    *b=(int *)malloc((dim-(nr*nc)/2)* sizeof(int));     //SE dim DISPARI BIANCO PIù GRANDE
}

void separa(int **mat, int nr, int nc, int *b, int *n) {
    int iB=0;
    int iN=0;
    for (int i=0; i<nr; i++)
        for (int j=0; j<nc; j++) {
            if ((i%2==0 && j%2==0) ||  (i%2!=0 && j%2!=0)) {
                b[iB] = mat[i][j];
                iB++;
            }
            else {
                n[iN]=mat[i][j];
                iN++;
            }
        }
}

void stampaVettore(char colore[10], int dim, int *vet) {
    printf("%s\n", colore);
    for (int j=0; j<dim; j++)
        printf("%d ", vet[j]);
    printf("\n");
}

void free2d(int **mat, int nr) {
    for (int i=0; i<nr; i++)
        free(mat[i]);
    free(mat);
}