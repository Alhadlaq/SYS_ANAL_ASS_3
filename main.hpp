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
#define TIME_SLOT_NUM	2
#define MAX_ITERATIONS	MAX_COURSES
#define NO_COURSE		-1
#define FULL_LOAD		2			// max number of courses for a student in a term
#define MAX_ALLOC		2			// amx number of courses in a classroom per term
#define MIN_ELECS		2			// minimum nummber of electives
#define MIN_STUDENTS	3			// minimum alloable students in a calssroom

#define TRUE		1
#define FALSE		0
	
enum COURSE_TYPE {CORE, ELECTIVE};
enum TIME_SLOT_	 {MORNING, AFTERNOON};

struct iteration
{
	int course;
	int selected;
};

struct taken_crs
{
	int crs_num;		// nummber of the taken course
	int term_num;		// number of the term in which the course is taken
};

/* classroom structure */
struct classroom
{
	int allocated[MAX_TERMS][TIME_SLOT_NUM];	// contains the index of the course to be taken in each slot
	int alloc_num[MAX_TERMS];					// number of courses allocated in a room each term (0, 1, or 2)
	int alloc_flag[MAX_TERMS][TIME_SLOT_NUM];	// flag to indicate if a time slot is occupied 
	int num_std[MAX_TERMS][TIME_SLOT_NUM];		// number of studetns occupying the room in each time slot
	int std_list[MAX_TERMS][TIME_SLOT_NUM][MAX_STUDENTS]; // numbers of all the students in a classrooms in a certain term and time slot
	int size;									// size of the classroom
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


struct student
{
	struct taken_crs taken_courses[MAX_COURSES];// taken courses with term stamps
	int taken_num;								// number of taken courses
	int elects_taken;							// number of electives taken
	int slot[MAX_TERMS][TIME_SLOT_NUM];			// (TRUE|FLASE) to tell if the student is occupied in a certain slot
	/*table of all the suggestions for the student and the registrations*/
	struct iteration term_tbl[MAX_TERMS][MAX_ITERATIONS];
};

/* externals */
extern struct classroom classrooms[MAX_CLASSROOM];		//array of classrooms
extern struct course courses[MAX_COURSES];				//array of courses
extern int student_num;			// number of students enrolled in the university
extern int term_num;			// number of terms to simulate
extern int needed_c;			// number of core course needed to graduate
extern int sample_term;			// sample term to be printed in the output
extern int sample_std;			// student index to be printed in the output
extern int room_num;			// number of classrooms availabe
extern int course_num;			// number of courses offered

#endif /* MAIN_HPP_ */
