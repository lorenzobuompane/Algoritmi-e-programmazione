#ifndef INC_28012020_ST_H
#define INC_28012020_ST_H

typedef struct symboltable *ST;

ST    STinit(int maxN);
void  STfree(ST st);
void  STinsert(ST st, char *str, int i);
int   STsearch(ST st, char *str);
char *STsearchByIndex(ST st, int i);

#endif //INC_28012020_ST_H
