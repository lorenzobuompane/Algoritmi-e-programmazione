#include <stdio.h>
#include <string.h>
#include "collezioneTitoli.h"

typedef enum {
    r_titolo,
    q_data,
    q_date,
    q_all,
    b_soglia,
    p_list
}comando_t;

comando_t leggiComando(char comando[]);
void swapDate(data_t *d1, data_t *d2);
void stampaMenu();

int main() {
    char comando[MAXC];
    char str[MAXC];
    data_t d1, d2;
    int soglia;
    comando_t cmd;
    collTitle_t c = LISTinit();
    c = TITLEfilesadd(c, "F1.txt", "F2.txt", "F3.txt");
    stampaMenu();
    while (1) {
        printf("Inserire comando:\n");
        scanf("%s", comando);
        cmd=leggiComando(comando);
        switch (cmd) {
            case r_titolo:
                printf("Inserisci titolo da cercare:\n");
                scanf("%s", str);
                ricercaTitolo(c, str);
                break;
            case q_data:
                printf("Inserisci titolo da cercare:\n");
                scanf("%s", str);
                printf("Inserisci data: <gg mm aaaa>\n");
                scanf("%d %d %d", &d1.gg, &d1.mm, &d1.aa);
                ricercaQuotazione(c, str, d1);
                break;
            case q_date:
                printf("Inserisci titolo da cercare:\n");
                scanf("%s", str);
                printf("Inserisci data 1: <gg mm aaaa>\n");
                scanf("%d %d %d", &d1.gg, &d1.mm, &d1.aa);
                printf("Inserisci data 2: <gg mm aaaa>\n");
                scanf("%d %d %d", &d2.gg, &d2.mm, &d2.aa);
                if (DATEcmp(d1, d2)<0)
                    swapDate(&d1, &d2);
                ricercaQuotazioniData(c, str, d1, d2);
                break;
            case q_all:
                printf("Inserisci titolo da cercare:\n");
                scanf("%s", str);
                ricercaQuotazioniALL(c, str);
                break;
            case b_soglia:
                printf("Inserisci titolo da cercare:\n");
                scanf("%s", str);
                printf("Inserisci soglia:\n");
                scanf("%d", &soglia);
                bilanciamento(c, str, soglia);
                break;
            case p_list:
                stampaLista(c);
                break;
            default:
                return 0;
        }

    }
}

void stampaMenu() {
    printf("\n\nCOMANDI DISPONIBILI\n"
           "titolo : ricerca titolo\n"
           "data : ricerca quotazione nella data data\n"
           "date : ricerca quotazione massima e minima tra due date\n"
           "all : ricerca quotazione massima eminima nell'intero intervallo\n"
           "soglia :  bilanciamento con soglia\n"
           "list : stampa lista\n"
           "fine\n");
}

comando_t leggiComando(char comando[]) {
    if (strcmp(comando, "titolo")==0)
        return r_titolo;
    if (strcmp(comando, "data")==0)
        return q_data;
    if (strcmp(comando, "date")==0)
        return q_date;
    if (strcmp(comando, "all")==0)
        return q_all;
    if (strcmp(comando, "soglia")==0)
        return b_soglia;
    if (strcmp(comando, "list")==0)
        return p_list;
}

void swapDate(data_t *d1, data_t *d2) {
    data_t tmp;
    tmp = *d1;
    *d1=*d2;
    *d2=tmp;
}