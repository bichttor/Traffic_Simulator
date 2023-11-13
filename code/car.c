#include "car.h"

/* Functions for creating and freeing cars. */

Car* createCar( int stepAdded, int origin, int next, int destination )
{
    Car* c = (Car*)malloc(sizeof(Car));

    c->stepAdded = stepAdded;
    c->origin = origin;
    c->next = next;
    c->destination = destination;

    c->moved = true;			/* Car moves on the time step it enters the simulation on */

    return c;
}

void freeCar( Car* c )
{
    free( c );
}
