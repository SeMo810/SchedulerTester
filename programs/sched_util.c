/**
 * This is the implementation of my sceduler policy util functions.
 *
 * Author: Sean Moss (semo0788@colorado.edu)
 */

#include "sched_util.h"

int schedutil_parse_policy(const char* arg, schedinfo *param)
{
	int policy;
	/* Parse the policy */
	if (!strcmp(arg, "SCHED_OTHER"))
        {
                policy = SCHED_OTHER;
        }
        else if (!strcmp(arg, "SCHED_FIFO"))
        {
                policy = SCHED_FIFO;
        }
        else if (!strcmp(arg, "SCHED_RR"))
        {
                policy = SCHED_RR;
        }
        else
        {
                printf("SCHED_UTIL: An invalid scheduler policy was provided: %s.\n", arg);
               	return 0;
        }

	param->param.sched_priority = sched_get_priority_max(policy);
	param->policy = policy;
	return 1;
}

int schedutil_implement_policy(schedinfo *param)
{
	if (sched_setscheduler(0, param->policy, &(param->param)))
	{
		printf("SCHED_UTIL: Failed to switch to new scheduler policy.\n");
		return 0;
	}
	return 1;
}
