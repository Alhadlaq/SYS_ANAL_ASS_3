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

struct classroom classrooms[MAX_CLASSROOM];

int main(int argc, char** argv) {
	int i;					// used in loops
	int student_num;		// number of students enrolled in the university
	int term_num;			// number of terms to simulate
	int needed_c;			// number of core course needed to graduate
	int smaple_term;		// sample term to be printed in the output
	int sample_std;			// student index to be printed in the output
	int room_num;			// number of classrooms availabe;
	
	FILE *input_para;		// intput containing general variables
	FILE *input_room;		//file containing info about the rooms
	
	/* open the input files */
	input_para = fopen("input_para.txt", "r");
	input_room = fopen("input_room.txt", "r");
	
	/* read the general variables */
	fscanf(input_para, "%d", &student_num);
	fscanf(input_para, "%d", &term_num);
	fscanf(input_para, "%d", &needed_c);
	fscanf(input_para, "%d", &smaple_term);
	fscanf(input_para, "%d", &sample_std);
	
	/* read the room information */
	fscanf(input_room, "%d", &room_num);
	
	
	
	return 0;
}
