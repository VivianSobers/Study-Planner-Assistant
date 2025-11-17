#ifndef PLANNER_H
#define PLANNER_H

#include "graph.h"

#define NAME_MAX 64
#define MAX_SUB 100

typedef struct
{
    int id;
    char name[NAME_MAX];
    int hrs;
    int pri;
    int act;
} Sub;

typedef struct
{
    Sub subs[MAX_SUB];
    int cnt;
    Graph *g;
} Plan;

Plan *initPlan(void);
void freePlan(Plan *p);

int addSub(Plan *p, const char *name, int hrs, int pri);
int updHrs(Plan *p, int id, int hrs);
int updPri(Plan *p, int id, int pri);
int remSub(Plan *p, int id);

int addDep(Plan *p, int from, int to);
int remDep(Plan *p, int from, int to);

void showPlan(const Plan *p);
void showBal(const Plan *p);
void showOrder(const Plan *p);

int findById(const Plan *p, int id);

#endif