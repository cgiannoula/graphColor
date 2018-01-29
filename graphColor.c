#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <math.h>
#include <sched.h>
#include <stdbool.h>
#include <float.h>
#include <limits.h>
#include <stdint.h>
#include <inttypes.h>

#include "graph.h"
#include "timers_lib.h"
#include "graphColor.h"

#define MAXFORBID 64 

/* Global vars */
graphColor_stats_t stats;
extern int64_t *color_arr;

/******************** SERIAL ********************/
static void setaffinity_oncpu(int cpu)
{
    cpu_set_t cpu_mask;
    int err;

    CPU_ZERO(&cpu_mask);
    CPU_SET(cpu, &cpu_mask);

    err = sched_setaffinity(0, sizeof(cpu_set_t), &cpu_mask);
    if (err) {
        perror("sched_setaffinity");
        exit(1);
    }
}

int64_t log_2(int64_t x){
    int64_t ret, mul=1;
    ret = 0;
    
    while(mul != x){
        mul *= 2;
        ret++;
    }

    return ret;
}

// A utility function used to print the solution
void printColor(struct Graph *graph)
{
    printf("Vertex   Color\n");
    for (int i = 0; i < graph->V; ++i)
        printf("%d \t\t %d\n", i, color_arr[i]);
}

void checkCorrectness(struct Graph *graph){

    printf("Checking correctnes ...\n");
    for(int i=0; i<graph->V; i++){
        if(color_arr[i] == -1){
            printf("ERROR uncolored\n");
            return;
        }
        for(int j=0; j<graph->array[i].neighboors; j++)
           if(color_arr[i] == color_arr[graph->array[i].head[j].dest] && i != graph->array[i].head[j].dest){
                printf("ERROR %d %d \n", i, graph->array[i].head[j].dest);
                return;
             }
    }

    printf("OK \n");
    return;
}

int ColorsUsed(struct Graph *graph){
    int *available;
    available = (int*) malloc((graph->maxDegree+1) * sizeof(int));
    
    for(int i=0; i<=graph->maxDegree; i++)
       available[i] = 0; 

    for(int u=0; u<graph->V; u++)
        available[color_arr[u]] = 1;

    int count=0;
    for(int i=0; i<=graph->maxDegree; i++){
        if(available[i] == 1)
            count++;
//        printf("i %d avail %d\n", i, available[i]);
    }
    
    return count;
}

// Initialize global statistics
void graphColor_stats_init(graphColor_stats_t *stats)
{
    stats->total_time = 0.0;
}

void graphColor_stats_print(graphColor_stats_t *stats)
{
	fprintf(stdout, "Extract time: \t\t %f\n", stats->total_time);
	fprintf(stdout, "\n\n\n");
}

void graphColor(struct Graph* graph)
{
//    timer_tt *timer = timer_init();
    int i, u, v;
    int V = graph->V;// Get the number of vertices in graph
    int maxDegree = graph->maxDegree;// Get the maxDegree 
    int64_t forbidden;
    int64_t offset;
    int64_t help;
    
        
    /*
     * Assign colors to vertices.
     */
    for(u=0; u<V; u++){
      int nb = graph->array[u].neighboors;

      offset = 0x0000000000000000;
      while(color_arr[u] == -1){
        forbidden = 0;
        for(i=0; i<nb; i++){
            v = graph->array[u].head[i].dest;

            /*
             * Set the forbidden colors as forbidden bits
             */
            if(color_arr[v] >= offset && color_arr[v] < offset + MAXFORBID){
                help = 1;
                help = help << (color_arr[v] - offset);
                forbidden = forbidden | help;
            }

        }

        /*
         * Find the first zero bit if exists
         * and set it as u's color.
         * If doesn't exist, repeat using
         * an increased(+64) colorRange.
         */

        /*
         * First zero bit:
         * 1. Invert the number
         * 2. Compute the two's complement of the inverted number (=initial number+1)
         * 3. AND the results of (1) and (2)
         * 4. Find the position by computing the binary logarithm of (3)
         */
        if(forbidden == 0xFFFFFFFFFFFFFFFF){
            offset += MAXFORBID;
            continue;
        }

        int64_t r1 = ~forbidden;
        int64_t r2 = forbidden + 1;
        int64_t clr = r1 & r2;      
        color_arr[u] = log_2(clr) + offset;

      }

    }
 
    return;
}


