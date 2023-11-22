#ifndef _road_h
#define _road_h
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "car.h"
#include "queue.h"

typedef struct RoadData
{
    /* TODO - Add data associated with road.  Some suggested data: */
    /* length of this road */
    int roadlen;
    int numRoad;
    /* information used to record/update whether the light at the end of this road is green or red */
    int green;
    int red;
    int reset;
    int lightcounter;
    bool light; /*green == TRUE, red/reset == FALSE*/
    /* intersections this road starts from and moves to */
    int from; // origin
    int to;
    /* Each road should have an array to track cars currently driving on them.  The type of this array can be either `Car**` 
     * (array of car pointers) or `Car*` (array of cars) but the former may be easier to use since locations on the road can 
     * be set to `NULL` if no car is present.
     */
    Car**  cars;
    /* For each road it is recommended to have a `queue` of cars waiting to enter the simulated road system (see `queue.h` for 
     * the queues functions which have already been implemented for you).  Cars will be put into this queue only when an add 
     * car event occurs for this road.
     */
    Queue* q;
}  RoadData;
RoadData* createRoad(RoadData* road, int from, int roadlen, int green, int red, int reset);
void freeRoad(RoadData* road);
void roadHopper(Queue* leavingThisQueue, RoadData* road);
void queueToRoad(Queue* leavingThisQueue, RoadData* road);
void moveCars(RoadData* road, int k);
void updateLight(RoadData* road );

void printDestinations(RoadData* road, int j);
void printRoadsEvent(RoadData* road, int j);
#endif

