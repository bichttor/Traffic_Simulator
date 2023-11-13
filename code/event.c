#include "event.h"

/* Functions for creating and freeing events. */

Event* createPrintRoadsEvent( int timeStep )
{
    Event* e = (Event*)malloc(sizeof(Event));

    e->eventTimeStep = timeStep;
    e->eventCode = PRINT_ROADS_EVENT;

    return e;
}

Event* createAddCarEvent( int timeStep, RoadData *pRoadData )
{
    Event* e = (Event*)malloc(sizeof(Event));

    e->eventTimeStep = timeStep;
    e->eventCode = ADD_CAR_EVENT;
    e->pCarQueue = createQueue();
    e->pRoadData = pRoadData;

    return e;
}

void freeEvent( Event* e )
{
    if( e->eventCode == ADD_CAR_EVENT )
        freeQueue( e->pCarQueue );
    free( e );
}
