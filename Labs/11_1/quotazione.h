//
// Created by loren on 21/01/2020.
//

#ifndef INC_11_1_QUOTAZIONE_H
#define INC_11_1_QUOTAZIONE_H

#include <stdlib.h>
#include <stdio.h>
#include "DataOra.h"


typedef struct Quotazione {
    data_t data;
    float QUOTgiornaliera;
} quot_t;

typedef struct BSTnode* BSTquot_t;

int BSTdateExist(BSTquot_t BSTnode, data_t data);
BSTquot_t BSTnewnode(quot_t quot);
BSTquot_t BSTinsert(BSTquot_t BSThead, quot_t quot);
void BSTinsertR(BSTquot_t node, quot_t quot);
void BSTstampaQuotazione(BSTquot_t BSTnode, data_t data);
void BSTsearch(BSTquot_t node, data_t d1, data_t d2, float *min, float *max);
void BSTsearchALL(BSTquot_t node, float *min, float *max);
void BSTcamminoMINMAX(BSTquot_t node, int *min, int *max, int count);
void BSTcamminoHEAD(BSTquot_t node, int *min, int *max);
BSTquot_t BSTbalance(BSTquot_t head);
BSTquot_t balanceR(BSTquot_t h);
BSTquot_t partR(BSTquot_t h, int r);
BSTquot_t rotR(BSTquot_t node);
BSTquot_t rotL(BSTquot_t node);
void BSTprintIN(BSTquot_t node);


#endif //INC_11_1_QUOTAZIONE_H
