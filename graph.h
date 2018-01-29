#ifndef __GRAPH_H_
#define __GRAPH_H_

#include <stdint.h>

typedef float weight_t;

struct AdjListNode
{
    int dest;
//    weight_t weight;
};
 
// A structure to represent an adjacency liat
struct AdjList
{
    int neighboors;
    struct AdjListNode *head;  // pointer to head node of list
    //int color;
};
 
// A structure to represent a graph. A graph is an array of adjacency lists.
// Size of array will be V (number of vertices in graph)
struct Graph
{
    unsigned int V;
    unsigned int edges;
    unsigned int maxDegree;
    struct AdjList* array;
};

int64_t *color_arr;

extern struct Graph* graph_read(const char *filename);
extern struct AdjListNode* newAdjListNode(int dest);
extern struct Graph* createGraph(int V);
extern void addEdge(struct Graph* graph, int src, int dest);
extern void find_avg_degree(struct Graph *graph);
#endif
