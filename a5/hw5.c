#include <stdio.h>         // for printf()
#include <pthread.h>       // for pthread_xxx() routines
#include "mcsim.h"

double gcount;    // global counter -- a double to handle large sums (billions+)
long numits;      // global variable for number of iterations (see step 3 below)

int main( int argc, char** argv ) {

	gcount = 0;

	/*

	---------------------------------------------------------------------
	Step-by-Step procedure for Monte carlo simulator to estimate PI
	---------------------------------------------------------------------
	1. Create the following variables:
		- pointer to an array of pthread structures
		- counting variables for loops
		- thread id
		- exit status of joined thread
		- number of threads to run
		- maximum number of threads (hint: rlimit)
		- nanosecond start and stop time structs (hint: timespec)
	2. Get number of threads input by user from argv[1]
	3. Get number of iterations input by user from argv[2]
	4. Get the maximum number of threads the OS can create (hint: getrlimit function)
	5. If are number of threads > maximum OS threads then goto 14, else goto step 6
	6. Allocate an array of pthread structures using number of threads input by user (see step 2)
	7. Get start time of simulation and store in time struct
	8. Use a loop to create a pthread for each index position in pthread array (created in step 5), if an error occurs during thread creation - exit simulation program immediately (hint: pthread_create function)
	9. Use a loop to join each pthread in created in the pthread array, if an error occurs during thread join operation - exit simulation program immediately (hint: pthread_join function)
	10. Get stop time of simulation and store in time struct
	11. Print out the:
		- value of PI using 6 decimal places
		- value stored in global variable gcount using 0 decimal places
		- time in seconds required to run the simulation using 4 decimal places (hint: mydifftime function)
	12. Free memory allocated for pthread array
	13. Call pthread terminate function (hint: pthread_exit function)
	14. exit simulation program

	---------------------------------------------------------------------
	Example input and output of Monte carlo simulator to estimate PI
	---------------------------------------------------------------------

		# ./hw5 300 100		// i.e. run simulatior using 300 threads and 100 iterations

	  	monte carlo value of PI = 3.141200
	  	value of count = 23559
	  	time in seconds = 0.0761

	*/
	
	pthread_t *thread_struct;
	
	int i, thread = 0, status, numOfThreads, iterations, result;
	double time;
	struct rlimit maxThreads;
	struct timespec start, stop;
	
	if(argc < 3){
		printf("Error in input.\n");
		exit(1);
	}
	
	numOfThreads = argv[1];
	iterations = argv[2];
	
	getrlimit(RLIMIT_NPROC, &maxThreads);
	
	if(numOfThreads > maxThreads.rlim_cur){
		printf("Max number of threads exceeded.\n");
		exit(1);
	}
	
	thread_struct = (pthread_t*) malloc(sizeof(pthread_t) * numOfThreads);
	clock_gettime(CLOCK_REALTIME, &start);
	
	for(i = 0; i < numOfThreads; i++){
	
		result = pthread_create(&(thread[i]), NULL, &th_routine, (void*) thread++);
		
		if(result != 0){
			printf("Error in thread %d.\n", thread);
			exit(1);
		}
	}
	
	for(i = 0; i < numOfThreads; i++){
		
		result = pthread_join(thread[i], NULL);
		
		if (result != 0){
			printf("Error joining thread %d.\n", thread)
			exit(1);
		}
	}
	
	clock_gettime(CLOCK_REALTIME, &stop);
	elapsed = mydifftime(&start, &stop);
	
	printf("monte carlo value of pi: %.6f\n", (4 * gcount/(iterations * numOfThreads)));
	printf("value of count: %.0f\n", gcount);
	printf("time in seconds: %.4f\n", time / 1000000000);

	return 0;

} // end main function
