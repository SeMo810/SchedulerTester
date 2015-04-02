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

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <time.h>

int main(int argc, char** argv)
{
	srand(time(NULL));
	mersenne_initialize_generator(rand());
	int r = mersenne_rand();
	printf("The random number was: %d.\n", r);
	return 0;
}
