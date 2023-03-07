#include <stdio.h>

#define MAXR 50

typedef struct coordinate {
    int i;
    int j;
} coordinate;

typedef struct output {
    coordinate estremo;
    int base;
    int altezza;
    int area;
} output;

int switch_function (int a1, int a2);
void leggiMatrice(int region[][MAXR], int max, int *nr, int *nc);
void spampaMatrice(int pInt[50][50], int nr, int nc);
int switch_function (int a1, int a2);
int riconosciRegione(int M[50][50], int nr, int nc, int r, int c, int *b, int *h);
int controlloEstremo(int M[50][50], int r, int c);

int main() {
    int nr, nc;
    int region[MAXR][MAXR];
    int b=0;
    int h=0;
    output base, altezza, area;
    base.base=0;
    altezza.altezza=0;
    area.area=0;

    leggiMatrice(region, MAXR, &nr, &nc);
    spampaMatrice(region, nr, nc);
    for (int r = 0; r < nr; r++) {
        for (int c = 0; c < nc; c++) {
            if (riconosciRegione(region, nr, nc, r, c, &b, &h)) {
                printf("Regione con estremo sinistro [%d, %d]: base %d, altezza %d\n", r+1, c+1, b, h);
                //CONFRONTO PER BASE
                if (switch_function(base.base, b)){
                    base.base=b;
                    base.altezza=h;
                    base.area=b*h;
                    base.estremo.i=r;
                    base.estremo.j=c;
                }
                //CONFRONTO PER ALTEZZA
                if (switch_function(altezza.altezza, h)){
                    altezza.base=b;
                    altezza.altezza=h;
                    altezza.area=b*h;
                    altezza.estremo.i=r;
                    altezza.estremo.j=c;
                }
                //CONFRONTO PER AREA
                if (switch_function(area.area, b*h)){
                    area.base=b;
                    area.altezza=h;
                    area.area=b*h;
                    area.estremo.i=r;
                    area.estremo.j=c;
                }
            }
        }
    }
    printf("\n");
    printf("Massima base: estremo superiore sinistro: <%d, %d> base=%d, altezza=%d, area=%d\n", base.estremo.i, base.estremo.j, base.base, base.altezza, base.area);
    printf("Massima area: estremo superiore sinistro: <%d, %d> base=%d, altezza=%d, area=%d\n", area.estremo.i, area.estremo.j, area.base, area.altezza, area.area);
    printf("Massima altezza: estremo superiore sinistro: <%d, %d> base=%d, altezza=%d, area=%d\n", altezza.estremo.i, altezza.estremo.j, altezza.base, altezza.altezza, altezza.area);



    return 0;
}

int riconosciRegione(int M[50][50], int nr, int nc, int r, int c, int *b, int *h) {
    int flag=controlloEstremo(M, r, c);
    if (flag){
        *b=1;
        *h=1;
        //TROVO ALTEZZA
        for (int i=r+1; i<nr; i++) {
            if (M[i][c]==1)
                *h=*h+1;
            else
                break;
        }
        //TROVO BASE
        for (int j=c+1; j<nc; j++) {
            if (M[r][j]==1)
                *b=*b+1;
            else
                break;
        }
        return 1;
    }
    return 0;
}

int controlloEstremo(int M[50][50], int r, int c) {
    if (M[r][c]==1) {
        if (r==0 && c==0){
            return 1;
        }
        else if (r==0) {
            if (M[r][c-1]==0)
                return 1;
            return 0;
        }
        else if (c==0) {
            if (M[r-1][c]==0)
                return 1;
            return 0;
        }
        else {
            if (M[r][c-1]==0 && M[r-1][c]==0)
                return 1;
            return 0;
        }
    }
    return 0;
}

void spampaMatrice(int pInt[50][50], int nr, int nc) {
    printf("Stampo matrice:\n");
    for (int i = 0; i < nr; i++) {
        for (int j = 0; j < nc; j++) {
            printf("%d ", pInt[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void leggiMatrice(int region[][MAXR], int max, int *nr, int *nc) {
    FILE *fp=fopen("region.txt", "r");
    if (fp==NULL)
        printf("Errore mell'apertura del file\n");
    else {
        fscanf(fp, "%d %d", nr, nc);
        for (int i = 0; i < *nr; i++) {
            for (int j = 0; j < *nc; j++) {
                fscanf(fp,"%d", &region[i][j]);
            }
        }
    }
    fclose(fp);
}

int switch_function (int a1, int a2)
{
    if (a2>a1)
        return 1;
    return 0;
}