#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define COD 7
#define STR 51
#define MAX_ELEMENT 8

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

//EQUIPAGGIAMENTO
typedef struct Tab_Equip {
    int inUso;
    inv_t *vettEq[MAX_ELEMENT];
} tabEquip_t;

//PERSONAGGIO
typedef struct Personaggio {
    char codice[COD];
    char nome[STR];
    char classe[STR];
    tabEquip_t equip;
    stat_t stat;
} pg_t;
typedef struct nodePg_t *link;
struct nodePg_t {
    pg_t pg;
    link next;
};
typedef struct Tab_pg {
    int nPg;
    link headPg;
    link tailPg;
} tabPg_t;

//FUNZIONI
void acquisizionePg(tabPg_t *tabPg);
link newNode(pg_t pg, link next);
void SortListIns(tabPg_t *h, pg_t pg);
void SortListDel(tabPg_t *h, char codice[COD]);
void stampaListaPg(tabPg_t *tabPg);
void stampaPg(pg_t pg);
void addPg(tabPg_t *tabPg);
void deletePg(tabPg_t *tabPg);
void addEquip(tabPg_t *tabPg, tabInv_t *tabInv);
void deleteEquip(tabPg_t *tabPg, tabInv_t *tabInv);
void calcolaStatistiche(tabPg_t *tabPg);


void acquisizioneInv(tabInv_t *tabInv);
void stampaVettoreInv(tabInv_t *tabInv);
void stampaOggetto(inv_t inventario);


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

void acquisizionePg(tabPg_t *tabPg) {
    FILE *fp=fopen("pg.txt", "r");
    char str[4*STR];
    pg_t tmp;
    link x;
    int i=0;
    while (fgets(str, 4*STR, fp)!=NULL) {
        sscanf(str, "%s %s %s %d %d %d %d %d %d", tmp.codice, tmp.nome, tmp.classe, &tmp.stat.hp, &tmp.stat.mp, &tmp.stat.atk, &tmp.stat.def, &tmp.stat.mag, &tmp.stat.spr);
        tmp.equip.inUso=0;
        SortListIns(tabPg, tmp);
    }
    for (x=tabPg->headPg; x->next!=NULL; x=x->next)
        i++;
    tabPg->nPg=i;
    fclose(fp);
    return;
}
link newNode(pg_t pg, link next) {
    link x = malloc(sizeof(struct nodePg_t));
    if (x==NULL)
        return NULL;
    else {
        x->pg=pg;
        x->next=next;
    }
    return x;
}
void SortListIns(tabPg_t *h, pg_t pg) {
    link x, p;
    if (h->headPg==NULL && h->tailPg==NULL) {               //LISTA VUOTA
        h->headPg=newNode(pg, h->headPg);
        h->tailPg=h->headPg;
        return;
    }
    if (strcmp(h->headPg->pg.codice, pg.codice)>0) {      //INSERIMENTO IN TESTA
        h->headPg = newNode(pg, h->headPg);
        return;
    }
    for (x=h->headPg->next, p=h->headPg; x!=NULL && strcmp(pg.codice, x->pg.codice)>0; p=x, x=x->next);
    if (x==NULL) {                                      //INSERIMENTO IN CODA
        p->next = newNode(pg, x);
        h->tailPg=p->next;
    } else p->next = newNode(pg, x);                    //INSERIMENTO IN MEZZO ALLA LISTA
    return;
}
void SortListDel(tabPg_t *h, char codice[COD]) {
    link x, p;


    if (strcmp(h->headPg->pg.codice, codice)==0) {      //CANCELLAZIONE IN TESTA
        x=h->headPg;
        h->headPg=x->next;
        if (x->next==NULL)                              //UNICO ELEMENTO
            h->tailPg=NULL;
        free(x);
        printf("ELIMINAZIONE COMPLETATA\n");
        return;
    }
    for (x=h->headPg->next, p=h->headPg; x!=NULL; p=x, x=x->next){
        if (strcmp(codice, x->pg.codice)==0){
            p->next=x->next;
            if (x->next==NULL)                          //ULTIMO ELEMENTO
                h->tailPg=p;                            //AGGIORNO CODA
            free(x);
            printf("ELIMINAZIONE COMPLETATA\n");
            return;
        }
    }

    printf("CODICE NON VALIDO\n");
}
void stampaListaPg(tabPg_t *tabPg) {
    link x;
    for (x=tabPg->headPg; x!=NULL; x=x->next)
        stampaPg(x->pg);
}
void stampaPg(pg_t pg) {
    printf("%s %s %s %d %d %d %d %d %d\n", pg.codice, pg.nome, pg.classe, pg.stat.hp, pg.stat.mp, pg.stat.atk, pg.stat.def, pg.stat.mag, pg.stat.spr);
}
void addPg(tabPg_t *tabPg) {
    pg_t tmp;
    link x;
    int prec=(tabPg->nPg);
    int i=0;
    printf("Inserisci:\n"
           "codice nome classe hp mp atk def mag spr\n");
    scanf("%s %s %s %d %d %d %d %d %d", tmp.codice, tmp.nome, tmp.classe, &tmp.stat.hp, &tmp.stat.mp, &tmp.stat.atk, &tmp.stat.def, &tmp.stat.mag, &tmp.stat.spr);
    tmp.equip.inUso=0;
    for (x=tabPg->headPg; x->next!=NULL; x=x->next) {
        if (strcmp(x->pg.codice, tmp.codice)==0) {
            printf("PERSONAGGIO ESISTENTE!\n");
            return;
        }
    }
    SortListIns(tabPg, tmp);
    for (x=tabPg->headPg; x->next!=NULL; x=x->next)
        i++;
    if (i==prec+1) {                                //CONTROLLO CHE L'AGGIUNTA SIA AVVENUTA CON SUCCESSO
        tabPg->nPg=i;
        printf("AGGIUNTA PERSONAGGIO AVVENUTA CON SUCCESSO!\n");
    } else printf("ERRORE AGGIUNTA PERSONAGGIO\n");
    return;
}
void deletePg(tabPg_t *tabPg) {
    char codice[COD];
    if (tabPg->headPg==NULL && tabPg->tailPg==NULL){            //LISTA VUOTA
        printf("LISTA VUOTA\n");
        return;
    }
    stampaListaPg(tabPg);
    printf("\nInserisci codice da eliminare:\n");
    scanf("%s", codice);
    SortListDel(tabPg, codice);
    return;
}
void addEquip(tabPg_t *tabPg, tabInv_t *tabInv){
    char codice[COD];
    char nome[STR];
    link x;
    stampaListaPg(tabPg);
    printf("Inserisci codice personaggio:\n");
    scanf("%s", codice);
    for (x=tabPg->headPg; x!=NULL; x=x->next) {
        if (strcmp(x->pg.codice, codice)==0)
            break;                                                              //x PERSONAGGIO SCELTO
    }
    if (x==NULL) {                                      //PERSONAGGIO INESISTENTE
        printf("Personaggio non esistente!\n");
        return;
    }
    if (x->pg.equip.inUso>=MAX_ELEMENT) {
        printf("Personaggio equipaggiato al massimo!\n");               //VETTORE EQUIPAGGIAMENTO PIENO
        return;
    }
    printf("\n");
    stampaVettoreInv(tabInv);
    printf("Inserire nome oggetto nell'inventario\n");
    scanf("%s", nome);                                                  //ogg INVENTARIO SCELTO
    for (int i=0; i<tabInv->nInv; i++) {
        if (strcmp(tabInv->vettInv[i].nome, nome)==0) {
            x->pg.equip.vettEq[x->pg.equip.inUso]=&(tabInv->vettInv[i]);
            (x->pg.equip.inUso)++;
            return;
        }
    }
    printf("Oggetto non esistente!\n");                                 //OGGETTO INESISTENTE
    return;
}
void deleteEquip(tabPg_t *tabPg, tabInv_t *tabInv) {
    char codice[COD];
    char nome[STR];
    link x;
    stampaListaPg(tabPg);
    printf("Inserisci codice personaggio:\n");
    scanf("%s", codice);
    for (x=tabPg->headPg; x!=NULL; x=x->next) {
        if (strcmp(x->pg.codice, codice)==0)
            break;                                                              //x PERSONAGGIO SCELTO
    }
    if (x==NULL) {                                      //PERSONAGGIO INESISTENTE
        printf("Personaggio non esistente!\n");
        return;
    }
    if (x->pg.equip.inUso==0) {                                                 //VETTORE EQUIPAGGIAMENTO VUOTO
        printf("Vettore equipaggiamento vuoto!\n");
        return;
    }
    printf("\n");
    for (int i=0; i<x->pg.equip.inUso; i++)
        stampaOggetto(*(x->pg.equip.vettEq[i]));
    printf("Inserire nome oggetto nell'inventario\n");
    scanf("%s", nome);                                                  //ogg INVENTARIO SCELTO
    for (int i=0; i<x->pg.equip.inUso; i++) {
        if (strcmp(x->pg.equip.vettEq[i]->nome, nome)){
            x->pg.equip.vettEq[i]=NULL;
            (x->pg.equip.inUso)--;
            return;
        }
    }
    printf("Oggetto non presente nel vettore equipaggiamento!\n");      //ogg NON PRESENTE IN VETTORE EQUIPAGGIAMENTO
}
void calcolaStatistiche(tabPg_t *tabPg) {
    stat_t tmp;
    link x;
    char codice[COD];
    stampaListaPg(tabPg);
    printf("Inserisci codice personaggio:\n");
    scanf("%s", codice);
    for (x=tabPg->headPg; x!=NULL; x=x->next) {
        if (strcmp(x->pg.codice, codice)==0)
            break;                                                              //x PERSONAGGIO SCELTO
    }
    if (x==NULL) {                                      //PERSONAGGIO INESISTENTE
        printf("Personaggio non esistente!\n");
        return;
    }
    //STATISTICHE DEL PERSONAGGIO
    tmp.hp=x->pg.stat.hp;
    tmp.mp=x->pg.stat.mp;
    tmp.atk=x->pg.stat.atk;
    tmp.def=x->pg.stat.def;
    tmp.mag=x->pg.stat.mag;
    tmp.spr=x->pg.stat.spr;
    //AGGIUNGO STATISTICHE EQUIPAGGIAMENTI
    for (int i=0; i<x->pg.equip.inUso; i++) {
        tmp.hp=tmp.hp+x->pg.equip.vettEq[i]->stat.hp;
        tmp.mp=tmp.mp+x->pg.equip.vettEq[i]->stat.mp;
        tmp.atk=tmp.atk+x->pg.equip.vettEq[i]->stat.atk;
        tmp.def=tmp.def+x->pg.equip.vettEq[i]->stat.def;
        tmp.mag=tmp.mag+x->pg.equip.vettEq[i]->stat.mag;
        tmp.spr=tmp.spr+x->pg.equip.vettEq[i]->stat.spr;
    }
    if (tmp.hp<1)
        tmp.hp=1;
    if (tmp.mp<1)
        tmp.mp=1;
    if (tmp.atk<1)
        tmp.atk=1;
    if (tmp.def<1)
        tmp.def=1;
    if (tmp.mag<1)
        tmp.mag=1;
    if (tmp.spr<1)
        tmp.spr=1;
    printf("\nStatistiche giocatore %s [%d oggetti equipaggiamento/i]:\n", x->pg.codice, x->pg.equip.inUso);
    printf("\thp: %d\n"
           "\tmp: %d\n"
           "\tatk: %d\n"
           "\tdef: %d\n"
           "\tmag: %d\n"
           "\tspr: %d\n", tmp.hp, tmp.mp, tmp.atk, tmp.def, tmp.mag, tmp.spr);
}


void acquisizioneInv(tabInv_t *tabInv) {
    FILE *fp=fopen("inventario.txt", "r");
    fscanf(fp, "%d", &tabInv->nInv);
    tabInv->maxInv=tabInv->nInv;
    tabInv->vettInv=malloc((tabInv->nInv)*sizeof(inv_t));
    for (int i=0; i<tabInv->nInv; i++)
        fscanf(fp, "%s %s %d %d %d %d %d %d", tabInv->vettInv[i].nome, tabInv->vettInv[i].tipologia, &tabInv->vettInv[i].stat.hp, &tabInv->vettInv[i].stat.mp, &tabInv->vettInv[i].stat.atk, &tabInv->vettInv[i].stat.def, &tabInv->vettInv[i].stat.mag, &tabInv->vettInv[i].stat.spr);
    fclose(fp);
    return;
}
void stampaVettoreInv(tabInv_t *tabInv) {
    for (int i=0; i<tabInv->nInv; i++)
        stampaOggetto(tabInv->vettInv[i]);
}
void stampaOggetto(inv_t inventario) {
    printf("%s %s %d %d %d %d %d %d\n", inventario.nome, inventario.tipologia, inventario.stat.hp, inventario.stat.mp, inventario.stat.atk, inventario.stat.def, inventario.stat.mag, inventario.stat.spr);
}