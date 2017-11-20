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
#include "Simulation.hpp"

using namespace std;

struct classroom classrooms[MAX_CLASSROOM];		//array of classrooms
struct course courses[MAX_COURSES];				//array of courses

int student_num;		// number of students enrolled in the university
int term_num;			// number of terms to simulate
int needed_c;			// number of core course needed to graduate
int smaple_term;		// sample term to be printed in the output
int sample_std;			// student index to be printed in the output
int room_num;			// number of classrooms availabe
int course_num;			// number of courses offered

void read_general_variables(FILE *input_file)
{
	/* read the general variables */
	fscanf(input_file, "%d", &student_num);
	fscanf(input_file, "%d", &term_num);
	fscanf(input_file, "%d", &needed_c);
	fscanf(input_file, "%d", &smaple_term);
	fscanf(input_file, "%d", &sample_std);
}

void read_room_info(FILE *input_file)
{
	int i;

	fscanf(input_file, "%d", &room_num);

	for (i = 0; i<room_num; i++)
	{
		fscanf(input_file, "%d", &classrooms[i].size);
	}
}

void read_course_info(FILE *input_file)
{
	int i, z;				// used in loops
	int pre_req_num;		// nummber of prerequisits
	char tmp_ary[MAX_ARRAY];// temporary array to hold info
	char *tmp_ptr;			// temporary pointer 

	fscanf(input_file, "%d", &course_num);
	fgets(tmp_ary, MAX_ARRAY, input_file);// ignore the '\n' at the start

	/*perform a first pass to record all the courses*/
	for (i = 0; i<course_num; i++)
	{
		fgets(tmp_ary, MAX_ARRAY, input_file);
		tmp_ptr = strtok(tmp_ary, " \n");
		strcpy(courses[i].name, tmp_ptr);
		if (*tmp_ptr == 'c')
			courses[i].type = CORE;
		else
			courses[i].type = ELECTIVE;
		courses[i].number = atoi(tmp_ptr + 1);
	}

	/*perform a second pass to record the pre-requisits*/
	rewind(input_file);		//look at the start of the file
	fgets(tmp_ary, MAX_ARRAY, input_file);//ignore first num
	for (i = 0; i<course_num; i++)
	{
		pre_req_num = 0;						//number of pre-reqs
		fgets(tmp_ary, MAX_ARRAY, input_file);
		tmp_ptr = strtok(tmp_ary, " \n");		//ignore the first course
		tmp_ptr = strtok(NULL, " \n");			//first pre-requisit
		while (tmp_ptr)							//while there is a pre-req
		{
			for (z = 0; z < course_num; z++)	         //look thrgouh the courses
			{
				if (!strcmp(tmp_ptr, courses[z].name))   //if the course is found
				{
					courses[i].pre_req[pre_req_num] = z; //store the pre-req index
					pre_req_num++;
					break;
				}
			}
			tmp_ptr = strtok(NULL, " \n");	    //get the next pre-requist
		}
		courses[i].pre_req_num = pre_req_num;	//record the number of pre-req for this course
	}
}

int main(int argc, char** argv) {
	
	
	FILE *input_para;		//intput containing general variables
	FILE *input_room;		//file containing info about the rooms
	FILE *input_course;		//file containing info about courses
	
	/* open the input files */
	input_para = 	fopen("input_para.txt", "r");
	input_room = 	fopen("input_room.txt", "r");
	input_course = 	fopen("input_course.txt", "r");
	
	/* read the general variables */
	read_general_variables(input_para);
	
	/* read the room information */
	read_room_info(input_room);
	
	/*read the course information*/
	read_course_info(input_course);

	/*start the university simulation*/
	start_simulation();

	return 0;
}
