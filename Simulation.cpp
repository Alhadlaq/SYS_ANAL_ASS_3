/*----------------------------------------------------------------------------*
Filename: 		Simulation.cpp
Purpose: 		This file contains the functions the runs the university
				simulation such as the undergrad office, registrar,
				building manager, and cash desk.
Date created:	17/11/2017
Edits:
*----------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include "main.hpp"
#include "Simulation.hpp"

#define	DEBUGGER

int pool_sz;				// size of the mandatory pool
int mand_pool[MAX_COURSES];	// indexes of courses in mandatory pool
int elecs_in_pool;			// number of electives in the mandatory pool
int current_term;			// current term number
int current_itr;			// curent iteration number
int itr_num[MAX_TERMS];		// to keep track of the number of iterations each term
int tuition[MAX_TERMS];
struct student students[MAX_STUDENTS];	// student database

void start_simulation(void)
{
#ifdef DEBUGGER
    FILE *debug = fopen("debug.txt", "w");
#endif //DEBUGGER
	/*create the mandatory pool that the undergarduate office will use.
	 *This pool contains the core corses in addition to all the pre-
	 *requisits to these core courses*/
	create_mandatory_pool();

	for (current_term = 0; current_term < term_num; current_term++)
	{
		for (current_itr = 0; current_itr < MAX_ITERATIONS; current_itr++)
		{
			itr_num[current_term]++;

			// advise all the students on what course to take
			advise_students();

			// if there is no demand for courses, then go to the next term
			if (no_demand())
				break;

			// register the course of the highest demand
			register_course();

			// if no more courses are available, or no classrooms
			if (no_available_rooms() || no_available_courses())
				break;
		}
		// let the building manager cancel classes with less than 3 students
		building_manager();
	}
    print_reports();
#ifdef DEBUGGER
	// print the suggestion and registration table for debugging purposes
	print_term_table(debug);
    fclose(debug);
#endif // DEBUGGER

}

void print_reports()
{
    FILE *output = fopen("output.txt", "w");
    printf_graduated_students(output);
    fprintf(output, "-----------------------------------------------------------------\n");
    print_tuition(output);
    fprintf(output, "-----------------------------------------------------------------\n");
    print_sample_std(output);
    fprintf(output, "-----------------------------------------------------------------\n");
    university_time_table(output);
    fprintf(output, "-----------------------------------------------------------------\n");
    courses_taken_by_students(output);
}

void courses_taken_by_students (FILE *out)
{
    int i, j, x, crs, h_std=0, selected;
    int print_flg[MAX_STUDENTS]; // to tell if the student has been printed or not
    
    // reset the flags
    for (i=0; i<MAX_STUDENTS; i++)
    {
        print_flg[i] = FALSE;
    }
    
    fprintf(out, "The courses taken by each student in each term:\n");
    for (x=0; x<student_num; x++)
    {
        // get the student from the remaining students with the highest number of taken courses
        selected = FALSE;
        for (i=0; i<student_num; i++)
        {
            // if the student has already been printed, then skip
            if (print_flg[i])
                continue;
            
            // if the student has not been printed yet
            if (selected && (students[i].taken_num > students[h_std].taken_num))
                h_std = i;
            else if (!selected)
            {
                h_std = i;
                selected = TRUE;
            }
        }
        // when we get out of this for loop h_std will be the student with the highest courses
        
        print_flg[h_std] = TRUE;
        fprintf(out, "Student B%d:\n", h_std+1);
        for (j=0; j<students[h_std].taken_num; j++)
        {
            crs = students[h_std].taken_courses[j].crs_num;
            fprintf(out, "Term%d:\t%s\n", students[h_std].taken_courses[j].term_num+1, courses[crs].name);
        }
        if(is_graduated(h_std)){fprintf(out, "Graduated\n");}
        fprintf(out, "\n");
    }
}

void university_time_table(FILE *out)
{
    int i, j, x, crs, sz;
    char name[MAX_NAME];
    
    fprintf(out, "Full university time table:\n\n");
    for (i=0; i<term_num; i++)
    {
        fprintf(out, "Term %d:\n", i+1);
        fprintf(out, "Classroom number\tSize\tMorning class\tStudents\tAfternoon class\tStudents\n");
        for (j=0; j<room_num; j++)
        {
            fprintf(out, "Room %d", j+1);
            fprintf(out, "\t\t\t%d", classrooms[j].size);
            for (x=0; x<TIME_SLOT_NUM; x++)
            {
                crs = classrooms[j].allocated[i][x];
                if (classrooms[j].alloc_flag[i][x])
                {
                    strcpy(name, courses[crs].name);
                    sz = classrooms[j].num_std[i][x];
                }
                else
                {
                    strcpy(name, "NONE");
                    sz = 0;
                }
                fprintf(out, "\t%s", name);
                fprintf(out, "\t\t%d\t", sz);
            }
            fprintf(out, "\n");
        }
        fprintf(out, "\n");
    }
    fprintf(out, "\n");
}

void print_sample_std (FILE *out)
{
    int i, crs;
    char name[MAX_NAME];
    fprintf(out, "The sample student B%d in the sample term %d has the following suggestions:\n", sample_std+1, sample_term+1);
    for (i=0; i<itr_num[sample_term]; i++)
    {
        crs = students[sample_std].term_tbl[sample_term][i].course;
        if (crs != NO_COURSE)
            strcpy(name, courses[crs].name);
        else
            strcpy(name, "NONE");
        fprintf(out, "Iteration %d:\tw:%s\t\ts:%d\n", i+1, name,
                students[sample_std].term_tbl[sample_term][i].selected);
    }
    fprintf(out, "\n");
}
 

void print_tuition (FILE *out)
{
    int i, j, x;
    
    for (i=0; i<term_num; i++)
    {
        for (j=0; j<student_num; j++)
        {
            for (x=0; x<students[j].taken_num; x++)
            {
                if (students[j].taken_courses[x].term_num == i)
                    tuition[i]++;
            }
        }
    }
    
    fprintf(out, "The tuitions per term are:\n");
    for (i=0; i<term_num; i++)
    {
        fprintf(out, "Term %d: %d\n", i+1, tuition[i]);
    }
    fprintf(out, "\n");
}

void printf_graduated_students(FILE *out)
{
    int i, sum=0;
    for (i=0; i<student_num; i++)
    {
        if (is_graduated(i))
            sum ++;
    }
    fprintf(out, "Number of graduated students = %d\n\n", sum);
}

int is_graduated (int student)
{
    int i, j, taken;
    
    // check to see if a student has taken all the courses in the mandatory pool
    for (i=0; i<pool_sz; i++)
    {
        taken = FALSE;
        for (j=0; j<students[student].taken_num; j++)
        {
            if (mand_pool[i] == students[student].taken_courses[j].crs_num)
            {
                taken = TRUE;
                break;
            }
        }
        if (!taken)
            return FALSE;
    }
    
    // check to see if the student has taken all the required electives
    if (students[student].elects_taken < MIN_ELECS)
        return FALSE;
    
    return TRUE;
}

void building_manager(void)
{
	int i, j, x, course;
    
    /* cancel the classes with less than 3 students */
	// for all the classrooms
	for (i = 0; i < room_num; i++)
	{
		// for all the time slots (morning and afternoon)
		for (j = 0; j < TIME_SLOT_NUM; j++)
		{
			// if the time slot is taken and contains less than 3 students
			if (classrooms[i].alloc_flag[current_term][j] && classrooms[i].num_std[current_term][j] < MIN_STUDENTS)
			{
				// cancel the classroom
				classrooms[i].alloc_flag[current_term][j] = FALSE;
                classrooms[i].num_std[current_term][j] = 0;
				classrooms[i].alloc_num[current_term]--;

				//cancel the course for that term
				course = classrooms[i].allocated[current_term][j];
				courses[course].registered[current_term] = FALSE;

				// tell the students that the course is canceled
				for (x = 0; x < classrooms[i].num_std[current_term][j]; x++)
				{
					remove_course(classrooms[i].std_list[current_term][j][x], i, j, course);
				}
			}
		}
	}
    
    /* switch classrooms if needed */
    for (i = 0; i < room_num; i++)
    {
        // for all the time slots (morning and afternoon)
        for (j = 0; j < TIME_SLOT_NUM; j++)
        {
            switch_room_if_required(i, j);
        }
    }
}

void switch_room_if_required (int room, int slot)
{
    int i, tmp;
    
    for (i=0; i<room_num; i++)
    {
        if (classrooms[room].size > classrooms[i].size &&
            classrooms[room].num_std[current_term][slot] < classrooms[i].num_std[current_term][slot])
        {
            // switch the rooms
            tmp = classrooms[room].allocated[current_term][slot];
            classrooms[room].allocated[current_term][slot] = classrooms[i].allocated[current_term][slot];
            classrooms[i].allocated[current_term][slot] = tmp;
            
            tmp = classrooms[room].num_std[current_term][slot];
            classrooms[room].num_std[current_term][slot] = classrooms[i].num_std[current_term][slot];
            classrooms[i].num_std[current_term][slot] = tmp;
            
            if (!classrooms[room].alloc_flag[current_term][slot])
            {
                classrooms[room].alloc_flag[current_term][slot] = TRUE;
                classrooms[i].alloc_flag[current_term][slot] = FALSE;
            }
        }
    }
}

void remove_course(int student, int room, int slot, int course)
{
	int i;

	// deselect the student
	for (i = 0; i < itr_num[current_term]; i++)
	{
		if (students[student].term_tbl[current_term][i].course == course)
			students[student].term_tbl[current_term][i].selected = FALSE;
	}

	// take the course out from the list of taken courses
	i = students[student].taken_num-1;
	if (students[student].taken_courses[i].crs_num != course)
	{
		students[student].taken_courses[i - 1].crs_num = students[student].taken_courses[i].crs_num;
		students[student].taken_courses[i - 1].term_num = students[student].taken_courses[i].term_num;
	}
	students[student].taken_num--;

	// if it is an elective then decrement the number of taken electives
	if (courses[course].type == ELECTIVE)
		students[student].elects_taken--;

	// make the time slot for the student unoccupied
	students[student].slot[current_term][slot] = FALSE;

}

void print_term_table(FILE *out)
{
	int i, j, x;
	char name[MAX_NAME];
	for (i = 0; i < term_num; i++)
	{
		fprintf(out, "Term %d\n", i+1);
		fprintf(out, "student number");
		for (j = 0; j < itr_num[i]; j++)
			fprintf(out, "\titeration number %d", j+1);
		fprintf(out, "\n");
		for (x = 0; x < student_num; x++)
		{
			fprintf(out, "B%d\t\t", x+1);
			for (j = 0; j < itr_num[i];j++)
			{
				if (students[x].term_tbl[i][j].course != NO_COURSE)
					strcpy(name, courses[students[x].term_tbl[i][j].course].name);
				else
					strcpy(name, "NONE");
				fprintf(out, "w: %s s: %d\t\t", name, students[x].term_tbl[i][j].selected);
			}
			fprintf(out, "\n");
		}
	}
}

int no_available_rooms(void)
{
	int i;
	for (i = 0; i < room_num; i++)
	{
		if (classrooms[i].alloc_num[current_term] < MAX_ALLOC)
			return FALSE;
	}
	return TRUE;
}


int no_available_courses(void)
{
	int i;
	for (i = 0; i < course_num; i++)
	{
		if (!courses[i].registered[current_term])
			return FALSE;
	}
	return TRUE;
}

int no_demand(void)
{
	int i;
	for (i = 0; i < student_num; i++)
	{
		if (students[i].term_tbl[current_term][current_itr].course != NO_COURSE)
			return FALSE;
	}
	return TRUE;
}

void register_course(void)
{
	int i;
	int hd_crs = 0;	// course of the highest demand
	int room;		// holds the index of the chosen room
	int slot;		// chosen time slot
	int tmp;		// temporary hold the idnex of a student

	// find the course of the highest demand
	for (i = 0; i < course_num; i++)
	{
		if (courses[i].demand[current_term][current_itr] > courses[hd_crs].demand[current_term][current_itr])
			hd_crs = i;
	}
	courses[hd_crs].registered[current_term] = TRUE;

	// find the classroom that best fits the students
	// it should be the smaller classroom that can fit the students
	// and at the same time has the least time conflicts
	room = find_room(courses[hd_crs].demand[current_term][current_itr]);

	// register the course in that room
	// if the morning slot is empty, then take it. or put course in afternoon slot
	if (!classrooms[room].num_std[current_term][MORNING])
		slot = MORNING;
	else
		slot = AFTERNOON;
	classrooms[room].allocated[current_term][slot] = hd_crs;
	classrooms[room].alloc_num[current_term]++;
	classrooms[room].alloc_flag[current_term][slot] = TRUE;

	// select the accepted students
	// the unaccepted studetnss are rejected because either the room
	// is too small or it contradicts their time schedule
	for (i = 0; i < student_num; i++)
	{
		// if the student wants the highest demand course and it does not conflict with schedule
		if ((students[i].term_tbl[current_term][current_itr].course == hd_crs) && (!students[i].slot[current_term][slot]))
		{
			// update student info
			students[i].term_tbl[current_term][current_itr].selected = TRUE;
			students[i].taken_courses[students[i].taken_num].crs_num = hd_crs;
			students[i].taken_courses[students[i].taken_num].term_num = current_term;
			students[i].taken_num++;
			students[i].slot[current_term][slot] = TRUE;
			if (courses[hd_crs].type == ELECTIVE)
				students[i].elects_taken++;

			// update classroom info
			tmp = classrooms[room].num_std[current_term][slot];		// index to the student list buffer
			classrooms[room].std_list[current_term][slot][tmp] = i;	// put number of student in the class student list
			classrooms[room].num_std[current_term][slot]++;			// increment the number of students in the classroom
			if (classrooms[room].num_std[current_term][slot] == classrooms[room].size)
				break;
		}
	}
}

int find_room(int demand)
{
	int selected = FALSE;	//flag that tells if a room has been selected or not
	int chosen=0;			//index number of the chosen room
	int i;

	for (i = 0; i < room_num; i++)
	{
		// if the room fits the students and it is available
		if ((classrooms[i].size >= demand) && (classrooms[i].alloc_num[current_term] < MAX_ALLOC))
		{
			//if the we have already selected a room and this room is smaller than previously selected one
			if (selected && classrooms[i].size < classrooms[chosen].size)
				chosen = i;
			//if we have not already selected a room, then select this room
			else if (!selected)
			{
				chosen = i;
				selected = TRUE;
			}
		}
	}

	//if no room has been selected, then just choose the largest available room
	if (!selected)
	{
		for (i = 0; i < room_num; i++)
		{
			if (classrooms[i].alloc_num[current_term] < MAX_ALLOC)
			{
				if (selected && classrooms[i].size > classrooms[chosen].size)
					chosen = i;
				else if (!selected)
				{
					chosen = i;
					selected = TRUE;
				}
			}
		}
	}

	return chosen;
}

void advise_students(void)
{
	int i, j, course, course_found;

	// for each student
	for (i = 0; i < student_num; i++)
	{
		/* if the student has taken the required number to graduate
		or if the student is taking a full load
		then dont advise the student to take any course and go to the next student */
		if (taking_full_load(i, current_term) || is_graduated(i))
		{
			students[i].term_tbl[current_term][current_itr].course = NO_COURSE;
			continue;
		}

		course_found = FALSE;
		// go through all the mandatory courses
		for (j = 0; j < pool_sz; j++)
		{
			course = mand_pool[j];
			/*if the course is: not taken by the student
			& not already registered
			& the pre-requisits are taken by student
			Then advise the student to take this course*/
			if (!is_taken(course, i) && pre_reqs_taken(course, i) && !courses[course].registered[current_term])
			{
				students[i].term_tbl[current_term][current_itr].course = course;
				courses[course].demand[current_term][current_itr]++;
				course_found = TRUE;
				break;
			}
		}

		// if the mandatory pool does not contain enough electives and no course is assigned from the pool
		if ((!course_found) && (elecs_in_pool < MIN_ELECS) && (students[i].elects_taken < MIN_ELECS))
		{
			//give the student any available elective course
			for (course = 0; course < course_num; course++)
			{
				if (!is_taken(course, i) && pre_reqs_taken(course, i) && !courses[course].registered[current_term])
				{
					students[i].term_tbl[current_term][current_itr].course = course;
					courses[course].demand[current_term][current_itr]++;
					course_found = TRUE;
					break;
				}
			}
		}

		// if no course is found, then dont advise the student
		if (!course_found)
			students[i].term_tbl[current_term][current_itr].course = NO_COURSE;
	}
}

int taking_full_load(int student, int term)
{
	int i, sum=0, result = FALSE;

	for (i = 0; i < itr_num[term]; i++)
	{
		sum += students[student].term_tbl[term][i].selected;
	}

	if (sum == FULL_LOAD)
		result = TRUE;

	return result;
}

int pre_reqs_taken(int course, int student)
{
	int i, j;
	int taken;

	for (i = 0; i < courses[course].pre_req_num; i++)
	{
		taken = FALSE;
		for (j = 0; j < students[student].taken_num; j++)
		{
			if (students[student].taken_courses[j].crs_num == courses[course].pre_req[i]
				&& students[student].taken_courses[j].term_num < current_term)
			{
				taken = TRUE;
				break;
			}
		}
		if (!taken)
			return FALSE;
	}
	return TRUE;
}

int is_taken(int course, int student)
{
	int i;
	for (i = 0; i < students[student].taken_num; i++)
	{
		if (students[student].taken_courses[i].crs_num == course)
			return TRUE;
	}
	return FALSE;
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
