#ifndef _trafficSimulator_h
#define _trafficSimulator_h
#include "event.h"
#include "graph.h"
#include "priorityQueue.h"
#include "queue.h"
#include "road.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct TrafficData {
    // Optional TODO - Fill this struct in with the data needed to simulate traffic.  Suggested data:
    /* graph representing the road network */
    Graph *g;
    /* array of the roads of the graph in the sequence they were added to the graph */
    RoadData *roads;
    /* priority queue of events where the priority represents the time the event will occur */
    PriorityQueue *pq;
    /* track the number of cars still in the simulator */
    int numCars;
    /* track the longest number of time steps that any light takes to cycle around.  This is useful for detecting gridlock. */
    int steps;
    int maxTime; // highest stepTime
} TrafficData;

void printNames();

TrafficData *createTrafficData(char *name);

void trafficSimulator(TrafficData *pTrafficData);

void freeTrafficData(TrafficData *pTrafficData);

#endif
