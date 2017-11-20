/*----------------------------------------------------------------------------*
Filename: 		Simulation.hpp
Purpose: 		This file contains function prototypes and helping structures
				for the university simulation.
Date created:	17/11/2017
Edits:
*----------------------------------------------------------------------------*/

#ifndef SIMULATION_HPP_
#define SIMULATION_HPP_

#define TRUE	1
#define FALSE	0

/*function prototypes*/
void start_simulation(void);
void create_mandatory_pool(void);
void add_to_pool(int course);
int is_mandatory(int course);

#endif