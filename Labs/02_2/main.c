#include <stdio.h>
#include <string.h>

#define MAX_STRINGHE 31
#define MAX_TRATTE 1001

typedef struct Orario {
    int secondi;
    int minuti;
    int ora;
} Orario;

typedef struct Dt {
    int anno;
    int mese;
    int giorno;
} Dt;

typedef struct Tratta {
    char codicetratta[MAX_STRINGHE];
    char partenza[MAX_STRINGHE];
    char destinazione[MAX_STRINGHE];
    Dt d;
    Orario o_partenza;
    Orario o_arrivo;
    int ritardo;
} Tratta;

typedef enum {
    r_date,
    r_partenza,
    r_capolinea,
    r_ritardo,
    r_ritardo_tot,
    r_fine,
    r_err
} comando_e;

comando_e leggiComando (char inserimento[100]);
int selezionaDati (Tratta t[MAX_TRATTE], int n, comando_e r, char str[100]);
int checkData(Tratta tratta, char opz1[MAX_STRINGHE], char opz2[MAX_STRINGHE]);
void stampaTratta(Tratta t);

int main()
{
    int n_tratte;
    Tratta file_log[MAX_TRATTE];
    char inserimento[100];
    int continua=1;

    //ACQUISIZIONE FILE
    FILE *fp=fopen("corse.txt", "r");
    if (fp==NULL)
        return -1;
    //LETTURA FILE
    fscanf(fp, "%d", &n_tratte);
    for (int i=0; i<n_tratte; i++) {
        fscanf(fp, "%s %s %s %d/%d/%d %d:%d:%d %d:%d:%d %d", file_log[i].codicetratta, file_log[i].partenza, file_log[i].destinazione, &file_log[i].d.anno, &file_log[i].d.giorno, &file_log[i].d.mese, &file_log[i].o_partenza.ora, &file_log[i].o_partenza.minuti, &file_log[i].o_partenza.secondi, &file_log[i].o_arrivo.ora, &file_log[i].o_arrivo.minuti, &file_log[i].o_arrivo.secondi, &file_log[i].ritardo);
    }

    while (continua) {
        //ACQUISIZIONE STRINGA COMANDI
        printf("\n\nElenco comandi:\n");
        printf("date: inserire due date nel formaro aa/mm/gg\n");
        printf("partenza: inserire fermata di partenza\n");
        printf("capolinea: inserire capolinea\n");
        printf("ritardo: inserire due date nel formaro aa/mm/gg\n");
        printf("ritardo_tot: inserire codice di tratta\n");
        printf("fine: TERMINAZIONE\n");
        printf("\nInserire <comando> <opzionale> <opzionale>: ");
        fgets(inserimento, 100, stdin);
        //COMANDI
        continua=selezionaDati(file_log, n_tratte, leggiComando(inserimento), inserimento);
    }


    return  0;
}

comando_e leggiComando (char inserimento[100]) {
    comando_e c;
    char cmd[MAX_STRINGHE];

    sscanf(inserimento, "%s", cmd);

    if (strcmp(cmd, "date")==0)
        c=r_date;
    else if (strcmp(cmd, "partenza")==0)
        c=r_partenza;
    else if (strcmp(cmd, "capolinea")==0)
        c=r_capolinea;
    else if (strcmp(cmd, "ritardo")==0)
        c=r_ritardo;
    else if (strcmp(cmd, "ritardo_tot")==0)
        c=r_ritardo_tot;
    else if (strcmp(cmd, "fine")==0)
        c=r_fine;
    else
        c=r_err;
    return c;
}

int selezionaDati (Tratta t[MAX_TRATTE], int n, comando_e r, char str[100]) {

    char opz1[MAX_STRINGHE];
    char opz2[MAX_STRINGHE];
    int ritardo=0;

    switch (r) {
        case r_date:
            sscanf(str, "%*s %s %s", opz1, opz2);
            printf("Stampo tratte comprese tra %s e %s:\n", opz1, opz2);
            for (int i=0; i<n; i++) {
                if (checkData(t[i], opz1, opz2))
                    stampaTratta(t[i]);
            }
            printf("-------");
            break;
        case r_partenza:
            sscanf(str, "%*s %s", opz1);
            printf("Stampo tratte con partenza %s:\n", opz1);
            for (int i=0; i<n; i++) {
                if (strcmp(t[i].partenza, opz1)==0)
                    stampaTratta(t[i]);
            }
            printf("-------");
            break;
        case r_capolinea:
            sscanf(str, "%*s %s", opz1);
            printf("Stampo tratte con partenza %s:\n", opz1);
            for (int i=0; i<n; i++) {
                if (strcmp(t[i].partenza, opz1)==0 || strcmp(t[i].destinazione, opz1)==0)
                    stampaTratta(t[i]);
            }
            printf("-------");
            break;
        case r_ritardo:
            sscanf(str, "%*s %s %s", opz1, opz2);
            printf("Stampo tratte in ritardo comprese tra %s e %s:\n", opz1, opz2);
            for (int i = 0; i < n; ++i) {
                if (t[i].ritardo!=0) {
                    if (checkData(t[i], opz1, opz2))
                        stampaTratta(t[i]);
                }
            }
            printf("-------");
            break;
        case r_ritardo_tot:
            sscanf(str, "%*s %s", opz1);
            printf("Stampo ritardo complessivo tratta %s: ", opz1);
            for (int i = 0; i < n; ++i) {
                if (strcmp(t[i].codicetratta, opz1)==0)
                    ritardo+=t[i].ritardo;
            }
            printf("%d\n", ritardo);
            printf("-------");
            break;
        case r_fine:
            printf("Selezione completata!");
            return 0;
        case r_err:
            printf("INSERIMENTO COMANDO ERRATO!");
            return 0;
        default:
            printf("INSERIMENTO COMANDO ERRATO!");
            return 0;
    }
    return 1;

}

void stampaTratta(Tratta t) {
    printf("%s %s %s %d/%02d/%02d %02d:%02d:%02d %02d:%02d:%02d %d\n", t.codicetratta, t.partenza, t.destinazione, t.d.anno, t.d.giorno, t.d.mese, t.o_partenza.ora, t.o_partenza.minuti, t.o_partenza.secondi, t.o_arrivo.ora, t.o_arrivo.minuti, t.o_arrivo.secondi, t.ritardo);
}

int checkData(Tratta tratta, char opz1[MAX_STRINGHE], char opz2[MAX_STRINGHE]) {
    Dt i, f;
    int inizio=0;
    int fine=0;
    sscanf(opz1, "%d/%d/%d", &i.anno, &i.giorno, &i.mese);
    sscanf(opz2, "%d/%d/%d", &f.anno, &f.giorno, &f.mese);

    //CONTROLLO INIZIO
    if (tratta.d.anno>i.anno)
        inizio=1;
    else if (tratta.d.anno==i.anno) {
        if (tratta.d.mese>i.mese)
            inizio=1;
        else if (tratta.d.mese==i.mese) {
            if (tratta.d.giorno>i.giorno)
                inizio=1;
            else if (tratta.d.giorno==i.giorno) {
                inizio=1;
            }
            else if (tratta.d.giorno<i.giorno){
                inizio=0;
            }
        }
        else if (tratta.d.mese<i.mese){
            inizio=0;
        }
    }
    else if (tratta.d.anno<i.anno){
        inizio=0;
    }

    //CONTROLLO FINE
    if (tratta.d.anno>f.anno)
        fine=0;
    else if (tratta.d.anno==f.anno) {
        if (tratta.d.mese>f.mese)
            fine=0;
        else if (tratta.d.mese==f.mese) {
            if (tratta.d.giorno>f.giorno)
                fine=0;
            else if (tratta.d.giorno==f.giorno) {
                fine=1;
            }
            else if (tratta.d.giorno<f.giorno){
                fine=1;
            }
        }
        else if (tratta.d.mese<f.mese){
            fine=1;
        }
    }
    else if (tratta.d.anno<f.anno){
        fine=1;
    }

    if (inizio==1 && fine==1)
        return 1;
    return 0;
}
