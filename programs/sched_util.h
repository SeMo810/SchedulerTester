/**
 * This is the header file for the util program that I am writing to allow for the parsing and setting of
 * scheduler policies in a program.
 *
 * Author: Sean Moss (semo0788@colorado.edu)
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sched.h>

/* Contains the scheduling info */
typedef struct __schedinfo
{
	struct sched_param param;
	int policy;
} schedinfo;


/* Parse a string to get the policy. Accepts SCHED_OTHER, SCHED_FIFO, SCHED_RR. */
int schedutil_parse_policy(const char* arg, schedinfo *param);
/* Activate a scheduler policy */
int schedutil_implement_policy(schedinfo *param);
