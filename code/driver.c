#include <stdlib.h>
#include <stdio.h>

#include "trafficSimulator.h"

int main( int argc, char *argv[] )
{
    int i;
    int numFiles = 7;
    /* defaultFilenames contains file names to be tested.  Set i-th int in enableTest to zero to disable the i-th test */
    char *defaultFilenames[] = {"./InputFiles/data-Trivial1.txt", 
								"./InputFiles/data-Trivial2.txt", 
								"./InputFiles/data-Simple.txt", 
								"./InputFiles/data-Merge.txt", 
								"./InputFiles/data-Complex.txt", 
								"./InputFiles/data-NearGridlock.txt", 
								"./InputFiles/data-Gridlock.txt" };
    int enableTest[]         = { 	1,  //data-Trivial1.txt
									1,  //data-Trivial2.txt
									1,  //data-Simple.txt
									1,  //data-Merge.txt
									1,  //data-Complex.txt
									1,  //data-NearGridlock.txt
									1 };//data-Gridlock.txt
		
		printNames( );

    if( argc==2 )  /* Usage: ./driver <filename> */
    {
        printf("\n\n------------------ START OF OUTPUT FOR %s --------------------\n\n", argv[1]);
		printf("\nREAD DATA FROM FILE\n\n");
        TrafficData* pTrafficData = createTrafficData( argv[1] );
        printf("\n\nSIMULATE THE ROAD NETWORK\n\n");
        trafficSimulator( pTrafficData );
        printf("\n\nFREE THE SIMULATION DATA\n\n");
        freeTrafficData( pTrafficData );
        printf("\n------------------ END OF OUTPUT FOR %s --------------------\n\n", argv[1]);
    }
    else
    {
        printf("\nRunning default test files: \n\n");

        for( i=0; i<numFiles; i++ )
        {
            if( enableTest[i]== 1 )//Only run tests with a 1 in enableTest
            {
                printf("\n\n------------------ START OF OUTPUT FOR %s --------------------\n\n", defaultFilenames[i]); 
				printf("\nREAD DATA FROM FILE\n\n");
                TrafficData* pTrafficData = createTrafficData( defaultFilenames[i] );
                printf("\n\nSIMULATE THE ROAD NETWORK\n\n");
                trafficSimulator( pTrafficData );
                printf("\n\nFREE THE SIMULATION DATA\n\n");
                freeTrafficData( pTrafficData );
                printf("\n------------------ END OF OUTPUT FOR %s --------------------\n\n", defaultFilenames[i]);
            }
            else
                printf("\n\n------------------ SKIPPED TESTING FOR %s --------------------\n\n", defaultFilenames[i]);
        }
    }
		
		printNames( );

    return 0;
}
