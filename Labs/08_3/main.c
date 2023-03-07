#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pg.h"

#define STR 51

typedef enum {
    newPg,
    delPg,
    newEquip,
    delEquip,
    stat,
    stampaLista,
    stampaVettore,
    fine,
    err
} comando_e;

void stampaComandi();
comando_e leggiComando (char comando[STR]);

int main() {
    tabPg_t *tabPg = malloc(sizeof(tabPg_t));
    tabPg->headPg=NULL;
    tabPg->tailPg=NULL;
    tabInv_t *tabInv = malloc(sizeof(tabInv_t));
    int continua=1;
    char comando[STR];
    comando_e cmd;

    acquisizionePg(tabPg);
    acquisizioneInv(tabInv);

    stampaComandi();

    while (continua) {
        printf("Inserisci comando:\n");
        scanf("%s", comando);
        cmd=leggiComando(comando);
        switch (cmd) {
            case newPg:
                addPg(tabPg);
                break;
            case delPg:
                deletePg(tabPg);
                break;
            case newEquip:
                addEquip(tabPg, tabInv);
                break;
            case delEquip:
                deleteEquip(tabPg, tabInv);
                break;
            case stat:
                calcolaStatistiche(tabPg);
                break;
            case stampaLista:
                stampaListaPg(tabPg);
                break;
            case stampaVettore:
                stampaVettoreInv(tabInv);
                break;
            case fine:
                continua=0;
                break;
            default:
                printf("ERRORE ACQUISIZIONE COMANDO\n");
        }
    }


    return 0;
}

void stampaComandi() {
    printf("Lista comandi:\n"
           "\tnewPg: aggiungi nuovo personaggio\n"
           "\tdelPg: elimina personaggio\n"
           "\tnewEquip: aggiungi oggetto all'equipaggiamento del parsonaggio\n"
           "\tdelEquip: elimina oggetto dall'equipaggiamento del parsonaggio\n"
           "\tstat: calcola statistiche personaggio\n"
           "\tstampaLista: stampa lista personaggi\n"
           "\tstampaVettore: stampa vettore inventario\n"
           "\tfine: termina\n");
}
comando_e leggiComando (char comando[STR]) {
    if (strcmp(comando, "newPg")==0)
        return newPg;
    if (strcmp(comando, "delPg")==0)
        return delPg;
    if (strcmp(comando, "newEquip")==0)
        return newEquip;
    if (strcmp(comando, "delEquip")==0)
        return delEquip;
    if (strcmp(comando, "stat")==0)
        return stat;
    if (strcmp(comando, "stampaLista")==0)
        return stampaLista;
    if (strcmp(comando, "stampaVettore")==0)
        return stampaVettore;
    if (strcmp(comando, "fine")==0)
        return fine;

    return err;
}