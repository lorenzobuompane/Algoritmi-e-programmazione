#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define SMAX 120

char *cercaRegexp(char *src, char *regexp);
int lunghezzaRegexp(char *regexp);

int main() {
    char regexp[SMAX];
    char src[SMAX];
    char stampa[SMAX];
    char *rit;

    printf("Inserisci stringa di ricerca:\n");
    gets(src);
    printf("Inserisci espressione regolare:\n");
    gets(regexp);

    rit=cercaRegexp(src, regexp);

    if (rit==NULL)
        printf("Regexp non trovata\n");
    else{
        sscanf(rit, "%s", stampa);
        printf("%s\n", stampa);
    }

    return 0;
}

char *cercaRegexp(char *src, char *regexp) {
    char *pos;
    int i=0;    //scandisce word
    int j=0;    //scandisce regexp
    int k=0;    //offset posizione parola su src
    char word[SMAX+1];
    char wordPrint[SMAX+1];
    int flag=0;
    int out=0;  //lettere da non considerare nel caso [ ]


    while (sscanf(src+k, "%s", word)==1) {  //while: acquisizione parola per parola della stringa src
        i=0;        //primo carattere di word
        j=0;        //azzero posizione regexp
        pos=src+k;  //posizione della parola che sto valutando

        while (i<strlen(word) && j<strlen(regexp)) {    //while: ricerca regexp (parametri controllo lunghezze)

            switch (regexp[j]) {    //switch: tipologia di carattere letto
                case '.':
                    i++;
                    j++;
                    break;
                case '[':
                    j++;
                    if (regexp[j]=='^') {
                        j++;
                        out=1;
                    }
                    if (out==1) {       //con ^
                        flag=1;
                        while (regexp[j]!=']') {        //considero tutte le lettere
                            if (word[i]==regexp[j])     //se ne trovo una uguale non va bene
                                flag=0;
                            j++;
                        }
                        if (flag==1) {                  //è OK
                            j++;
                        } else j=0;
                    }
                    else {
                        flag=0;
                        while (regexp[j]!=']') {        //considero tutte le lettere
                            if (word[i]==regexp[j]) {   //se ne trovo almeno una uguale va bene
                                flag=1;
                            }
                            j++;
                        }
                        if (flag==1) {
                            j++;
                        } else j=0;
                    }
                    i++;

                    //DA COMPLETARE
                    break;
                case '\\':
                    j++;    //forse neccessita di doppio incremento di j
                    if (regexp[j]=='a') {
                        if (islower(word[i]))
                            j++;
                        else
                            j = 0;
                    }
                    if (regexp[j]=='A') {
                        if (isupper(word[i]))
                            j++;
                        else
                            j=0;
                    }
                    i++;
                    break;
                default:
                    if (word[i]==regexp[j])
                        j++;
                    else
                        j=0;
                    i++;
                    break;
            }
            sscanf(pos, "%s", wordPrint);
            if (j==strlen(regexp) && lunghezzaRegexp(regexp)==strlen(wordPrint)) {           //CAMBIO WORD CON REGEXP
                return pos;     //se parole dopo la prima mi tiene in considerazione anche lo spazio
            }
            k++;
        }
    }

    return NULL;
}

int lunghezzaRegexp(char *regexp) {
    int l=0;
    for (int i=0; i<strlen(regexp); i++) {
        if (regexp[i]=='[') {
            while (regexp[i]!=']') {
                i++;
            }
        }
        l++;
    }
}