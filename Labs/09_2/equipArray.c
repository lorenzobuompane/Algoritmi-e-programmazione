#include "equipArray.h"

struct equipArray_s {
    int inUso;
    int vettEq[EQUIP_SLOT];
};

equipArray_t equipArray_init() {
    equipArray_t tmp = malloc(sizeof(struct equipArray_s));
    for (int i=0; i<EQUIP_SLOT; i++) {
        tmp->vettEq[i]=-1;
    }
    tmp->inUso=0;
    return tmp;
}

void equipArray_free(equipArray_t equipArray) {
    free(equipArray);
}

int equipArray_inUse(equipArray_t equipArray) {
    return equipArray->inUso;
}

void equipArray_print(FILE *fp, equipArray_t equipArray, invArray_t invArray) {
    for (int i=0; i<EQUIP_SLOT; i++) {
        if (equipArray->vettEq[i]!=-1) {
            fprintf(fp, "\t");
            invArray_printByIndex(fp, invArray, equipArray->vettEq[i]);
        }

    }
}

void equipArray_update(equipArray_t equipArray, invArray_t invArray) {
    int i;
    char str[LEN];
    invArray_print(stdout, invArray);
    printf("Inserire oggetto da aggiungere/rimuovere:\n");
    scanf("%s", str);
    i=invArray_searchByName(invArray, str);
    for (int j=0; j<EQUIP_SLOT; j++) {
        if (i==equipArray_getEquipByIndex(equipArray, j)) {
            //PRESENTE IN equip --> RIMUOVERE
            equipArray->inUso-=1;
            equipArray->vettEq[j]=-1;
            return;
        }
    }
    //NON PRESENTE IN equip --> AGGIUNGERE
    if (equipArray->inUso>=EQUIP_SLOT)
        return;
    for (int j=0; j<EQUIP_SLOT; j++) {
        if (equipArray->vettEq[j]==-1) {
            equipArray->inUso+=1;
            equipArray->vettEq[j]=invArray_searchByName(invArray, str);
            return;
        }
    }

}

int equipArray_getEquipByIndex(equipArray_t equipArray, int index) {
    return equipArray->vettEq[index];
}