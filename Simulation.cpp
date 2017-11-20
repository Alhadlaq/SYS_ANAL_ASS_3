/*----------------------------------------------------------------------------*
Filename: 		Simulation.cpp
Purpose: 		This file contains the functions the runs the university
				simulation such as the undergrad office, registrar,
				building manager, and cash desk.
Date created:	17/11/2017
Edits:
*----------------------------------------------------------------------------*/

#include "main.hpp"
#include "Simulation.hpp"

int pool_sz;				// size of the mandatory pool
int mand_pool[MAX_COURSES];	// indexes of courses in mandatory pool
int elecs_in_pool;			// number of electives in the mandatory pool

void start_simulation (void)
{
	/*create the mandatory pool that the undergarduate office will use.
	 *This pool contains the core corses in addition to all the pre-
	 *requisits to these core courses*/
	create_mandatory_pool();
}

void create_mandatory_pool(void)
{
	int i;

	// for all the courses available
	for (i = 0; i < course_num; i++)
	{
		// if it is an elective, then skip it
		if (courses[i].type == ELECTIVE)
			continue;

		// if it is a core course
		// add it to the pool and all its pre-requisits
		add_to_pool(i);
	}
}

void add_to_pool(int course)
{
	int i;

	// add the course to the mandatory pool if it is not already added
	if (!is_mandatory(course))
	{
		mand_pool[pool_sz] = course;
		pool_sz++;
	}

	// keep track of the number of electives in the mandatory pool
	if (courses[course].type == ELECTIVE)
		elecs_in_pool++;

	// if the course has pre-requisits
	// for each pre-requisit, add to the pool
	for (i = 0; i < courses[course].pre_req_num; i++)
	{
		add_to_pool(courses[course].pre_req[i]);
	}
}

int is_mandatory(int course)
{
	int i;

	for (i = 0; i < pool_sz; i++)
	{
		if (course == mand_pool[i])
			return TRUE;
	}

	return FALSE;
}