#include <stdio.h>
#include <stdlib.h>

typedef struct Activity {
    int ts;
    int tf;
    int durata;
}att_t;
typedef struct Wrapper {
    att_t *att;
    int n_att;
    int ris;
    int last;
    int *dur;
    int *prec;
}wrp_t;

void att_read(wrp_t *wrapper);
void val_init(wrp_t *wrapper);
void sortVett(wrp_t *wrapper);
void bestAtt(wrp_t *wrapper);
void printBestAtt(wrp_t *wrapper, int i);

int main() {
    wrp_t *wrapper=malloc(sizeof(wrp_t));

    att_read(wrapper);
    sortVett(wrapper);
    bestAtt(wrapper);

    printf("Best activity sequence:\n");
    printBestAtt(wrapper, wrapper->last);
    printf("and its duration is %d\n", wrapper->ris);

    return 0;
}

void att_read(wrp_t *wrapper) {
    FILE *fp=fopen("att.txt", "r");
    if (fp==NULL)
        printf("Errore nel caricamento\n");
    fscanf(fp, "%d", &wrapper->n_att);
    val_init(wrapper);
    for (int i=0; i<wrapper->n_att; i++) {
        fscanf(fp, "%d %d", &wrapper->att[i].ts, &wrapper->att[i].tf);
        wrapper->att[i].durata=(wrapper->att[i].tf) - (wrapper->att[i].ts);
    }
    return;
}
void val_init(wrp_t *wrapper) {
    wrapper->att=malloc(wrapper->n_att* sizeof(att_t));
    wrapper->dur=malloc(wrapper->n_att* sizeof(att_t));
    wrapper->prec=malloc(wrapper->n_att* sizeof(att_t));
    wrapper->ris=-1;
    wrapper->last=-1;
}
void sortVett(wrp_t *wrapper) {
    att_t tmp;
    for (int i=0; i<wrapper->n_att-1; i++) {
        if (wrapper->att[i].ts>wrapper->att[i+1].ts) {
            tmp.ts=wrapper->att[i+1].ts;
            tmp.tf=wrapper->att[i+1].tf;
            tmp.durata=wrapper->att[i+1].durata;
            wrapper->att[i+1].ts=wrapper->att[i].ts;
            wrapper->att[i+1].tf=wrapper->att[i].tf;
            wrapper->att[i+1].durata=wrapper->att[i].durata;
            wrapper->att[i].ts=tmp.ts;
            wrapper->att[i].tf=tmp.tf;
            wrapper->att[i].durata=tmp.durata;
        } else if (wrapper->att[i].ts==wrapper->att[i+1].ts) {
            if (wrapper->att[i].tf>wrapper->att[i+1].tf) {
                tmp.ts=wrapper->att[i+1].ts;
                tmp.tf=wrapper->att[i+1].tf;
                tmp.durata=wrapper->att[i+1].durata;
                wrapper->att[i+1].ts=wrapper->att[i].ts;
                wrapper->att[i+1].tf=wrapper->att[i].tf;
                wrapper->att[i+1].durata=wrapper->att[i].durata;
                wrapper->att[i].ts=tmp.ts;
                wrapper->att[i].tf=tmp.tf;
                wrapper->att[i].durata=tmp.durata;
            }
        }
    }
}
void bestAtt(wrp_t *wrapper) {
    int i, j;
    //INIZIALIZZO PRIMO ELEMENTO VETTORI
    wrapper->ris = wrapper->att[0].durata;
    wrapper->last = 0;
    wrapper->dur[0] = wrapper->att[0].durata;
    wrapper->prec[0] = -1;
    //CICLO SU OGNI ATTIVITA
    for (i = 1; i < wrapper->n_att; i++) {
        //SONO SICURO CHE ATTIVITA LUNGA 1 SIA COMPATIBILE
        wrapper->dur[i] = wrapper->att[i].durata;
        wrapper->prec[i] = -1;
        //CONTROLLO SE E MASSIMA
        for (j = 0; j < i; j++) {
            //CONTROLLO SE COMPATIBILE
            if (wrapper->att[i].ts > wrapper->att[j].tf) {
                //CONTROLLO SE DURATA MASSIMA
                if (wrapper->dur[i] < wrapper->dur[j] + wrapper->att[i].durata) {
                    wrapper->dur[i] = wrapper->dur[j] + wrapper->att[i].durata;
                    wrapper->prec[i] = j;
                }
            }
        }
        if (wrapper->ris < wrapper->dur[i]) {
            wrapper->ris = wrapper->dur[i];
            wrapper->last = i;
        }
    }
}
void printBestAtt(wrp_t *wrapper, int i) {
    if (i!=-1) {
        printBestAtt(wrapper, wrapper->prec[i]);
        printf("%d - %d\n", wrapper->att[i].ts, wrapper->att[i].tf);
    }
    /*
    if (wrapper->prec[i]==-1) {

        return;
    }
    printBestAtt(wrapper, wrapper->prec[i]);
    printf("%d - %d\n", wrapper->att[i].ts, wrapper->att[i].tf);
     */
}