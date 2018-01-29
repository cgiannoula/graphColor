#ifndef __DIJKSTRAMT_H_
#define __DIJKSTRAMT_H_

#include <pthread.h>
#include <stdbool.h>

#include "graph.h"

typedef struct graphColor_stats_st{
    double total_time;
} graphColor_stats_t;

extern void printColor(struct Graph *graph);
extern void checkCorrectness(struct Graph *graph);
extern int ColorsUsed(struct Graph *graph);
extern void graphColor_stats_init(graphColor_stats_t *stats);
extern void graphColor_stats_print(graphColor_stats_t *stats);
extern void graphColor(struct Graph* graph);
#endif
