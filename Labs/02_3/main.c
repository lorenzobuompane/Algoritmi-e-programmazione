#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define SMAX 21
#define CMAX 6
#define RMAX 201
#define PMAX 26

int checkParola(char p[PMAX], char s[CMAX]);

int confronta(char p[26], char s[6], int i);

void stampa(char parola[26], int count, char seq[6]);

void split_parola(char pString[2][26], char parola[26]);

int apostrofo(char parola[26]);

int main() {

    //APERTURA FILE
    FILE *ft=fopen("testo.txt", "r");
    FILE *fs=fopen("sequenze.txt","r");
    if (ft==NULL && fs==NULL)
        return -1;

    char sequenze[SMAX][CMAX];
    int n_sequenza;
    char parola[PMAX];
    int check=0;
    int count=0;
    int found=0;

    fscanf(fs,"%d", &n_sequenza);
    for (int i = 0; i < n_sequenza; ++i) {
        fscanf(fs, "%s", sequenze[i]);
    }

    for (int j = 0; j < n_sequenza; ++j) {
        printf("Stampo parole contenenti la sequenza %s:\n", sequenze[j]);
        while (fscanf(ft,"%s", parola)!=EOF) {
            count++;
            if (apostrofo(parola)==1)
                count++;
            check=checkParola(parola, sequenze[j]);
            if (check && found<10) {
                stampa(parola, count, sequenze[j]);
                found++;
            }
            else if (found==10)
                break;
        }
        printf("\n--------\n\n");
        found=0;
        count=0;
        rewind(ft);
    }
    fclose(ft);
    fclose(fs);
    return 0;
}

void stampa(char parola[26], int count, char seq[6]) {
    char p_apo[2][26];
    char s_low[6];

    //SEQUENZA IN MINUSCOLO
    for (int k = 0; k < strlen(seq); ++k) {
        s_low[k]=tolower(seq[k]);
    }
    s_low[strlen(seq)]='\0';

    if (apostrofo(parola)==1) {
        split_parola(p_apo, parola);
        if (strstr(p_apo[0], s_low)==NULL)
            printf("%s (posizione %d)\n", p_apo[1], count);
        else
            printf("%s\' (posizione %d)\n", p_apo[0], count-1);
    }
    else {
        for (int i = 0; i < strlen(parola); ++i) {
            if (ispunct(parola[i]))
                parola[i]='\0';
        }
        printf("%s (posizione %d)\n", parola, count);
    }

}

int apostrofo(char parola[26]) {
    for (int i = 0; i < strlen(parola); i++) {
        if (parola[i]=='\''){
            return 1;
        }
    }
    return 0;
}

void split_parola(char pString[2][26], char parola[26]) {
    int i=0;
    while (parola[i]!='\'') {
        pString[0][i]=parola[i];
        i++;
    }
    i++;
    pString[0][i]='\'';
    for (int k = 0; k < strlen(parola)-strlen(pString[0]); k++, i++) {
        pString[1][k]=parola[i];
    }
}

int checkParola(char p[PMAX], char s[CMAX]) {
    char p_low[PMAX] = {'\0'};
    char s_low[CMAX] = {'\0'};
    int flag=0;
    int j=0;

    //TUTTO IN MINUSCOLO
    for (j = 0; j < strlen(p); ++j) {
        p_low[j]=tolower(p[j]);
    }
    for (int k = 0; k < strlen(s); ++k) {
        s_low[k]=tolower(s[k]);
    }

    //CONTROLLO PRIMO CARATTERE
    for (int i = 0; i < strlen(p_low); ++i) {
        if (p_low[i]==s_low[0])
            flag=confronta(p_low, s_low, i);
        if (flag)
            break;
    }
    return flag;
}

int confronta(char p[26], char s[6], int i) {
    for (int j = 0; j < strlen(s); ++j) {
        if (p[i+j]!=s[j])
            return 0;
    }
    return 1;
}