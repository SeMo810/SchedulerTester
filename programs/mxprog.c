/**
 * This is the implementation of the mixed io/cpu program that I will be testing.
 * It is just mixing the two other programs functionality into one.
 * This will use the distance calculations from cpuprog, and then write all of the results out to
 * a file, using the same names as the ioprog application.
 *
 * Author: Sean Moss (semo0788@colorado.edu)
 */

/* Include flag */
#define _GNU_SOURCE

#include "sched_util.h"
#include "mersenne.h"

#include <math.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define FILENAMELENGTH 64
#define OUTPUTDATACHUNK 4096
#define OUTPUTDATASIZE 16384
#define OUTPUTFILENAME "data/dataoutput%d.dat"

#define NUMBER_CALCULATIONS 4096

/* This will be increased by the parent program, and copied to the child program. This will allow children to uniquely name their files. */
int child_number = 0;

void run_process(float* floatBuffer);
float* run_calculations();

int main(int argc, char** argv)
{
	if (argc != 3)
        {
                printf("Usage: \"./mxprog <number_children> <scheduler_policy>\"");
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
                        float* fptr = run_calculations();
			run_process(fptr);
                        exit(EXIT_SUCCESS);
                }
                else
                {
                        ++child_number;
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

/* This will populate the buffer with 4096 floats from the distances between random points. */
float* run_calculations()
{
	float* floatBuffer = NULL;
	if (!(floatBuffer = (float*)malloc(NUMBER_CALCULATIONS * sizeof(float))))
	{
		printf("Could not allocate space for the float buffer.\n");
		exit(EXIT_FAILURE);
	}

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
                floatBuffer[i] = sqrt(x2 + y2); /* Most of the CPU work will come from this call. */
                lastx = x;
                lasty = y;
        }

	return floatBuffer;
}

/* This will write out the 4096 floats in 4 chunks of 1024 floats, or 4096 bytes each. */
void run_process(float* floatBuffer)
{
	int outputFD;
	char outputName[FILENAMELENGTH];
	
	sprintf(outputName, OUTPUTFILENAME, child_number); /* Create the output file name. */

	/* Open output file descriptor in write only mode */
        if ((outputFD = open(outputName, O_WRONLY | O_CREAT | O_TRUNC | O_SYNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH)) < 0)
        {
                printf("Failed to open output file %s.\n", outputName);
                exit(EXIT_FAILURE);
        }

	/* Take the distance calculations and write them out to the file. */
	char* transferBuffer = (char*)floatBuffer;
        ssize_t bytesWritten = 0;
	ssize_t amtWritten = 0;
	int writePass = 0;
        do
        {
                bytesWritten = write(outputFD, transferBuffer + (OUTPUTDATACHUNK * writePass), OUTPUTDATACHUNK);
                if (bytesWritten < 0)
                {
                        printf("Failed to write to the output file %s.\n", outputName);
                        exit(EXIT_FAILURE);
                }

		amtWritten += bytesWritten;
		++writePass;
        }
        while (amtWritten < OUTPUTDATASIZE);

	/* Free buffer and close files */
        free(transferBuffer);
        if (close(outputFD))
        {
                printf("Failed to close output file %s.\n", outputName);
                exit(EXIT_FAILURE);
        }
}
