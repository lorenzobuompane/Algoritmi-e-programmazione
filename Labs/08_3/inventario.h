#ifndef INC_08_3_INVENTARIO_H
#define INC_08_3_INVENTARIO_H

#define STR 51

//STATISTICHE
typedef struct Statistiche{
    int hp;
    int mp;
    int atk;
    int def;
    int mag;
    int spr;
} stat_t;

//INVENTARIO
typedef struct Inventario {
    char nome[STR];
    char tipologia[STR];
    stat_t stat;
} inv_t;
typedef struct Tab_Inv {
    inv_t *vettInv;
    int nInv;
    int maxInv;
} tabInv_t;

void acquisizioneInv(tabInv_t *tabInv);
void stampaVettoreInv(tabInv_t *tabInv);
void stampaOggetto(inv_t inventario);

#endif //INC_08_3_INVENTARIO_H
