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
    int i,j;
    for(i = 0; i < road->numRoad; i++){/*goes through all the roads*/
      for(j = 0; j < road[i].roadlen; j++){/*free all cars left in road*/
        if(road[i].cars[j] != NULL){
          freeCar(road[i].cars[j]); 
        }
      }
      
      freeQueue(road[i].q);
      free(road[i].cars);
    }
    free(road);
    
}

/* Suggested TODO - Write a function that attempts to move the cars on a given road forward (if space ahead of them was empty).
*/
void moveCars(RoadData* road) {
    int i,j;
      for(i = 0; i < road->numRoad; i++){/*goes through all the roads*/
        for(j = road[i].roadlen-1; j >= 0; j--){/*starts from the "end" of the road*/
          if (road[i].cars[j] != NULL && road[i].cars[j - 1] == NULL && road[i].cars[j]->moved == true){/*checks to see if position contains car and the next position is NULL and car hasnt moved*/
            road[i].cars[j]->moved = false;/*has moved*/
            road[i].cars[j - 1] = road[i].cars[j];
            road[i].cars[j] = NULL;  
          }
        }
      }
}

/* Suggested TODO - Write a function to attempt to move the car at the first position on a given road
 * to the last position of a another given road.
 */
void roadHopper(RoadData* road) {
   int i;
    for(i = 0; i < road->numRoad; i++){
      if(road[i].cars[0] != NULL){
        /*maybe get shortest distance to find next node then enqueue the car into that node, if light is green
        and the spot is NULL then add car to the road else leave in the queue*/
      }
    }
}

/* Suggested TODO - Write a function to attempt to move a car from the add car queue onto the end of this road.
 */
void queueToRoad(RoadData* road) {
      int i;
      queueType qt; /*car*/
      for(i = 0; i < road->numRoad; i++){ 
        if(road[i].cars[road[i].roadlen-1] == NULL && !isEmpty(road[i].q)){/*checks if "end" and queue are valid , dequeues from queue and places are at the "end"*/
          qt = dequeue(road[i].q);
          road[i].cars[road[i].roadlen-1] = qt; 
          qt->moved = false;/*has moved*/
        }
      }
      
}


/* Suggested TODO - Write a function to update the current state of the traffic light based on the current cycle.
 */
void updateLight(RoadData* road, int j) {
 int i;
  for(i = 0; i < road->numRoad;i++){
    if(j%road[i].reset == road[i].green){
    road[i].light = true;
    }
    if(j%road[i].reset == road[i].red){
    road[i].light = false;
      }
    }
 
}

/*resets moves for next timestep*/
void resetCar(RoadData* road ){
  int i,j;
  for(i = 0; i < road->numRoad; i++){/*goes through all the roads*/
    for(j = 0; j < road[i].roadlen; j++){/*free all cars left in road*/
      if(road[i].cars[j] != NULL){
        road[i].cars[j]->moved = true;/*hasnt moved*/
      }
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
      printf("Cars on the road from %d to %d\n", road[i].from,road[i].to);

      for(k = 0; k < road[i].roadlen; k++){
       if(road[i].cars[k] != NULL){
        printf("%d ", road[i].cars[k]->destination);
       }
       else{
         printf("- ");
       }
     }
      if(road[i].light == true){
       printf("(GREEN LIGHT)\n");
     }
    else if(road[i].light == false) {
      printf("(RED LIGHT)\n");
    }
     else{
       printf("(??? LIGHT)\n");
     }
  }
  printf("\n");
}

