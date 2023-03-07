//
// Created by loren on 20/01/2020.
//

#include "DataOra.h"

/**
 * CONFRONTO DATA
 * @param d1 : date 1
 * @param d2 : date 2
 * @return
 * 1 : d1 > d2 (d1 più recente)
 * 0 : d1 == d2
 * -1: d1 < d2 (d1 più lontana)
 */
int DATEcmp(data_t d1, data_t d2) {
    if (d1.aa>d2.aa)
        return 1;
    else if (d1.aa==d2.aa) {
        if (d1.mm > d2.mm)
            return 1;
        else if (d1.mm==d2.mm) {
            if (d1.gg > d2.gg)
                return 1;
            else if (d1.gg==d2.gg)
                return 0;
        }
    }
    return -1;
}

/**
 * CONFRONTO ORA
 * @param h1
 * @param h2
 * @return
 * 1 : h1 > h2 (h1 più recente)
 * 0 : h1 == h2
 * 1 : h1 < h2 (h1 più lontana)
 */
int HOURcmp(ora_t h1, ora_t h2) {
    if (h1.hh>h2.hh)
        return 1;
    else if (h1.hh==h2.hh) {
        if (h1.mm>h2.mm)
            return 1;
        else if (h1.mm==h2.mm)
            return 0;
    }
    return -1;
}

/**
 * CONFRONTO DATA ORA
 * @param t1
 * @param t2
 * @return
 * 1 : t1 > t2 (t1 più recente)
 * 0 : t1 == t2
 * 1 : t1 < t2 (t1 più lontana)
 */
int DATEHOURcmp(tempo_t t1, tempo_t t2) {
    int d = DATEcmp(t1.data, t2.data);
    int h = HOURcmp(t1.ora, t2.ora);
    if (d==1)
        return 1;
    if (d==-1)
        return -1;
    if (h==1)
        return 1;
    if (h==-1)
        return -1;
    return 0;
}