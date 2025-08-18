#include <stdlib.h>
#include <stdio.h>
#ifndef INC_21_02_2023_A_H
#define INC_21_02_2023_A_H
//da , a ;
typedef struct inc_s{int T; int *tv; int P; int *pv; int **madj;} *inc;
typedef struct assign_s{int n; int *pvs; int resa;} assigns;
typedef struct sol_s{int T; assigns *assign; int N;} *sol;

inc leggifile(FILE *in);
sol getproposta(FILE *in );
int check(int **sin, inc G, sol ris);
void debugprint(int **sin, inc G);
void solve(inc G);
int calcolaresa(int **sin, inc G, int *sol);
void solve_r(int pos, int n, int* rr, int *tmpr, int *best, int curmax, int k, inc G );

//aggiunte funzioni free
void freesol(sol ris);
void freeinc(inc G);

#endif //INC_21_02_2023_A_H
