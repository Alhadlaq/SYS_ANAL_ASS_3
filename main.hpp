/*----------------------------------------------------------------------------*
Filename: 		main.hpp
Purpose: 		This file contains the main structures used in the university.
Date created:	17/11/2017
Edits:
*----------------------------------------------------------------------------*/

#ifndef MAIN_HPP_
#define MAIN_HPP_

#define MAX_CLASSROOM	10
#define MAX_COURSES		20	
#define MAX_ARRAY		128
#define MAX_PRE_REQ		20
#define MAX_NAME		16
#define MAX_STUDENTS	1000
#define MAX_TERMS		20
#define MAX_ITERATIONS	MAX_COURSES
	
enum COURSE_TYPE {CORE, ELECTIVE};

/* classroom structure */
struct classroom
{
	int size;
};

struct course
{
	char name[MAX_NAME];
	int type;
	int number;
	int pre_req[MAX_PRE_REQ];
	int pre_req_num;
	int demand[MAX_TERMS][MAX_ITERATIONS];
	int registered[MAX_TERMS];
};

/* externals */
extern struct classroom classrooms[MAX_CLASSROOM];		//array of classrooms
extern struct course courses[MAX_COURSES];				//array of courses
extern int student_num;			// number of students enrolled in the university
extern int term_num;			// number of terms to simulate
extern int needed_c;			// number of core course needed to graduate
extern int smaple_term;			// sample term to be printed in the output
extern int sample_std;			// student index to be printed in the output
extern int room_num;			// number of classrooms availabe
extern int course_num;			// number of courses offered

#endif /* MAIN_HPP_ */