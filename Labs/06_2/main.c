#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRINGHE 51

typedef struct Data {
    int gg;
    int mm;
    int aa;
} Data;

typedef struct node *link;

typedef struct Individuo {
    char codice[MAX_STRINGHE];
    char nome[MAX_STRINGHE];
    char cognome[MAX_STRINGHE];
    Data dataNascita;
    char via[MAX_STRINGHE];
    char citta[MAX_STRINGHE];
    int cap;
} Individuo;

struct node {
    Individuo human;
    link next;
};

typedef enum {
    a_tastiera,
    a_file,
    r_codice,
    c_codice,
    c_data,
    s_terminal,
    s_file,
    f_end,
    e_err
}comando_c;

link acquisizioneFile(link anagrafica);
link acquisizioneTastiera(link anagrafica);
link SortListIns(link h, Individuo val);
link newNode(Individuo val, link next);
int confrontaData (Data A, Data B);
void stampaLista(link anagrafica);
void stampaListasuFile(link anagrafica);
void stampaIndividuo(Individuo x);
void stampaListaComandi();
comando_c leggiComando(char comando[MAX_STRINGHE]);
link ricercaIndividuo(link anagrafica);
Individuo listExtrKeyP(link *hp, char codice[MAX_STRINGHE]);
link cancellaDate(link h, Data d1, Data d2);
link iterazione(link h, Data d);
void stampaListasuFile(link anagrafica);
void switchData(Data *d1, Data *d2);


int main() {
    link anagrafica = NULL;
    int continua=1;
    char comando[MAX_STRINGHE];
    comando_c comandoC;
    Individuo tmp;
    char codice[MAX_STRINGHE];
    Data d1, d2;

    stampaListaComandi();
    while (continua) {
        scanf("%s", comando);
        comandoC=leggiComando(comando);
        switch (comandoC) {
            case a_tastiera:
                anagrafica=acquisizioneTastiera(anagrafica);
                printf("ACQUISIZIONE COMPLETATA\n");
                break;
            case a_file:
                anagrafica=acquisizioneFile(anagrafica);
                printf("ACQUISIZIONE COMPLETATA\n");
                break;
            case r_codice:
                ricercaIndividuo(anagrafica);
                break;
            case c_codice:
                printf("Inserire codice:\n");
                scanf("%s", codice);
                tmp=listExtrKeyP(&anagrafica, codice);
                if (strcmp(tmp.codice, "NULL")!=0) {
                    stampaIndividuo(tmp);
                    printf("ELEMENTO ESTRATTO E CANCELLATO\n");
                }
                else printf("CODICE NON TROVATO\n");
                break;
            case c_data:

                printf("Inserire prima data intervallo: (gg mm aa)\n");
                scanf("%d %d %d", &d1.gg, &d1.mm, &d1.aa);
                printf("Inserire seconda data intervallo: (gg mm aa)\n");
                scanf("%d %d %d", &d2.gg, &d2.mm, &d2.aa);
                anagrafica=cancellaDate(anagrafica, d1, d2);
                printf("DATE ELIMINATE se presenti\n");
                break;
            case s_terminal:
                stampaLista(anagrafica);
                break;
            case s_file:
                stampaListasuFile(anagrafica);
                break;
            case f_end:
                continua=0;
                break;
            default:
                printf("Errore lettura comando!\n");
                break;
        }
    }
    return 0;
}

link acquisizioneTastiera(link anagrafica){
    Individuo val;
    printf("Inserisci codice:\n");
    scanf("%s", val.codice);
    printf("Inserisci nome:\n");
    scanf("%s", val.nome);
    printf("Inserisci cognome:\n");
    scanf("%s", val.cognome);
    printf("Inserisci data di nascita in formato gg mm aaaa:\n");
    scanf("%d %d %d", &val.dataNascita.gg, &val.dataNascita.mm, &val.dataNascita.aa);
    printf("Inserisci via:\n");
    scanf("%s", val.via);
    printf("Inserisci citta':\n");
    scanf("%s", val.citta);
    printf("Inserisci cap:\n");
    scanf("%d", &val.cap);
    anagrafica=SortListIns(anagrafica, val);
    return anagrafica;
}
comando_c leggiComando(char comando[MAX_STRINGHE]) {
    if (strcmp(comando, "a_tastiera")==0)
        return a_tastiera;
    if (strcmp(comando, "a_file")==0)
        return a_file;
    if (strcmp(comando, "r_codice")==0)
        return r_codice;
    if (strcmp(comando, "c_codice")==0)
        return c_codice;
    if (strcmp(comando, "c_data")==0)
        return c_data;
    if (strcmp(comando, "s_terminal")==0)
        return s_terminal;
    if (strcmp(comando, "s_file")==0)
        return s_file;
    if (strcmp(comando, "f_end")==0)
        return f_end;
    return e_err;
}
link newNode(Individuo val, link next) {
    link x = malloc(sizeof(struct node));
    if (x==NULL)
        return NULL;
    else {
        x->human=val;
        x->next=next;
    }
    return x;
}
link SortListIns(link h, Individuo val) {
    link x, p;
    if (h==NULL || confrontaData(val.dataNascita, h->human.dataNascita))
        return newNode(val, h);

    for (
            x=h->next, p=h;
            x!=NULL && confrontaData(x->human.dataNascita, val.dataNascita);
            p=x, x=x->next
        );

    p->next=newNode(val, x);
    return h;
}
link acquisizioneFile(link anagrafica) {
    Individuo tmp;

    char nomefile[MAX_STRINGHE];
    printf("Inserisci nome file:\n");
    scanf("%s", nomefile);

    FILE *fp = fopen(nomefile, "r");

    //FILE *fp = fopen("anagrafica.txt", "r");

    if (fp==NULL)
        printf("ERRORE LETTURA FILE\n");

    while (fscanf(fp,"%s %s %s %d/%d/%d %s %s %d", tmp.codice, tmp.nome, tmp.cognome, &tmp.dataNascita.gg, &tmp.dataNascita.mm, &tmp.dataNascita.aa, tmp.via, tmp.citta, &tmp.cap)==9) {
        anagrafica=SortListIns(anagrafica, tmp);
    }
    fclose(fp);
    return anagrafica;
}
int confrontaData (Data A, Data B) {
    /*
 * return 1 se data A > B, ovvero se A più giovane
 * return 0 se data A < B, ovvero se A più vecchio
 */
    /*
    int swap=0;
    if (A.aa>B.aa)
        swap=1;
    else if (A.aa==B.aa) {
        if (A.mm>B.mm)
            swap=1;
        else if (A.mm==B.mm) {
            if (A.gg>B.gg)
                swap=1;
        }
    }
    return swap;
     */
    if (A.aa>B.aa) return 1;
    if (A.aa==B.aa && A.mm>B.mm) return 1;
    if (A.aa==B.aa && A.mm==B.mm && A.gg>B.gg) return 1;
    return 0;
}
void stampaLista(link anagrafica) {
    link x;
    for (x=anagrafica; x!=NULL; x=x->next)
        stampaIndividuo(x->human);
}
void stampaListasuFile(link anagrafica) {
    link x;
    FILE *fo=fopen("out.txt", "w");
    for (x=anagrafica; x!=NULL; x=x->next)
        fprintf(fo, "%s %s %s %d/%d/%d %s %s %d\n", x->human.codice, x->human.nome, x->human.cognome, x->human.dataNascita.gg, x->human.dataNascita.mm, x->human.dataNascita.aa, x->human.via, x->human.citta, x->human.cap);
    fclose(fo);
}
void stampaIndividuo(Individuo x){
    printf("%s %s %s %d/%d/%d %s %s %d\n", x.codice, x.nome, x.cognome, x.dataNascita.gg, x.dataNascita.mm, x.dataNascita.aa, x.via, x.citta, x.cap);
}
void stampaListaComandi() {
    printf("\nLISTA COMANDI:"
           "\n\ta_tastiera -> acquisizione da tastiera"
           "\n\ta_file -> acuisizione da file"
           "\n\tr_codice -> ricerca per codice"
           "\n\tc_codice -> cancella per codice"
           "\n\tc_data -> cancella tra le due date"
           "\n\ts_terminal -> stampa lista su terminale"
           "\n\ts_file -> stampa lista su file"
           "\n\tf_end -> FINE"
           "\n");
}
link ricercaIndividuo(link anagrafica) {
    link x;
    char codice[MAX_STRINGHE];
    printf("Inserisci codice per la ricerca: ");
    scanf("%s", codice);
    for (x=anagrafica; x->next!=NULL; x=x->next)
        if (strcmp(x->human.codice, codice)==0) {
            stampaIndividuo(x->human);
            return x;
        }
    printf("NESSUN INDIVIDUO TROVATO CON CODICE %s", codice);
}
Individuo listExtrKeyP(link *hp, char codice[MAX_STRINGHE]) {
    link *xp, t;
    Individuo i;
    strcpy(i.codice, "NULL");
    for (xp=hp; (*xp)!=NULL; xp=&((*xp)->next)) {
        if (strcmp((*xp)->human.codice, codice)==0) {
            t=*xp;
            *xp=(*xp)->next;
            i=t->human;
            free(t);
            break;
        }
    }
    return i;
}
link cancellaDate(link h, Data d1, Data d2) {
    link delete;
    Individuo tmp;
    if (confrontaData(d1, d2)==0)
        switchData(&d1, &d2);
    printf("piccolo %d %d %d\ngrande %d %d %d\n", d1.gg, d1.mm, d1.aa, d2.gg, d2.mm, d2.aa);
    delete=iterazione(h, d1);
    if (delete!=NULL) {
        /*
        for (; delete!=NULL && confrontaData(delete->human.dataNascita, d2)==1; delete=delete->next) {
            tmp=listExtrKeyP(&h, delete->human.codice);
            printf("CANCELLO ->\t");
            stampaIndividuo(tmp);
        }
         */
        while (delete!=NULL && confrontaData(delete->human.dataNascita, d2)==1) {
            tmp=listExtrKeyP(&h, delete->human.codice);
            printf("CANCELLO ->\t");
            stampaIndividuo(tmp);
            delete=delete->next;
        }
    }
    else
        printf("Nessun individuo da cancellare\n");
    return h;
}
link iterazione(link h, Data d) {
    link x;
    if (h==NULL) return NULL;
    for (x=h; x->next!=NULL && confrontaData(x->human.dataNascita, d)==1; x=x->next);
    /*
    printf("---\n");
    stampaIndividuo(x->human);
    printf("---\n");
     */
    if (x->next==NULL && confrontaData(x->human.dataNascita, d)==1) return NULL;
    else return x;
}
void switchData(Data *d1, Data *d2) {
    Data tmp;
    tmp=*d1;
    *d1=*d2;
    *d2=tmp;
}
