/**
 * This is the header file for my custom implmentation of the mersenne twister algorithm used to generate pseudo-random numbers.
 * I am using this for my CPU-bound program because of the heavy CPU use that occurs when it generates a new list of pseduo-random numbers.
 * However, since it generates 623 rumbers per run, I will just force it to recalculate all 623 number every single time it is called, instead of
 * every 623rd time it is called.
 *
 * I adapted this algorithm for C from the pseudo-code algorithm found at:
 * http://en.wikipedia.org/wiki/Mersenne_Twister#Pseudocode
 *
 * Author: Sean Moss (semo0788@colorado.edu)
 */

/* 
 * Call this function at the beginning of each child program. It initializes the structures needed by the algorithm to work.
 * "seed" could just be time() or rand() from the c library. 
 */
void mersenne_initialize_generator(int seed);
/* 
 * This just extracts a random number. Normally this would only regenerate random numbers every 623rd call, but for my purposes in order to make
 * it as CPU intensive as possible, I will have it regenerate the numbers on every single call.
 */
int mersenne_rand(); 
