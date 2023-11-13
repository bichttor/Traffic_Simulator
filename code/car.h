#ifndef _car_h
#define _car_h

#include <stdlib.h>
#include <stdbool.h>

typedef struct Car
{
    int stepAdded;      /* The time step associated with the addCar event that added this car */
    int origin;         /* The intersection this car started from */
    int next;           /* The intersection this car is driving toward currently */
    int destination;    /* The intersection this car wants to ultimately stop at */

    bool moved;         /* Track whether a car has moved during this time step (remember to reset to false before next time step) */
}  Car;

Car* createCar( int stepAdded, int origin, int next, int destination );
void freeCar( Car* c );

#endif
