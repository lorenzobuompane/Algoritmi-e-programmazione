#ifndef ST_H
#define ST_H

#define MAXC 30

typedef struct symboltable *ST;
typedef struct node *ID;

ST STinit(int maxN);
void STinsert(ST st,  char *elab, char *rete);

///     SEARCH BY NAME      ///
int STsearch(ST st, char *elab, char *rete);
int STsearchElab(ST st, char *elab);
int STsearchRete(ST st, char *rete);

///     SEARCH BY INDEX     ///
char *STsearchByIndex(ST st, int i);
char * STsearchElabByIndex(ST st, int i);
char * STsearchReteByIndex(ST st, int i);


int STreturnN(ST st);
char * STreturnStrByElabRete (char * elab, char * rete);

int * NodeIndexSort(ST st);


#endif

