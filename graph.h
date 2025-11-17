#ifndef GRAPH_H
#define GRAPH_H

#define MAX_V 100

typedef struct Node
{
    int v;
    struct Node *next;
} Node;

typedef struct
{
    Node *adj[MAX_V];
} Graph;

Graph *createGraph(void);
void freeGraph(Graph *g);

int addEdge(Graph *g, int from, int to);
int remEdge(Graph *g, int from, int to);
int hasEdge(Graph *g, int from, int to);

void topoSort(Graph *g, int ids[], int n, int res[], int *sz);

#endif