//
// Created by loren on 20/01/2020.
//

#ifndef INC_11_1_DATAORA_H
#define INC_11_1_DATAORA_H

typedef struct Data {
    int aa;
    int mm;
    int gg;
}data_t;

typedef struct Ora {
    int hh;
    int mm;
}ora_t;

typedef struct Time {
    data_t data;
    ora_t ora;
}tempo_t;

int DATEcmp(data_t d1, data_t d2);
int HOURcmp(ora_t h1, ora_t h2);
int DATEHOURcmp(tempo_t t1, tempo_t t2);

#endif //INC_11_1_DATAORA_H
