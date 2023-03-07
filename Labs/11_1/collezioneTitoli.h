//
// Created by loren on 20/01/2020.
//

#ifndef INC_11_1_COLLEZIONETITOLI_H
#define INC_11_1_COLLEZIONETITOLI_H

#include "DataOra.h"
#include "quotazione.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAXC 20

typedef struct collTitoli* collTitle_t;
typedef struct titolo* title_t;

collTitle_t LISTinit();
///INSERIMENTO ORDINATO LISTA DI TITOLI
collTitle_t LISTinsTitle(collTitle_t c, char name[MAXC]);
title_t LISTnewnode(char name[MAXC], title_t next);
///INSERIMENTO LISTA DI TRANSAZIONI
collTitle_t LISTinsTrans(char name[MAXC], collTitle_t c, tempo_t dataora, int valore, int numero);
void addTransNumber(collTitle_t c, char name[MAXC], int nt);
///ACQUISIZIONE TITOLI
int checkTitolo(title_t list, char name[MAXC]);
collTitle_t TITLEfilesadd(collTitle_t c, char n1[MAXC], char n2[MAXC], char n3[MAXC]);
collTitle_t TITLEaddfromFile(collTitle_t c, char nomefile[MAXC]);

///CALCOLO QUOTAZIONI GIORNALIERE
void QUOTupdate(collTitle_t list);

void stampaLista(collTitle_t c);
void stampaTitolo(title_t t);

///FUNZIONI DI RICERCA
void ricercaTitolo(collTitle_t c, char str[MAXC]);
void ricercaQuotazione(collTitle_t c, char str[MAXC], data_t d);
void ricercaQuotazioniData(collTitle_t c, char str[MAXC], data_t d1, data_t d2);
void ricercaQuotazioniALL(collTitle_t c, char str[MAXC]);
void bilanciamento(collTitle_t c, char str[MAXC], int soglia);



#endif //INC_11_1_COLLEZIONETITOLI_H
