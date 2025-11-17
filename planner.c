#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "planner.h"
Plan *initPlan(void)
{
    Plan *p = malloc(sizeof(Plan));
    if (!p) 
        return NULL;
    p->g = createGraph();
    if (!p->g)
    {
        free(p);
        return NULL;
    }
    p->cnt = 0;
    for (int i = 0; i < MAX_SUB; i++)
        p->subs[i].act = 0;
    return p;
}
void freePlan(Plan *p)
{
    if (!p) return;
    freeGraph(p->g);
    free(p);
}

int findById(const Plan *p, int id)
{
    if (!p) return -1;
    for (int i = 0; i < MAX_SUB; i++)
    {
        if (p->subs[i].act && p->subs[i].id == id)
            return i;
    }
    return -1;
}

int addSub(Plan *p, const char *name, int hrs, int pri)
{
    if (!p || !name || hrs < 0 || pri < 0) 
        return -1;
    if (strlen(name) == 0 || strlen(name) >= NAME_MAX) 
        return -1;
    
    for (int i = 0; i < MAX_SUB; i++)
    {
        if (p->subs[i].act && strcmp(p->subs[i].name, name) == 0)
            return -1;
    }
    if (p->cnt >= MAX_SUB) 
        return -1;
    int slot = -1;
    for (int i = 0; i < MAX_SUB; i++)
    {
        if (!p->subs[i].act)
        {
            slot = i;
            break;
        }
    }
    if (slot == -1) return -1;
    p->subs[slot].id = slot;
    strcpy(p->subs[slot].name, name);
    p->subs[slot].name[NAME_MAX - 1] = '\0';
    p->subs[slot].hrs = hrs;
    p->subs[slot].pri = pri;
    p->subs[slot].act = 1;
    p->cnt++;
    return slot;
}
int updHrs(Plan *p, int id, int hrs)
{
    if (!p || hrs < 0) 
        return -1;
    int idx = findById(p, id);
    if (idx < 0) 
        return -1;
    p->subs[idx].hrs = hrs;
    return 0;
}

int updPri(Plan *p, int id, int pri)
{
    if (!p || pri < 0) 
        return -1;
    int idx = findById(p, id);
    if (idx < 0) 
        return -1;
    p->subs[idx].pri = pri;
    return 0;
}

int remSub(Plan *p, int id)
{
    if (!p)
        return -1;
    int idx = findById(p, id);
    if (idx < 0) 
        return -1;
    p->subs[idx].act = 0;
    p->cnt--;
    for (int i = 0; i < MAX_V; i++)
    {
        remEdge(p->g, i, id);
        remEdge(p->g, id, i);
    }
    return 0;
}

int addDep(Plan *p, int from, int to)
{
    if (!p) 
        return -1;
    if (findById(p, from) < 0) 
        return -1;
    if (findById(p, to) < 0) 
        return -1;
    return addEdge(p->g, from, to);
}

int remDep(Plan *p, int from, int to)
{
    if (!p) 
        return -1;
    return remEdge(p->g, from, to);
}

void showPlan(const Plan *p)
{
    if (!p) 
        return;
    printf("\n========== Study Plan ==========\n");
    printf("Total subjects: %d\n\n", p->cnt);
    if (p->cnt == 0)
    {
        printf("No subjects added yet.\n");
        return;
    }
    for (int i = 0; i < MAX_SUB; i++)
    {
        if (p->subs[i].act)
        {
            Sub s = p->subs[i];
            printf("ID: %d | %s\n", s.id, s.name);
            printf("  Hours: %d | Priority: %d\n", s.hrs, s.pri);
            printf("  --------------------------------\n");
        }
    }
}

void showBal(const Plan *p)
{
    if (!p || p->cnt == 0)
    {
        printf("No subjects to analyze.\n");
        return;
    }
    int tot = 0;
    for (int i = 0; i < MAX_SUB; i++)
    {
        if (p->subs[i].act)
            tot += p->subs[i].hrs;
    }
    double avg = (double)tot / p->cnt;
    printf("\n========== Balance Analysis ==========\n");
    printf("Total hours: %d\n", tot);
    printf("Average per subject: %.2f hours\n\n", avg);
    
    for (int i = 0; i < MAX_SUB; i++)
    {
        if (p->subs[i].act)
        {
            Sub s = p->subs[i];
            printf("%s (ID %d): %d hours - ", s.name, s.id, s.hrs);
            
            if (s.hrs > avg * 1.3)
                printf("Over-allocated. Consider reducing.\n");
            else if (s.hrs < avg * 0.7)
                printf("Under-allocated. Consider adding more time.\n");
            else
                printf("Well-balanced.\n");
        }
    }
}

void showOrder(const Plan *p)
{
    if (!p || p->cnt == 0)
    {
        printf("No subjects to order.\n");
        return;
    }
    int ids[MAX_SUB];
    int n = 0;
    for (int i = 0; i < MAX_SUB; i++)
    {
        if (p->subs[i].act)
            ids[n++] = p->subs[i].id;
    }
    
    int res[MAX_SUB];
    int sz = 0;
    topoSort(p->g, ids, n, res, &sz);
    
    if (sz == -1)
    {
        printf("\nCannot create study order: Dependency cycle detected!\n");
        printf("Please check your prerequisites for circular dependencies.\n");
        return;
    }
    printf("\n========== Suggested Study Order ==========\n");
    printf("(Respecting all dependencies)\n\n");
    
    for (int i = 0; i < sz; i++)
    {
        int id = res[i];
        int idx = findById(p, id);
        
        if (idx >= 0)
        {
            Sub s = p->subs[idx];
            printf("%d. %s (ID %d) - %d hours, Priority %d\n",
                   i + 1, s.name, s.id, s.hrs, s.pri);
        }
    }
}