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
        }
    else if (road->cars[road->roadlen-1]/*if true we should be at the end of the array*/) {
        roadHopper(road->from, road->to);
        }
    else if (road->cars[k -1] != NULL && road->cars[k + 1] != NULL) {
        return;
        }

    }

/* Suggested TODO - Write a function to attempt to move the car at the first position on a given road
 * to the last position of a another given road.
 */
void roadHopper(Queue* leavingThisQueue, RoadData* road) {
    if (front(leavingThisQueue) == NULL) {
        return;
    }
    // Should we update the Car** array here too?

    Car* car = dequeue(leavingThisQueue);
    enqueue(road->q, car);
}

/* Suggested TODO - Write a function to attempt to move a car from the add car queue onto the end of this road.
 */
void queueToRoad(Queue* leavingThisQueue, RoadData* road) {
    if (front(leavingThisQueue) == NULL || road->cars[0] != NULL) {
        return;
    }
    // Could add error handling here
    // Should we update the Car** array here too?
    Car* car = dequeue(leavingThisQueue);
    enqueue(road->q, car);
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

/*prints all the roads*/
void printRoadsEvent(RoadData* road, int j){
  int i,k;
  for(i = 0; i < road->numRoad; i++){
    if(i == 0){
      printf("STEP %d - PRINT_ROADS_EVENT - Current contents of the roads:\n", j);
    }
     printf("\nCars on the road from %d to %d\n", road[i].from,road[i].to);
     for(k = 0; k < road[i].roadlen; k++){
       if(road[i].cars[k] != NULL){
        printf("%d ", road[i].cars[k]->destination);
       }
       else{
         printf("- ");
       }
     }
  }
  printf("\n");
}

