/**
 * This is the implementation of the io-bound program that I will be testing.
 * It draws heavily on the rw.c file provided with the assignment, by copying the information from an input file
 * a certain number of times and putting it into the output file. It has just been modified so that each child process
 * gets it's own output file.
 *
 * Author: Sean Moss (semo0788@colorado.edu)
 * Heavily adapted from the rw.c file provided with the assigment.
 */

/* Include flag */
#define _GNU_SOURCE

#include "sched_util.h"

#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define INPUTFILENAME "data/datainput.dat"
#define OUTPUTFILENAME "data/dataoutput%d.dat"

/* This will be increased by the parent program, and copied to the child program. This will allow children to uniquely name their files. */
int child_number = 0;

void run_process();

int main(int argc, char** argv)
{
	if (argc != 3)
	{
		printf("Usage: \"./ioprog <number_children> <scheduler_policy>\"");
		exit(EXIT_FAILURE);
	}
	int numChildren = atoi(argv[1]);
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

	/* Spawn the child processes */
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
        while (1)
        {
                pid_t status;
                pid_t done = wait(&status);
                if (done == -1)
                {
                        if (errno == ECHILD)
                        {
                                break; /* No more child processes */
                        }
                        else
                        {
                                printf("Waiting for child failed.\n");
                                abort();
                        }
                }
                else
                {
                        if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
                        {
                                printf("Waiting for pid %d failed.\n", done);
                                abort();
                        }
                }
        }


        return 0;
}

void run_process()
{
	
}
