#include "trafficSimulator.h"

void printRoadData( int length, int from, int to, int greenStartTime, int greenEndTime, int lightCycleLength );
int max( int a, int b );

void printNames( )
{
    printf("\nThis solution was completed by:\n");
    printf("<Victor Olvera>\n");
    printf("<Nick Foley>\n\n");
}

/* createTrafficData
 * input: char* filename of file to read
 * output: TrafficData* which stores the data of this road network
 *
 * Create a new TrafficData variable and read in the traffic data from the file whose name is stored in char* filename
 */
TrafficData* createTrafficData( char* filename )
{
    /* open the file */
    FILE *pFile = fopen( filename, "r" );
    
    int vertices, edges, incoming, add, timeStep, to, from, i, j, k, numCars, destination, printRoad;
    /*intialize memory for struct*/
    fscanf( pFile, "%d %d", &vertices, &edges);
    TrafficData* traffic = (TrafficData*)malloc(sizeof(TrafficData));
    traffic->g = createGraph(vertices);
    traffic->roads = (RoadData*)malloc(sizeof(RoadData)*edges);
    traffic->pq = createPQ( );
	
    k = 0;/*keep track of the roads*/
    /*read in data for roads*/
    for(i = 0; i < vertices; i++){
      fscanf(pFile,"%d", &incoming); // amount of roads going to vertex i
      for(j = 0; j < incoming; j++){
	fscanf(pFile, "%d %d %d %d %d", &traffic->roads[k].from, &traffic->roads[k].roadlen, &traffic->roads[k].green, &traffic->roads[k].red, &traffic->roads[k].reset);
        traffic->roads[k].to = i;
        traffic->roads[k].q = createQueue();
        setEdge(traffic->g, traffic->roads[k].from, i , traffic->roads[k].roadlen );
        printRoadData( traffic->roads[k].roadlen, traffic->roads[k].from, traffic->roads[k].to, traffic->roads[k].green, traffic->roads[k].red, traffic->roads[k].reset );
        k++;
      }   
    }
    /*store number of roads*/
    traffic->roads->numRoad = edges;
    
    /*initializes the lightcounter to keep track of when to switch lights*/
    for(i = 0; i < edges;i++){
       traffic->roads[i].lightcounter = 0;
    }
	
    /*read in data for cars*/
    printf("Add the cars events:\n");
    fscanf(pFile, "%d", &add);
    traffic->maxTime = 0;
    
    for(i = 0; i<add; i++){
      fscanf(pFile, "%d %d %d %d", &from, &to, &timeStep,&numCars);
      Event* e = createAddCarEvent(timeStep,traffic->roads );
      e->pRoadData->cars = (Car**)malloc(sizeof(Car*)*numCars);
      printf("\nCreated event for time step %d on road from %d to %d.\n",timeStep,from,to);
      printf("Destinations of added cars: ");
      
      for(j = 0; j < numCars; j++){
        fscanf(pFile,"%d", &destination);
        e->pRoadData->cars[j] = createCar( timeStep, from, to,destination);
        enqueue(e->pCarQueue, e->pRoadData->cars[j] );
      	enqueueByPriority( traffic->pq, e, e->eventTimeStep );/*ADD_CAR_EVENT*/
        traffic->maxTime = max(traffic->maxTime, timeStep);
        
        if(j == numCars-1){
          printf("%d\n",e->pRoadData->cars[j]->destination);
        }
        else{
          printf("%d, ",e->pRoadData->cars[j]->destination);
        }
        
      }
      
    }

    /*read in printRoad time steps*/
    printf("\nAdd the roads events:\nTime steps: ");
    
    fscanf(pFile, "%d", &printRoad);
    for(i = 0; i < printRoad; i++){
      fscanf(pFile, "%d", &timeStep);
      Event* e = createPrintRoadsEvent(timeStep);
      enqueueByPriority( traffic->pq, e, e->eventTimeStep );/*PRINT_ROADS_EVENT*/
      traffic->maxTime = max(traffic->maxTime, timeStep);
      
      if(i == printRoad - 1){
        printf("%d\n",e->eventTimeStep);
      }
      else{
        printf("%d, ",e->eventTimeStep);
      }
      
    }
    
    /* HINTs:
     * Each road can be stored in a `RoadData` struct (see `road.h`).
     *
     * You'll want to store all of these `RoadData` structs in a single array.  This is important to track the order that
     * roads were added to your graph.  These are also the order they are processed in each time step.  You can store this
     * array in your TrafficData struct.
     *
     * You'll add edges to a graph to represent each road using `setEdge` (see `graph.c`).  The vertices of the graph
     * represent intersections.  The graph will do the work of finding shortest paths (see `getNextOnShortestPath` in graph.c
     * and the longest shortest path problem on Blackboard).
     *
     * It will also help to add your `RoadData` structs to your graph using `setEdgeData` (see `graph.c`).   You can then
     * retrieve that `RoadData` struct by calling `getEdgeData`.  This will be helpful for finding roads when cars pass
     * through intersections.
     *
     * Each event will be stored in an Event struct (see `event.h`).
     *
     * It's recommended to store all of the `Event` structs in a single priority queue (using time step as the priority).  This
     * allows you to quickly find the next event to execute by time step (see `enqueueByPriority`, `getFrontPriority`, and
     * `dequeuePQ`).
     *
     * Each car is stored in a Car struct (see `car.h`).
     */


    /* close file */
    fclose( pFile );

    return traffic; /* TODO: Replace this with your TrafficData pointer */
}

/* Print color coding for printRoadData (may not work outside of Linux environment) */
#define PRINT_COLOR false

/* provided code - DO NOT CHANGE
 * printRoadData
 * input: int length, int from, int to, int greenStartTime, int greenEndTime, int lightCycleLength
 * output: prints the given road
 *
 * Call this function to print out the road data you read in 
 */
void printRoadData( int length, int from, int to, int greenStartTime, int greenEndTime, int lightCycleLength )
{
	int i;
	char state='R';
	
	printf("Created road from %d to %d with length %d (green=%d; red=%d; reset=%d).\n", from, to, length, greenStartTime, greenEndTime, lightCycleLength );
	printf("Cycle number: ");
	for( i=0; i<25; i++ ){
		printf("%2d ", i );
	}
	printf("...\nLight state : ");	
	if(PRINT_COLOR) 
		printf("\033[0;31m");//Color = RED
	for( i=0; i<25; i++ ){	/* print example light cycle: */
		if( i%lightCycleLength==greenStartTime ){
			if(PRINT_COLOR) 
				printf("\033[0;32m");//Color = GREEN
			state = 'G';
		}
		if( i%lightCycleLength==greenEndTime ){
			if(PRINT_COLOR) 
				printf("\033[0;31m");//Color = RED
			state = 'R';
		}
		printf("%2c ", state );
	}
	if(PRINT_COLOR) 
		printf("\033[0m");//Reset color
	printf("...\n\n");
}

/* trafficSimulator
 * input: char* name of file to read
 * output: N/A
 *
 * Simulate the road network in the given TrafficData variable
 */
void trafficSimulator( TrafficData* pTrafficData )
{
    /* TODO: complete this function */
	int i;
    priorityQueueType PQ;
    Queue *waitingCars = createQueue();
    
    /* Loop until all events processed and either all cars reached destination or gridlock has occurred */
    while(!isEmptyPQ(pTrafficData->pq) /*&& either all cars reached destination || gridlock has occurred */){
      PQ = dequeuePQ( pTrafficData->pq );
      /* Update the state of every traffic */ 
      updateLight(pTrafficData->roads);
      for(i = 0; i < pTrafficData->maxTime ; i++){/* Loop on events associated with this time step */
        if(PQ->eventTimeStep == i){/*event is executed*/
          if(PQ->eventCode == ADD_CAR_EVENT){/*add cars into a waiting queue for the roads*/
            mergeQueues(waitingCars, PQ->pCarQueue);
            printf("STEP %d - ADD_CAR_EVENT - Cars enqueued on road from %d to %d\n\n", i, PQ->pRoadData->from, PQ->pRoadData->to);
           /* TODO doesnt print out correct road, need a way to get the correct road for the add car event FIXME*/
          }
          if(PQ->eventCode == PRINT_ROADS_EVENT){
            printf("STEP %d - PRINT_ROADS_EVENT - Current contents of the roads:\nCars on the road from %d to %d\n\n", i, pTrafficData->roads->from, pTrafficData->roads->to);
            /*doesnt print out correct road, need a way to get the correct road FIXME*/
            /*print out road queue*/
          }
          PQ = dequeuePQ( pTrafficData->pq );/* dequeue next event*/
        }
        /*simulate traffic*/
           
        /* First try to move cars through the next intersection */
        
        /* Second move waiting cars onto the end of each road if possible */

        /* Third move cars forward on every road (only those that haven't moved yet this time step) */
        
        /*if car reaches destination, print reach destination in I amount of steps then free car, maybe use a counter to see if all the cars have made their destination*/
      }
    
    }
    printf("Average number of time steps to the reach their destination is AVG.\nMaximum number of time steps to the reach their destination is MAX.");
  
}

/* freeTrafficData
 * input: TrafficData* pTrafficData
 * output: N/A
 *
 * Free the data in the TrafficData variable
 */
void freeTrafficData( TrafficData* pTrafficData )
{
  freeRoad(pTrafficData->roads);
  freeGraph(pTrafficData->g);
  freePQ(pTrafficData->pq);
  free(pTrafficData);
}

int max( int a, int b )
{
    if(a>b)
        return a;
    return b;
}

