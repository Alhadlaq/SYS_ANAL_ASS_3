/*----------------------------------------------------------------------------*
Filename: 		Simulation.hpp
Purpose: 		This file contains function prototypes and helping structures
				for the university simulation.
Date created:	17/11/2017
Edits:
*----------------------------------------------------------------------------*/

#ifndef SIMULATION_HPP_
#define SIMULATION_HPP_

#define TRUE		1
#define FALSE		0

#define NO_COURSE	-1
#define FULL_LOAD	2

struct iteration
{
	int course;
	int selected;
};

struct student
{
	int taken_courses[MAX_COURSES];	// indexes to the taken courses
	int taken_num;					// number of taken courses
	int elects_taken;				// number of electives taken
	/*table of all the suggestions for the student and the registrations*/
	struct iteration term_tbl[MAX_TERMS][MAX_ITERATIONS];
};

/*function prototypes*/
void start_simulation(void);
void create_mandatory_pool(void);
void add_to_pool(int course);
int is_mandatory(int course);
void advise_students(void);
int is_taken(int course, int student);
int pre_reqs_taken(int course, int student);
void register_course(void);
int taking_full_load(int student, int term);

#endif