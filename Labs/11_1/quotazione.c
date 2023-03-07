//
// Created by loren on 21/01/2020.
//

#include "quotazione.h"

struct BSTnode {
    quot_t quot;
    int N;
    BSTquot_t LEFT;
    BSTquot_t RIGHT;
};


int BSTdateExist(BSTquot_t BSTnode, data_t data) {
    if (BSTnode == NULL)
        return 0;
    if (DATEcmp(data, BSTnode->quot.data)==0)
        return 1;
    if (DATEcmp(data, BSTnode->quot.data)==1)
        return BSTdateExist(BSTnode->RIGHT, data);
    else
        return BSTdateExist(BSTnode->LEFT, data);
}

BSTquot_t BSTnewnode(quot_t quot) {
    BSTquot_t q = malloc(sizeof(struct BSTnode));
    q->N=1;
    q->LEFT=NULL;
    q->RIGHT=NULL;
    q->quot=quot;
    return q;
}

BSTquot_t BSTinsert(BSTquot_t BSThead, quot_t quot) {
    if (BSThead == NULL) {
        return BSTnewnode(quot);
    }
    BSTinsertR(BSThead, quot);

    return BSThead;

}

void BSTinsertR(BSTquot_t node, quot_t quot) {
    int confrontoData = DATEcmp(quot.data, node->quot.data);
    (node->N)++;
    if (confrontoData>=0) {
        if (node->RIGHT == NULL)
            node->RIGHT = BSTnewnode(quot);
        else {
            BSTinsertR(node->RIGHT, quot);
        }

    }
    else {
        if (node->LEFT == NULL)
            node->LEFT = BSTnewnode(quot);
        else {
            BSTinsertR(node->LEFT, quot);

        }
    }

}

void BSTstampaQuotazione(BSTquot_t BSTnode, data_t data) {
    if (DATEcmp(data, BSTnode->quot.data)==0) {
        printf("Quotazione: %f", BSTnode->quot.QUOTgiornaliera);
        return;
    }
    if (DATEcmp(data, BSTnode->quot.data)==1)
        BSTstampaQuotazione( BSTnode->RIGHT,  data);
    else
        BSTstampaQuotazione( BSTnode->LEFT,  data);
}

void BSTsearch(BSTquot_t node, data_t d1, data_t d2, float *min, float *max) {
    if (node == NULL)
        return;

    BSTsearch(node->LEFT, d1, d2, min, max);
    if (DATEcmp(d1, node->quot.data)>=0 && DATEcmp(d2, node->quot.data)<=0) {
        if (node->quot.QUOTgiornaliera>=*max)
            *max= node->quot.QUOTgiornaliera;
        if (node->quot.QUOTgiornaliera<=*min)
            *min= node->quot.QUOTgiornaliera;
    }
    BSTsearch(node->RIGHT, d1, d2, min, max);
}

void BSTsearchALL(BSTquot_t node, float *min, float *max) {
    if (node == NULL)
        return;

    BSTsearchALL(node->LEFT, min, max);
    printf("%d %d %d %d \n", node->quot.data.aa, node->quot.data.mm, node->quot.data.gg, node->N);
    if (node->quot.QUOTgiornaliera>=*max)
        *max= node->quot.QUOTgiornaliera;
    if (node->quot.QUOTgiornaliera<=*min)
        *min= node->quot.QUOTgiornaliera;
    BSTsearchALL(node->RIGHT, min, max);
}

void BSTcamminoHEAD(BSTquot_t node, int *min, int *max) {
    int maxL=INT_MIN;
    int maxR=INT_MIN;
    int minL=INT_MAX;
    int minR=INT_MAX;
    if (node->RIGHT!=NULL)
        BSTcamminoMINMAX(node->RIGHT, &minR, &maxR, 1);
    else {
        minR=0;
        maxR=0;
    }
    if (node->LEFT!=NULL)
        BSTcamminoMINMAX(node->LEFT, &minL, &maxL, 1);
    else {
        minL=0;
        maxL=0;
    }
    if (minL<minR)
        *min=minL;
    else
        *min=minR;
    if (maxL>maxR)
        *max=maxL;
    else
        *max=maxR;
}

void BSTcamminoMINMAX(BSTquot_t node, int *min, int *max, int count) {
    if (node->LEFT==NULL && node->RIGHT==NULL) {
        if (*min>count)
            *min=count;
        if (*max<count)
            *max=count;
        return;
    }
    if (node->RIGHT!=NULL)
        BSTcamminoMINMAX(node->RIGHT, min, max, count+1);
    if (node->LEFT!=NULL)
        BSTcamminoMINMAX(node->LEFT, min, max, count+1);
}
BSTquot_t BSTbalance(BSTquot_t head) {
    return balanceR(head);
}
BSTquot_t balanceR(BSTquot_t h) {
    int r;
    if (h==NULL)
        return NULL;
    r=(h->N+1)/2-1;
    h=partR(h, r);
    h->LEFT=balanceR(h->LEFT);
    h->RIGHT=balanceR(h->RIGHT);
    return h;
}

BSTquot_t partR(BSTquot_t h, int r) {
    int t;
    if (h->LEFT==NULL)
        t=0;
    else
        t=h->LEFT->N;
    if (t>r) {
        h->LEFT=partR(h->LEFT, r);
        h=rotR(h);
    }
    if (t<r) {
        h->RIGHT = partR(h->RIGHT, r-t-1);
        h=rotL(h);
    }
    return h;
}

BSTquot_t rotR(BSTquot_t node) {
    BSTquot_t x = node->LEFT;
    node->LEFT=x->RIGHT;
    x->RIGHT=node;
    x->N=node->N;
    node->N=1;
    node->N += (node->LEFT) ? node->LEFT->N : 0;
    node->N += (node->RIGHT) ? node->RIGHT->N : 0;
    return x;
}

BSTquot_t rotL(BSTquot_t node) {
    BSTquot_t x = node->RIGHT;
    node->RIGHT=x->LEFT;
    x->LEFT=node;
    x->N=node->N;
    node->N=1;
    node->N += (node->LEFT) ? node->LEFT->N : 0;
    node->N += (node->RIGHT) ? node->RIGHT->N : 0;
    return x;
}

void BSTprintIN(BSTquot_t node) {
    if (node==NULL)
        return;
    BSTprintIN(node->LEFT);
    printf("DATA: %d/%d/%d \tQuotazione: %f\n", node->quot.data.gg, node->quot.data.mm, node->quot.data.aa,  node->quot.QUOTgiornaliera);
    BSTprintIN(node->RIGHT);
}