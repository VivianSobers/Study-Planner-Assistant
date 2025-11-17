#include <stdlib.h>
#include "graph.h"

Graph *createGraph(void)
{
    Graph *g = malloc(sizeof(Graph));
    if (!g) return NULL;
    
    for (int i = 0; i < MAX_V; i++)
    {
        g->adj[i] = NULL;
    }
    
    return g;
}

void freeGraph(Graph *g)
{
    if (!g) return;
    
    for (int i = 0; i < MAX_V; i++)
    {
        Node *c = g->adj[i];
        while (c)
        {
            Node *t = c;
            c = c->next;
            free(t);
        }
    }
    
    free(g);
}

int hasEdge(Graph *g, int from, int to)
{
    if (!g || from < 0 || to < 0 || from >= MAX_V || to >= MAX_V)
        return 0;
    
    Node *c = g->adj[from];
    while (c)
    {
        if (c->v == to) return 1;
        c = c->next;
    }
    return 0;
}

int addEdge(Graph *g, int from, int to)
{
    if (!g || from < 0 || to < 0 || from >= MAX_V || to >= MAX_V)
        return -1;
    if (from == to) return -1;
    
    if (hasEdge(g, from, to)) return 0;
    
    Node *n = malloc(sizeof(Node));
    if (!n) return -1;
    
    n->v = to;
    n->next = g->adj[from];
    g->adj[from] = n;
    
    return 0;
}

int remEdge(Graph *g, int from, int to)
{
    if (!g || from < 0 || to < 0 || from >= MAX_V)
        return -1;
    
    Node *c = g->adj[from];
    Node *pr = NULL;
    
    while (c)
    {
        if (c->v == to)
        {
            if (pr)
                pr->next = c->next;
            else
                g->adj[from] = c->next;
            free(c);
            return 0;
        }
        pr = c;
        c = c->next;
    }
    
    return -1;
}

void topoSort(Graph *g, int ids[], int n, int res[], int *sz)
{
    if (!g || !ids || !res || !sz)
    {
        if (sz) *sz = 0;
        return;
    }
    
    int ind[MAX_V] = {0};
    int vis[MAX_V] = {0};
    
    for (int i = 0; i < n; i++)
    {
        int u = ids[i];
        Node *c = g->adj[u];
        while (c)
        {
            for (int j = 0; j < n; j++)
            {
                if (ids[j] == c->v)
                {
                    ind[c->v]++;
                    break;
                }
            }
            c = c->next;
        }
    }
    
    int idx = 0;
    int proc = 0;
    
    while (proc < n)
    {
        int found = 0;
        for (int i = 0; i < n; i++)
        {
            int id = ids[i];
            if (!vis[id] && ind[id] == 0)
            {
                res[idx++] = id;
                vis[id] = 1;
                found = 1;
                proc++;
                
                Node *c = g->adj[id];
                while (c)
                {
                    ind[c->v]--;
                    c = c->next;
                }
                break;
            }
        }
        
        if (!found)
        {
            *sz = -1;
            return;
        }
    }
    
    *sz = idx;
}