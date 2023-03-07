#include <stdio.h>
#include <stdlib.h>
#define N 4

typedef struct Matrici {
    int ****z, ****r, ****t, ****s;
}matr_t;

int **** matr_init(int nZ, int nR, int nT, int nS);
matr_t* matr_struct_init(int nZ, int nR, int nT, int nS);
void matr_free(int ****m, int nZ, int nR, int nT, int nS);
void matr_struct_free(matr_t *m, int nZ, int nR, int nT, int nS);
int fZ(matr_t *m, int nZ, int nR, int nT, int nS);
int fR(matr_t *m, int nZ, int nR, int nT, int nS);
int fT(matr_t *m, int nZ, int nR, int nT, int nS);
int fS(matr_t *m, int nZ, int nR, int nT, int nS);
int findMax(int rZ, int rR, int rT, int rS);

int main() {
    FILE *fp=fopen("hard_test_set.txt", "r");
    matr_t *m;
    int n_collane;
    int nZ, nR, nT, nS;
    int rZ, rR, rT, rS;
    int max;

    fscanf(fp, "%d", &n_collane);
    for (int i=1; i<=n_collane; i++) {                                                   /// i = NUMERO DEL TEST
        fscanf(fp, "%d %d %d %d", &nZ, &nR, &nT, &nS);
        m=matr_struct_init(nZ+1, nR+1, nT+1, nS+1);                     ///sovralloco per evitare SIGSERV
        rZ=fZ(m, nZ-1, nR, nT, nS)+1;
        rR=fR(m, nZ, nR-1, nT, nS)+1;
        rT=fT(m, nZ, nR, nT-1, nS)+1;
        rS=fS(m, nZ, nR, nT, nS-1)+1;
        max=findMax(rZ, rR, rT, rS);
        printf("TEST #%d\n", i);
        printf("zaffiro = %d, rubino = %d, topazio = %d, smeraldo = %d, TOT = %d\n", nZ, nR, nT, nS, nZ+nR+nT+nS);
        printf("Lunghezza massima collana: %d\n", max);
        matr_struct_free(m, nZ, nR, nT, nS);
    }

    fclose(fp);
    return 0;
}
matr_t* matr_struct_init(int nZ, int nR, int nT, int nS) {
    matr_t *m;
    m=malloc(sizeof(matr_t));

    m->z=matr_init(nZ, nR, nT, nS);
    m->r=matr_init(nZ, nR, nT, nS);
    m->t=matr_init(nZ, nR, nT, nS);
    m->s=matr_init(nZ, nR, nT, nS);

    return m;
}
int **** matr_init(int nZ, int nR, int nT, int nS) {
    int ****p;

    p=malloc(nZ* sizeof(int***));
    for (int z=0; z<nZ; z++) {
        p[z]=malloc(nR* sizeof(int**));
        for (int r=0; r<nR; r++) {
            p[z][r]=malloc(nT* sizeof(int*));
            for (int t=0; t<nT; t++) {
                p[z][r][t]=malloc(nS* sizeof(int));
            }
        }
    }
    for (int z=0; z<nZ; z++) {
        for (int r=0; r<nR; r++) {
            for (int t=0; t<nT; t++) {
                for(int s=0; s<nS; s++) {
                    p[z][r][t][s]=-1;
                }
            }
        }
    }

    return p;
}
void matr_struct_free(matr_t *m, int nZ, int nR, int nT, int nS) {
    matr_free(m->z, nZ, nR, nT, nS);
    matr_free(m->r, nZ, nR, nT, nS);
    matr_free(m->t, nZ, nR, nT, nS);
    matr_free(m->s, nZ, nR, nT, nS);

}
void matr_free(int ****m, int nZ, int nR, int nT, int nS) {
    for (int z=0; z<nZ; z++) {
        for (int r=0; r<nR; r++) {
            for (int t=0; t<nT; t++) {
                    free(m[z][r][t]);
            }
        }
    }
    for (int z=0; z<nZ; z++) {
        for (int r=0; r<nR; r++) {
                free(m[z][r]);
        }
    }
    for (int z=0; z<nZ; z++) {
            free(m[z]);
    }
    free(m);
}
int findMax(int rZ, int rR, int rT, int rS) {
    int m1, m2;
    if (rZ>rR)
        m1=rZ;
    else m1=rR;
    if (rT>rS)
        m2=rT;
    else m2=rS;
    if (m1>m2)
        return m1;
    return m2;

}

int fZ(matr_t *m, int nZ, int nR, int nT, int nS) {
    int r1, r2;
    if (nZ<0)     ///controllo sulla pietra corrente (se è minore di 0 significa che è entrato nella funzione ma non aveva più pietre disponibili)
        return -1;      ///tolgo pietra presa incorrettamente

    if (m->z[nZ][nR][nT][nS]!=-1)
        return m->z[nZ][nR][nT][nS]+1;

    r1=fZ(m, nZ-1, nR, nT, nS);
    r2=fR(m, nZ, nR-1, nT, nS);

    if (r1>r2)
        m->z[nZ][nR][nT][nS]=r1;
    else m->z[nZ][nR][nT][nS]=r2;

    return m->z[nZ][nR][nT][nS]+1;
}
int fR(matr_t *m, int nZ, int nR, int nT, int nS) {
    int r1, r2;
    if (nR<0)     ///controllo sulla pietra corrente (se è minore di 0 significa che è entrato nella funzione ma non aveva più pietre disponibili)
        return -1;      ///tolgo pietra presa incorrettamente

    if (m->r[nZ][nR][nT][nS]!=-1)
        return m->r[nZ][nR][nT][nS]+1;

    r1=fS(m, nZ, nR, nT, nS-1);
    r2=fT(m, nZ, nR, nT-1, nS);

    if (r1>r2)
        m->r[nZ][nR][nT][nS]=r1;
    else m->r[nZ][nR][nT][nS]=r2;

    return m->r[nZ][nR][nT][nS]+1;
}
int fT(matr_t *m, int nZ, int nR, int nT, int nS) {
    int r1, r2;
    if (nT<0)     ///controllo sulla pietra corrente (se è minore di 0 significa che è entrato nella funzione ma non aveva più pietre disponibili)
        return -1;      ///tolgo pietra presa incorrettamente

    if (m->t[nZ][nR][nT][nS]!=-1)
        return m->t[nZ][nR][nT][nS]+1;

    r1=fZ(m, nZ-1, nR, nT, nS);
    r2=fR(m, nZ, nR-1, nT, nS);

    if (r1>r2)
        m->t[nZ][nR][nT][nS]=r1;
    else m->t[nZ][nR][nT][nS]=r2;

    return m->t[nZ][nR][nT][nS]+1;
}
int fS(matr_t *m, int nZ, int nR, int nT, int nS) {
    int r1, r2;
    if (nS<0)     ///controllo sulla pietra corrente (se è minore di 0 significa che è entrato nella funzione ma non aveva più pietre disponibili)
        return -1;      ///tolgo pietra presa incorrettamente

    if (m->s[nZ][nR][nT][nS]!=-1)
        return m->s[nZ][nR][nT][nS]+1;

    r1=fS(m, nZ, nR, nT, nS-1);
    r2=fT(m, nZ, nR, nT-1, nS);

    if (r1>r2)
        m->s[nZ][nR][nT][nS]=r1;
    else m->s[nZ][nR][nT][nS]=r2;

    return m->s[nZ][nR][nT][nS]+1;
}