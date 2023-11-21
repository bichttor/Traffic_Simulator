#include "road.h"

#include "trafficSimulator.h"

/* Suggested TODO - Write a function to create road.
 */
RoadData* createRoad(RoadData* road, int from, int roadlen, int green, int red, int reset){
    road->from = from;
    road->roadlen = roadlen;
    road->green = green;
    road->red = red;
    road->reset = reset;
    return road;
}
/* Suggested TODO - Write a function to free a road.
 */
void freeRoad(RoadData* road){
    /*create loop that frees all cars left in road*/

    free(road);
}

/* Suggested TODO - Write a function that attempts to move the cars on a given road forward (if space ahead of them was empty).
*/
void moveCars(RoadData* road, int k/*k is the current position the car is in*/) {
    /* Car position might be passed from Event*/
    if (road->cars[k] != NULL && road->cars[k + 1] == NULL) {
        road->cars[k + 1] = road->cars[k]; // moves the car forward
        road->cars[k] = NULL; // sets "current" slot to NULL
        }else if (road->cars[road->roadlen - 1]) {
 /* this should check if car is at the end of the road.
   probably call the function that changes intersections.
  */
     }else if (road->cars[k -1] != NULL && road->cars[k + 1] != NULL) {
  /* car cannot move forward */
     }

    }

/* Suggested TODO - Write a function to attempt to move the car at the first position on a given road
 * to the last position of a another given road.
 */

/* Suggested TODO - Write a function to attempt to move a car from the add car queue onto the end of this road.
 */
void queueToRoad(Queue* leavingThisQueue, RoadData* road) {
    CarData* car = dequeue(leavingThisQueue);
    enqueue(road->queue, car);
}


/* Suggested TODO - Write a function to update the current state of the traffic light based on the current cycle.
 */
void updateLight(RoadData* road) {
  int i;
  for(i = 0; i < road->numRoad;i++){
    road[i].lightcounter++;
    if(road[i].lightcounter > road[i].reset){/*reset road light*/
      road[i].lightcounter = 0;
    }
    else if(road[i].lightcounter != road[i].red &&road[i].lightcounter != road[i].reset){/*road is green*/
      road[i].light = true;
    }
    else{/*road is red*/
      road[i].light = false;   
    }
  }
  
}
/* Suggested TODO - Write a function to print the destinations of the cars on the road
 */
void printDestinations(RoadData* road, int j) {
 int origin = road->cars[j]->origin;
 int dest = road->cars[j]->destination;

 //printf("Test Test Test From %d to %d\n", origin, dest);
 printf("Cars on the road from %d to %d: \n", origin,dest);
}
