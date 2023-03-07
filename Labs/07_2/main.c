#include <stdio.h>
#include <stdlib.h>

#define N 4

typedef struct pietra {
    int num;
    int val;
    int n_eff;
} Pietra;

typedef enum {
    zaffiri,
    rubini,
    topazi,
    smeraldi
} codifica;

typedef struct final {
    int *collana;
    int val;
    int num;
} Final;

void acquisizioneDati(FILE *fp, int *max_rip, Pietra p[]);
void disp_rip(int pos, int *sol, Final *solFin, Pietra p[], int max_rip);
int soluzione(int pos, int *sol, Pietra p[], int max_rip);
int valore(int pos, int *sol, Pietra p[]);
int accettabile(int i, int *sol, int pos, Pietra p[]);
int salvataggioCollana(Final *solFin, int *sol, int pos, int valore);
void stampaTest(Final solFin, Pietra p[], int k, int max_rip);
int controlloRipPietra(int pos, int i, int *sol, int max_rip);
void calcoloZaffiriSmeraldi(int *sol, int pos);
int ZaffiriMinoreSmeraldi(int *sol, int pos);

int main() {
    FILE *fp=fopen("e2_test_set.txt", "r");
    if (fp==NULL) return -1;
    int num_test;
    Pietra p[N];
    int max_rip;
    int *sol;
    Final solFin;

    fscanf(fp, "%d", &num_test);

    for (int k=0; k<num_test; k++) {
        acquisizioneDati(fp, &max_rip, p);
        sol=(int *)malloc((p[zaffiri].num+p[smeraldi].num+p[rubini].num+p[topazi].num)* sizeof(int));
        solFin.collana=(int *)malloc((p[zaffiri].num+p[smeraldi].num+p[rubini].num+p[topazi].num)* sizeof(int));
        solFin.num=-1;
        solFin.val=-1;
        disp_rip(0, sol, &solFin, p, max_rip);
        stampaTest(solFin, p, k+1, max_rip);
        free(sol);
        free(solFin.collana);
    }
    return 0;
}

void acquisizioneDati(FILE *fp, int *max_rip, Pietra p[]) {
    for (int i=0; i<N; i++) {
        fscanf(fp, "%d", &p[i].num);
        p[i].n_eff=p[i].num;
    }
    for (int i=0; i<N; i++)
        fscanf(fp, "%d", &p[i].val);
    fscanf(fp, "%d", max_rip);
    if (p[zaffiri].num>p[smeraldi].num)
        p[zaffiri].num=p[smeraldi].num;
    return;
}
void disp_rip(int pos, int *sol, Final *solFin, Pietra p[], int max_rip) {
    int i;
    int valoreCorrente;
    if (soluzione(pos, sol, p, max_rip)) {
        valoreCorrente=valore(pos, sol, p);
        if (valoreCorrente>solFin->val && ZaffiriMinoreSmeraldi(sol, pos)) {
            salvataggioCollana(solFin, sol, pos, valoreCorrente);
        }
        return;
    }
    for (i=0; i<N; i++) {
        if (accettabile(i, sol, pos, p) && controlloRipPietra(pos, i, sol, max_rip)) {
            p[i].num--;
            sol[pos]=i;
            disp_rip(pos+1, sol, solFin, p, max_rip);
            p[i].num++;
        }
    }
    return;
}
int soluzione(int pos, int *sol, Pietra p[], int max_rip) {
    if (pos==0) return 0;
    switch (sol[pos-1]){
        case zaffiri:
            if (p[rubini].num!=0)
                return 0;
            if (p[zaffiri].num!=0 && controlloRipPietra(pos, zaffiri, sol, max_rip))
                return 0;
            break;
        case smeraldi:
            if (p[topazi].num!=0)
                return 0;
            if (p[smeraldi].num!=0 && controlloRipPietra(pos, smeraldi, sol, max_rip))
                return 0;
            break;
        case rubini:
            if (p[smeraldi].num!=0 || p[topazi].num!=0)
                return 0;
            break;
        case topazi:
            if (p[zaffiri].num!=0 || p[rubini].num!=0)
                return 0;
            break;
    }
    return 1;
}
int valore(int pos, int *sol, Pietra p[]) {
    int valore=0;
    for (int i=0; i<pos; i++) {
        valore+=p[sol[i]].val;
    }
    return valore;
}
int accettabile(int i, int *sol, int pos, Pietra p[]) {
    if (pos==0 && p[i].num>0) return 1;
    if (p[i].num==0) return 0;
    switch (i){
        case zaffiri:
            if (sol[pos-1]==zaffiri || sol[pos-1]==topazi)
                return 1;
            break;
        case smeraldi:
            if (sol[pos-1]==smeraldi || sol[pos-1]==rubini)
                return 1;
            break;
        case rubini:
            if (sol[pos-1]==zaffiri || sol[pos-1]==topazi)
                return 1;
            break;
        case topazi:
            if (sol[pos-1]==smeraldi || sol[pos-1]==rubini)
                return 1;
            break;
        default:
            break;
    }
    return 0;
}
int salvataggioCollana(Final *solFin, int *sol, int pos, int valore) {
    solFin->num=pos;
    solFin->val=valore;
    for (int i=0; i<pos; i++)
        solFin->collana[i]=sol[i];
}
void stampaTest(Final solFin, Pietra p[], int k, int max_rip) {
    printf("TEST #%d\n", k);
    printf("zaffiro = %d [%d], "
           "rubino = %d [%d], "
           "topazio = %d [%d], "
           "smeraldo = %d [%d], "
           "TOT = %d {max_rip = %d}\n",
            p[zaffiri].n_eff, p[zaffiri].val,
            p[rubini].n_eff, p[rubini].val,
            p[topazi].n_eff, p[topazi].val,
            p[smeraldi].n_eff, p[smeraldi].val,
            p[zaffiri].n_eff+p[rubini].n_eff+p[smeraldi].n_eff+p[topazi].n_eff, max_rip);
    printf("Soluzione ottima di valore %d usando %d gemma/e\n", solFin.val, solFin.num);
    printf("Composizione collana: ");
    for (int i=0; i<solFin.num; i++) {
        switch (solFin.collana[i]) {
            case zaffiri:
                printf("z");
                break;
            case smeraldi:
                printf("s");
                break;
            case rubini:
                printf("r");
                break;
            case topazi:
                printf("t");
                break;
            default:
                break;
        }
    }
    printf("\n");
    return;
}
int controlloRipPietra(int pos, int i, int *sol, int max_rip) {
    if (pos<max_rip) return 1;
    for (int j=pos-max_rip; j<pos; j++) {
        if (sol[j] != i)
            return 1;
    }
    return 0;
}
void calcoloZaffiriSmeraldi(int *sol, int pos) {
    int n_z=0;
    int n_s=0;
    for (int j=0; j<pos; j++){
        if (sol[j]==zaffiri)
            n_z++;
        if (sol[j]==smeraldi)
            n_s++;
    }
    printf("z: %d s: %d\n\n", n_z, n_s);
}
int ZaffiriMinoreSmeraldi(int *sol, int pos) {
    int n_z=0;
    int n_s=0;
    for (int j=0; j<pos; j++){
        if (sol[j]==zaffiri)
            n_z++;
        if (sol[j]==smeraldi)
            n_s++;
    }
    if (n_z<=n_s)
        return 1;
    return 0;
}