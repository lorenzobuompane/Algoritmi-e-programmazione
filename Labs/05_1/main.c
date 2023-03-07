#include <stdio.h>
#include <stdlib.h>

#define SIZE 256

typedef struct Amico {
    char **scelte;
    int num_scelte;
} Amico;

void stampa(Amico *amici, int num_amici);
int princ_molt(int pos, Amico *val, char **sol, int n, int count);

int main() {
    FILE *fp=fopen("brani.txt", "r");
    if (fp==NULL)
        return -1;

    Amico *amici;
    int num_amici;
    char **sol;
    int count=0;

    //ACQUISIZIONE DA FILE CON ALLOCAZIONE DINAMICA
    fscanf(fp, "%d", &num_amici);
    amici=(Amico *)malloc(num_amici* sizeof(Amico));
    for (int i=0; i<num_amici; i++) {
        fscanf(fp, "%d", &amici[i].num_scelte);
        amici[i].scelte=(char **)malloc(amici[i].num_scelte* sizeof(char*));
        for (int j=0; j<amici[i].num_scelte; j++) {
            amici[i].scelte[j]=(char *)malloc(SIZE* sizeof(char));
            fscanf(fp, "%s", amici[i].scelte[j]);
        }
    }

    //stampa(amici, num_amici);

    //ALLOCO DINAMICAMENTE VETTORE SOLUZIONE
    sol=(char **)malloc(num_amici* sizeof(char *));
    for (int i=0; i<num_amici; i++) {
        sol[i]=(char *)malloc(SIZE* sizeof(char));
    }

    count=princ_molt(0, amici, sol, num_amici, count);

    printf("%d", count);

    return 0;
}

void stampa(Amico *amici, int num_amici) {
    for (int i=0; i<num_amici; i++) {
        printf("Amico %d\n", i+1);
        for (int j=0; j<amici[i].num_scelte; j++) {
            printf("\t%s\n", amici[i].scelte[j]);
        }
        printf("\n");
    }
}

int princ_molt(int pos, Amico *val, char **sol, int n, int count) {
    int i;
    if (pos>=n) {
        for (i=0; i<n; i++)
            printf("%s\n", sol[i]);
        printf("\n");
        return count + 1;
    }
    for (i=0; i<val[pos].num_scelte; i++) {
        sol[pos]=val[pos].scelte[i];
        count=princ_molt(pos+1, val, sol, n, count);
    }
    return count;
}