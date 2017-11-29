/*----------------------------------------------------------------------------*
Filename: 		Simulation.hpp
Purpose: 		This file contains function prototypes and helping structures
				for the university simulation.
Date created:	17/11/2017
Edits:
*----------------------------------------------------------------------------*/

#ifndef SIMULATION_HPP_
#define SIMULATION_HPP_

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
int no_demand(void);
int find_room(int demand);
int no_available_courses(void);
int no_available_rooms(void);
void print_term_table(FILE *out);
void building_manager(void);
void remove_course(int student, int room, int slot, int course);
void print_reports();
void printf_graduated_students(FILE *out);
void print_tuition (FILE *out);
void print_sample_std (FILE *out);
void university_time_table(FILE *out);
void courses_taken_by_students (FILE *out);

#endif
