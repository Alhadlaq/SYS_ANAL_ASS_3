/*----------------------------------------------------------------------------*
Filename: 		main.hpp
Purpose: 		This file contains the main structures used in the university.
Date created:	17/11/2017
Edits:
*----------------------------------------------------------------------------*/


#define MAX_CLASSROOM	10
#define MAX_COURSES		20	
#define MAX_ARRAY		128
	
enum COURSE_TYPE {CORE, ELECTIVE};

/* classroom structure */
struct classroom
{
	int size;
};

struct course
{
	int type;
	int number;
};

/* externals */
extern struct classroom classrooms[MAX_CLASSROOM];
