/**
 * This is the implementation of the CPU bound program that I will be testing.
 * It generates a sudo-random number using a modified mersenne twister algorithm that generates the numbers
 * every time it is called, instead of every 624th time that it is called. It will also take every two numbers that
 * are generated and treat them like a point in 2D space, and calulate their distance to the previous point.
 * The actual mersenne generation sequence is only moderately CPU intensive, but when it is called every time I believe that
 * it will be CPU intensive enough to work for this application, particularly when paired with the sqrt() function.
 *
 * Author: Sean Moss (semo0788@colorado.edu)
 */

#include "mersenne.h"
#include "sched_util.h"

#include <math.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

#define NUMBER_CALCULATIONS 10000

void run_calculations();

int main(int argc, char** argv)
{
	if (argc != 3)
	{
		printf("Usage: \".\\cpuprog <number_of_children> <sched_policy>\"");
		exit(EXIT_FAILURE);
	}
	int numChildren = atoi(argv[1]); /* Convert to number of children to spawn. */
	schedinfo policy;
	/* Set the policy */
	if (!schedutil_parse_policy(argv[2], &policy))
	{
		exit(EXIT_FAILURE);
	}
	if (!schedutil_implement_policy(&policy))
	{
		exit(EXIT_FAILURE);
	}
	
	printf("Spawning %d children, using the scheduler policy %s.\n", numChildren, argv[2]);

	/* Spawn the children processes */
	int i;
	for (i = 0; i < numChildren; ++i)
	{
		pid_t pid = fork();
		if (pid == 0) /* Child */
		{
			run_calculations();
			exit(EXIT_SUCCESS);
		}
	}

	/* Wait for all children to finish */
	pid_t status;
	do
	{
		pid_t done = wait(&status);
		if (done == -1 && errno != ECHILD)
		{
			printf("Error during wait()");
			abort();
		}
	}
	while (status > 0);

	return 0;
}

void run_calculations()
{
	srand(time(NULL));
	mersenne_initialize_generator(rand());

	int lastx = 0;
	int lasty = 0;
	int i;
	for (i = 0; i < NUMBER_CALCULATIONS; ++i)
	{
		int x = mersenne_rand();
		int y = mersenne_rand();
		int x2 = x - lastx;
		int y2 = y - lasty;
		x2 *= x2;
		y2 *= y2;
		sqrt(x2 + y2); /* Most of the CPU work will come from this call. */
		lastx = x;
		lasty = y;
	}
}
