#include <stdio.h>
#include <stdlib.h>

typedef struct Tile {
    char c0;
    int v0;
    char c1;
    int v1;
    int orientamento;       // -1: NON PRESO
                            //  0: PRESO (c0,v0) ORIZZONTALE (c1,v1) VERTICALE
                            //  1: PRESO (c1,v1) ORIZZONTALE (c0,v0) VERTICALE
    int n_tile;
} tile_t;
typedef struct Tiles {
    tile_t *tiles;
    int numTiles;
} tabTiles_t;
typedef struct Board {
    tile_t ***board;
    int nr;
    int nc;
} tabBoard_t;
typedef struct Solution {
    tabBoard_t *tabB;
    tabTiles_t *tabT;
    int val;
} tabSolution_t;

void acquisizioneTiles(tabTiles_t *tabT);
void acquisizioneBoard(tabBoard_t *tabB, tabTiles_t *tabT);
void stampaTiles(tabTiles_t *tabT);
void stampaBoard(tabBoard_t *tabB);
void disp_rip(int pos, tabTiles_t *tabT, tabBoard_t *tabB, tabSolution_t *tabS, int n, int k);
int checkSol(tabBoard_t *tabB);
void copiaSol(tabSolution_t *tabS, tabBoard_t *tabB, tabTiles_t *tabT);
void allocoSol(tabSolution_t *tabS, int numTiles, int nr, int nc);

int main() {
    tabBoard_t *tabB=malloc(sizeof(tabBoard_t));
    tabTiles_t *tabT=malloc(sizeof(tabTiles_t));
    tabSolution_t *tabS=malloc(sizeof(tabSolution_t));

    acquisizioneTiles(tabT);
    acquisizioneBoard(tabB, tabT);
    allocoSol(tabS, tabT->numTiles, tabB->nr, tabB->nc);
    tabS->tabT->numTiles=tabT->numTiles;
    tabS->tabB->nr=tabB->nr;
    tabS->tabB->nc=tabB->nc;
    tabS->val=-1;
    copiaSol(tabS, tabB, tabT);     //come se la inizializzassi hai valori iniziali
    disp_rip(0, tabT, tabB, tabS, tabT->numTiles, (tabB->nr * tabB->nc));
    stampaBoard(tabS->tabB);
    printf("Valore soluzione massima: %d", tabS->val);
    checkSol(tabS->tabB);

    return 0;
}

void allocoSol(tabSolution_t *tabS, int numTiles, int nr, int nc) {
    tabS->tabB=malloc(sizeof(tabBoard_t));
    tabS->tabT=malloc(sizeof(tabTiles_t));
    tabS->tabT->tiles=malloc(numTiles*sizeof(tile_t));
    tabS->tabB->board=malloc(nr*sizeof(tile_t**));
    for (int i=0; i<nr; i++)
        tabS->tabB->board[i]=malloc(nc*sizeof(tile_t*));
}
void acquisizioneTiles(tabTiles_t *tabT) {
    FILE *ft=fopen("tiles.txt", "r");
    char str[1000];
    fscanf(ft,"%d\n", &tabT->numTiles);
    tabT->tiles=malloc(tabT->numTiles*sizeof(tile_t));
    for (int i=0; i<tabT->numTiles; i++) {
        tabT->tiles[i].n_tile=i;
        tabT->tiles[i].orientamento=-1;
        fscanf(ft, "%c %d %c %d\n", &tabT->tiles[i].c0, &tabT->tiles[i].v0, &tabT->tiles[i].c1, &tabT->tiles[i].v1);
    }
    fclose(ft);
    return;
}
void acquisizioneBoard(tabBoard_t *tabB, tabTiles_t *tabT) {
    int t, o;
    FILE *fb=fopen("board.txt", "r");
    fscanf(fb, "%d %d", &tabB->nr, &tabB->nc);
    tabB->board=malloc((tabB->nr)*sizeof(tile_t**));
    for (int i=0; i<tabB->nr; i++)
        tabB->board[i]=malloc((tabB->nc)* sizeof(tile_t*));
    for (int i=0; i<tabB->nr; i++) {
        for (int j=0; j<tabB->nc; j++) {
            fscanf(fb, "%d/%d", &t, &o);
            if (t!=-1) {
                tabB->board[i][j]=&(tabT->tiles[t]);
                tabT->tiles[t].orientamento=o;
            } else {
                tabB->board[i][j]=NULL;
            }
        }
    }
    fclose(fb);
    return;
}
void stampaTiles(tabTiles_t *tabT) {
    for (int i=0; i<tabT->numTiles; i++)
        printf("%c %d %c %d\n", tabT->tiles[i].c0, tabT->tiles[i].v0, tabT->tiles[i].c1, tabT->tiles[i].v1);
}
void stampaBoard(tabBoard_t *tabB) {
    for (int i=0; i<tabB->nr; i++) {
        for (int j=0; j<tabB->nc; j++) {
            if (tabB->board[i][j]!=NULL)
                printf("%d/%d ", tabB->board[i][j]->n_tile, tabB->board[i][j]->orientamento);
            else
                printf("-1/-1 ");
        }
        printf("\n");
    }
    return;
}
void disp_rip(int pos, tabTiles_t *tabT, tabBoard_t *tabB, tabSolution_t *tabS, int n, int k) {
    int i, r, c, val;
    if (pos>=k) {
        /*
         * Inserire funzione per trovare il valore massimo
         *      salvare in tabS se di valore massimo
         */
        val=checkSol(tabB);
        if (val>tabS->val) {
            copiaSol(tabS, tabB, tabT);
            tabS->val=val;
        }
        return;
    }
    r=pos/(tabB->nr);
    c=pos%(tabB->nr);
    if (tabB->board[r][c]==NULL){
        for (i=0; i<n; i++) {
            if (tabT->tiles[i].orientamento==-1) {
                tabB->board[r][c] = &(tabT->tiles[i]);
                tabT->tiles[i].orientamento = 0;
                disp_rip(pos + 1, tabT, tabB, tabS, n, k);
                tabT->tiles[i].orientamento = 1;
                disp_rip(pos + 1, tabT, tabB, tabS, n, k);
                tabT->tiles[i].orientamento = -1;
                tabB->board[r][c] = NULL;
            }
        }
    } else {
        disp_rip(pos+1, tabT, tabB, tabS, n, k);
    }
    return;
}
void copiaSol(tabSolution_t *tabS, tabBoard_t *tabB, tabTiles_t *tabT) {
    int tmp;
    for (int i=0; i<tabT->numTiles; i++)
        tabS->tabT->tiles[i]=tabT->tiles[i];
    for (int i=0; i<tabS->tabB->nr; i++) {
        for (int j=0; j<tabS->tabB->nc; j++) {
            if (tabB->board[i][j]!=NULL) {
                tmp = tabB->board[i][j]->n_tile;
                tabS->tabB->board[i][j]=&(tabS->tabT->tiles[tmp]);
            } else tabS->tabB->board[i][j]=NULL;
        }
    }
}
int checkSol(tabBoard_t *tabB) {
    int i, j;
    int flag=1;
    int val=0;
    int tmp=0;
    int valR=0;
    int valC=0;
    char cc0, cc1;
    //valore righe
    for (i=0; i<tabB->nr; i++) {
        for (j=0; j<tabB->nc-1; j++) {
            if(tabB->board[i][j]->orientamento==0){
                cc0=tabB->board[i][j]->c0;
                tmp+=tabB->board[i][j]->v0;
            }
            else {
                cc0=tabB->board[i][j]->c1;
                tmp+=tabB->board[i][j]->v1;
            }
            if(tabB->board[i][j+1]->orientamento==0){
                cc1=tabB->board[i][j+1]->c0;
            }
            else {
                cc1=tabB->board[i][j+1]->c1;
            }
            if (cc0!=cc1) {
                flag=0;
                break;
            } else {
                valR+=tmp;
                tmp=0;
            }
        }
        if (flag==0) {
            tmp=0;
            valR=0;
        } else {
            valR+=(tabB->board[i][j]->orientamento==0)?tabB->board[i][j]->v0:tabB->board[i][j]->v1;
            val+=valR;
            valR=0;
        }
        flag=1;
    }
    flag=1;
    tmp=0;
    //valore colonne
    for (j=0; j<tabB->nc; j++) {
        for (i=0; i<tabB->nr-1; i++) {
            if(tabB->board[i][j]->orientamento==0){
                cc0=tabB->board[i][j]->c1;
                tmp+=tabB->board[i][j]->v1;
            }
            else {
                cc0=tabB->board[i][j]->c0;
                tmp+=tabB->board[i][j]->v0;
            }
            if(tabB->board[i+1][j]->orientamento==0){
                cc1=tabB->board[i+1][j]->c1;
            }
            else {
                cc1=tabB->board[i+1][j]->c0;
            }
            if (cc0!=cc1) {
                flag=0;
                break;
            } else {
                valC+=tmp;
                tmp=0;
            }
        }
        if (flag==0) {
            tmp=0;
            valC=0;
        } else {
            valC+=(tabB->board[i][j]->orientamento==0)?tabB->board[i][j]->v1:tabB->board[i][j]->v0;
            val+=valC;
            valC=0;
        }
        flag=1;
    }
    return val;
}