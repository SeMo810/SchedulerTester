/**
 * This is the code/implementation file for my custom implmentation of the mersenne twister algorithm used to generate pseudo-random numbers.
 * I am using this for my CPU-bound program because of the heavy CPU use that occurs when it generates a new list of pseduo-random numbers.
 * However, since it generates 623 rumbers per run, I will just force it to recalculate all 623 number every single time it is called, instead of
 * every 623rd time it is called.
 *
 * I adapted this algorithm for C from the pseudo-code algorithm found at:
 * http://en.wikipedia.org/wiki/Mersenne_Twister#Pseudocode
 *
 * Author: Sean Moss (semo0788@colorado.edu)
 */

#include "mersenne.h"

#define MERSENNE_ARRAY_LENGTH 624
#define LOWEST_BITS_MASK ((long long)(0x00000000FFFFFFFF))

/* The state array of the generator. */
int state[MERSENNE_ARRAY_LENGTH] = { 0x00 };
/* The current index of the state array. */
int state_index = 0;

void mersenne_initialize_generator(int seed)
{
	state_index = 0;
	state[0] = seed;
	int i;
	for (i = 1; i < MERSENNE_ARRAY_LENGTH; ++i)
	{
		state[i] = (int)(1812433253 * (state[i-1] ^ (state[i-1] >> 30))); 
	}
}

void generate_numbers()
{
	int i;
	for (i = 0; i < MERSENNE_ARRAY_LENGTH; ++i)
	{
		int y = (state[i] & 0x80000000) + (state[(i+1)%624] & 0x7FFFFFFF);
		state[i] = state[(i+397)%624] ^ (y >> 1);
		if ((y & 1) > 0)
		{
			state[i] ^= 0x9908B0DF;
		}
	}
}

int mersenne_rand()
{
	generate_numbers();
	
	int y = state[state_index];
	y ^= (y >> 11);
	y ^= ((y << 7) & 0x9D2C5680);
	y ^= ((y << 15) & 0xEFC60000);
	y ^= (y >> 18);

	state_index += 1;
	state_index %= 624;
	return y;
}
