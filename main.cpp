/*----------------------------------------------------------------------------*
Filename: 		main.cpp
Purpose: 		This file contains the main function which reads the input
		 		files and then starts the operation of the university.
Date created:	17/11/2017
Edits:
*----------------------------------------------------------------------------*/

#include <iostream>
#include <stdio.h>
#include "main.hpp"

using namespace std;

struct classroom classrooms[MAX_CLASSROOM];		//array of classrooms
struct course courses[MAX_COURSES];				//array of courses

int main(int argc, char** argv) {
	int i;					// used in loops
	int student_num;		// number of students enrolled in the university
	int term_num;			// number of terms to simulate
	int needed_c;			// number of core course needed to graduate
	int smaple_term;		// sample term to be printed in the output
	int sample_std;			// student index to be printed in the output
	int room_num;			// number of classrooms availabe;
	int course_num;			// number of courses offered
	char tmp[MAX_ARRAY];	// temporary array to hold info
	
	FILE *input_para;		// intput containing general variables
	FILE *input_room;		//file containing info about the rooms
	FILE *input_course;		//file containing info about courses
	
	/* open the input files */
	input_para = 	fopen("input_para.txt", "r");
	input_room = 	fopen("input_room.txt", "r");
	input_course = 	fopen("input_course.txt", "r");
	
	/* read the general variables */
	fscanf(input_para, "%d", &student_num);
	fscanf(input_para, "%d", &term_num);
	fscanf(input_para, "%d", &needed_c);
	fscanf(input_para, "%d", &smaple_term);
	fscanf(input_para, "%d", &sample_std);
	
	/* read the room information */
	fscanf(input_room, "%d", &room_num);
	for (i=0; i<room_num; i++)
	{
		fscanf(input_room, "%d", &classrooms[i].size);
	}
	
	/* read the course information */
	fscanf(input_course, "%d", &course_num);
	fgets(tmp, MAX_ARRAY, input_course);	// ignore the '\n' at the start
	for (i=0; i<course_num; i++)
	{
		fgets(tmp, MAX_ARRAY, input_course);
		
	}

	
	return 0;
}
