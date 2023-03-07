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

typedef enum output {
    o_FILE,
    o_STDOUT,
    o_ERR
} output;

typedef enum ord {
    r_DATAORA,
    r_CODICE,
    r_PARTENZA,
    r_DESTINAZIONE,
    s_PARTENZA,
    r_ERR
} ord;

void BubbleSort(int N, Tratta* o_DataOra[], Tratta* o_CodiceTratta[], Tratta* o_Destinazione[], Tratta* o_Partenza[]);
int DataOraGT (Tratta A, Tratta B);
void stampaTratta(Tratta t);
void stampaTrattaFile(Tratta t, FILE *fo);
output comando_o(char comando[31]);
ord comando_r(char comando[31]);
int selezionaPartenza(char partenza[31], char partenza1[31]);

int main() {
    int n_tratte;
    Tratta file_log[MAX_TRATTE];
    Tratta *o_DataOra[MAX_TRATTE];
    Tratta *o_CodiceTratta[MAX_TRATTE];
    Tratta *o_Partenza[MAX_TRATTE];
    Tratta *o_Destinazione[MAX_TRATTE];
    char comando[MAX_STRINGHE];
    char partenza[MAX_STRINGHE];
    output out;
    ord ordScelto;
    FILE *fo;


    //ACQUISIZIONE FILE
    FILE *fp=fopen("corse.txt", "r");
    if (fp==NULL)
        return -1;
    //LETTURA FILE
    fscanf(fp, "%d", &n_tratte);
    for (int i=0; i<n_tratte; i++) {
        fscanf(fp, "%s %s %s %d/%d/%d %d:%d:%d %d:%d:%d %d", file_log[i].codicetratta, file_log[i].partenza, file_log[i].destinazione, &file_log[i].d.anno, &file_log[i].d.giorno, &file_log[i].d.mese, &file_log[i].o_partenza.ora, &file_log[i].o_partenza.minuti, &file_log[i].o_partenza.secondi, &file_log[i].o_arrivo.ora, &file_log[i].o_arrivo.minuti, &file_log[i].o_arrivo.secondi, &file_log[i].ritardo);
    }

    //RIEMPIO VETTORI PUNTATORI NON IN ORDINE
    for (int i=0; i<n_tratte; i++) {
        o_DataOra[i] = &file_log[i];
        o_CodiceTratta[i]=&file_log[i];
        o_Destinazione[i]=&file_log[i];
        o_Partenza[i]=&file_log[i];
    }

    //ORDINO VETTORI PUNTATORI
    BubbleSort(n_tratte, o_DataOra, o_CodiceTratta, o_Destinazione, o_Partenza);
    printf("VETTORI ORDINATI\n");

    //STAMPO VETTORE
    printf("OUTPUT:\n\to_FILE\n\to_STDOUT\n");
    scanf("%s", comando);
    out=comando_o(comando);
    printf("ORDINAMENTO:\n\tr_DATAORA\n\tr_CODICE\n\tr_PARTENZA\n\tr_DESTINAZIONE\n\ts_PARTENZA\n");
    scanf("%s", comando);
    ordScelto=comando_r(comando);


    switch (out) {
        case o_FILE:
            fo=fopen("output.txt", "w");
            switch (ordScelto) {
                case r_DATAORA:
                    for (int i=0; i<n_tratte; i++)
                        stampaTrattaFile(*o_DataOra[i], fo);
                    break;
                case r_CODICE:
                    for (int i=0; i<n_tratte; i++)
                        stampaTrattaFile(*o_CodiceTratta[i], fo);
                    break;
                case r_PARTENZA:
                    for (int i=0; i<n_tratte; i++)
                        stampaTrattaFile(*o_Partenza[i], fo);
                    break;
                case r_DESTINAZIONE:
                    for (int i=0; i<n_tratte; i++)
                        stampaTrattaFile(*o_Destinazione[i], fo);
                    break;
                case s_PARTENZA:
                    printf("Scegli stazione di partenza: ");
                    scanf("%s", partenza);
                    for (int i=0; i<n_tratte; i++)
                        if (selezionaPartenza(o_Partenza[i]->partenza, partenza))
                            stampaTrattaFile(*o_Partenza[i], fo);
                    break;
                default:
                    fprintf(fo, "ORDINAMENTO NON VALIDO!");
                    break;
            }
            printf("STAMPATO SU FILE!");
            fclose(fo);
            break;
        case o_STDOUT:
            switch (ordScelto) {
                case r_DATAORA:
                    for (int i=0; i<n_tratte; i++)
                        stampaTratta(*o_DataOra[i]);
                    break;
                case r_CODICE:
                    for (int i=0; i<n_tratte; i++)
                        stampaTratta(*o_CodiceTratta[i]);
                    break;
                case r_PARTENZA:
                    for (int i=0; i<n_tratte; i++)
                        stampaTratta(*o_Partenza[i]);
                    break;
                case r_DESTINAZIONE:
                    for (int i=0; i<n_tratte; i++)
                        stampaTratta(*o_Destinazione[i]);
                    break;
                case s_PARTENZA:
                    printf("Scegli stazione di partenza: \n");
                    scanf("%s", partenza);
                    for (int i=0; i<n_tratte; i++)
                        if (selezionaPartenza(o_Partenza[i]->partenza, partenza))
                            stampaTratta(*o_Partenza[i]);
                    break;
                default:
                    printf("ORDINAMENTO NON VALIDO!");
                    break;
            }
            break;
        default:
            printf("OUTPUT NON VALIDO!");
    }

    return 0;
}

int selezionaPartenza(char p_vett[31], char p_acq[31]) {
    if (strlen(p_acq)==strlen(p_vett))
        if (strcmp(p_acq, p_vett)==0)
            return 1;
    for (int i=0; i<strlen(p_acq); i++)
        if (p_acq[i]!=p_vett[i])
            return 0;
    return 1;
}

ord comando_r(char comando[31]) {
    if (strcmp(comando, "r_DATAORA")==0)
        return r_DATAORA;
    if (strcmp(comando, "r_CODICE")==0)
        return r_CODICE;
    if (strcmp(comando, "r_PARTENZA")==0)
        return r_PARTENZA;
    if (strcmp(comando, "r_DESTINAZIONE")==0)
        return r_DESTINAZIONE;
    if (strcmp(comando, "s_PARTENZA")==0)
        return s_PARTENZA;
    return r_ERR;
}

output comando_o(char comando[31]) {
    if (strcmp(comando, "o_FILE")==0)
        return o_FILE;
    if (strcmp(comando, "o_STDOUT")==0)
        return o_STDOUT;
    return o_ERR;
}

void BubbleSort(int N, Tratta* o_DataOra[], Tratta* o_CodiceTratta[], Tratta* o_Destinazione[], Tratta* o_Partenza[]) {
    int i, j, l=0, r=N-1;
    Tratta * temp;
    for (i=l; i<r; i++) {
        for (j=l; j<r-i+l; j++) {
            //ORDINAMENTO DATA ORA
            if (DataOraGT(*o_DataOra[j], *o_DataOra[j+1])) {
                temp=o_DataOra[j];
                o_DataOra[j]=o_DataOra[j+1];
                o_DataOra[j+1]=temp;
            }
            //ORDINAMENTO CODICE TRATTA
            if (strcmp(o_CodiceTratta[j]->codicetratta, o_CodiceTratta[j+1]->codicetratta)>0) {
                temp=o_CodiceTratta[j];
                o_CodiceTratta[j]=o_CodiceTratta[j+1];
                o_CodiceTratta[j+1]=temp;
            }
            //ORDINAMENTO DESTINAZIONE
            if (strcmp(o_Destinazione[j]->destinazione, o_Destinazione[j+1]->destinazione)>0) {
                temp=o_Destinazione[j];
                o_Destinazione[j]=o_Destinazione[j+1];
                o_Destinazione[j+1]=temp;
            }
            //ORDINAMENTO PARTENZA
            if (strcmp(o_Partenza[j]->partenza, o_Partenza[j+1]->partenza)>0) {
                temp=o_Partenza[j];
                o_Partenza[j]=o_Partenza[j+1];
                o_Partenza[j+1]=temp;
            }
        }
    }
}

int DataOraGT (Tratta A, Tratta B) {
    int swap=0;

    if (A.d.anno>B.d.anno)
        swap=1;
    else if (A.d.anno==B.d.anno) {
        if (A.d.mese>B.d.mese)
            swap=1;
        else if (A.d.mese==B.d.mese) {
            if (A.d.giorno>B.d.giorno)
                swap=1;
            else if (A.d.giorno==B.d.giorno){
                if (A.o_partenza.ora>B.o_partenza.ora)
                    swap=1;
                else if (A.o_partenza.ora==B.o_partenza.ora){
                    if (A.o_partenza.minuti>B.o_partenza.minuti)
                        swap=1;
                    else if (A.o_partenza.minuti==B.o_partenza.minuti){
                        if (A.o_partenza.secondi>B.o_partenza.secondi)
                            swap=1;
                    }
                }
            }
        }
    }

    return swap;

}

void stampaTratta(Tratta t) {
    printf("%s %s %s %d/%02d/%02d %02d:%02d:%02d %02d:%02d:%02d %d\n", t.codicetratta, t.partenza, t.destinazione, t.d.anno, t.d.giorno, t.d.mese, t.o_partenza.ora, t.o_partenza.minuti, t.o_partenza.secondi, t.o_arrivo.ora, t.o_arrivo.minuti, t.o_arrivo.secondi, t.ritardo);
}

void stampaTrattaFile(Tratta t, FILE *fo) {
    fprintf(fo, "%s %s %s %d/%02d/%02d %02d:%02d:%02d %02d:%02d:%02d %d\n", t.codicetratta, t.partenza, t.destinazione, t.d.anno, t.d.giorno, t.d.mese, t.o_partenza.ora, t.o_partenza.minuti, t.o_partenza.secondi, t.o_arrivo.ora, t.o_arrivo.minuti, t.o_arrivo.secondi, t.ritardo);

}