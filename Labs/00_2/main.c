#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int conta(char s[], int n);

int main()
{
    char nomeFile[20];
    char parola[20];
    FILE *fp;
    int parole=0;
    int nss=0;
    int lss=0;

    printf("Nome file:\n");
    scanf("%s", nomeFile);

    fp=fopen(nomeFile, "r");
    if(fp==NULL)
        return -1;

    fscanf(fp, "%d", &parole);

    printf("\nInserire lunghetta sottostringhe:\n");
    scanf("%d", &lss);

    for (int i=0; i<parole; i++){
        fscanf(fp, "%s", parola);
        nss=conta(parola, lss);
        printf("\nParola: %s\tNumero di sottostringhe di lunghezza %d contententi 2 vocali: %d", parola, lss, nss);
    }

    fclose(fp);

    return 0;
}

int conta(char s[], int n) {

    int vocali=0;
    int a=0;

    for (int i=0; i<=strlen(s)-n; i++) {
   //     if(isupper(s[i]))
   //         s[i]=tolower(s[i]);
        for (int j=0; j<n; j++) {
            if (s[i+j]=='a' || s[i+j]=='e' || s[i+j]=='i' || s[i+j]=='o' || s[i+j]=='u' || s[i+j]=='A' || s[i+j]=='E' || s[i+j]=='I' || s[i+j]=='O' || s[i+j]=='U')
                vocali++;
        }
        if (vocali==2)
            a++;
        vocali=0;
    }

    return a;
}
