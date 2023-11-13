#ifndef _event_h
#define _event_h
#include <stdbool.h>

#include "queue.h"
#include "road.h"

typedef enum eventType { ADD_CAR_EVENT, PRINT_ROADS_EVENT } eventType;

typedef struct Event
{
    eventType eventCode;    /* Type of event */
    int eventTimeStep;      /* Time step associated with this event */

    /* PRINT_ROADS_EVENT */
    //No additional data needed

    /* ADD_CAR_EVENT */
    Queue *pCarQueue;       /* Queue associated with the event */
    RoadData *pRoadData;    /* RoadData associated with the event (use getEdgeData from graph.c to retrieve this) */

}  Event;

Event* createPrintRoadsEvent( int timeStep );
Event* createAddCarEvent( int timeStep, RoadData *pRoadData );
void freeEvent( Event* e );

#endif
