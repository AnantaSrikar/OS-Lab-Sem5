/*
	Coding the basic CPU scheduling algorithms

	Author: Srikar
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct proc
{
	int arv_time;
	int bst_time;
	int proiority;
}

typedef struct proc proc;

int main()
{

	int input_arr[argc - 1];

	for(int i = 1; i < argc; i++)
	{
		for(int j = 0; j < strlen(argv[i]); j++)
			if(!isdigit(argv[i][j])
			{
				printf("Please enter only numbers!\n");
				return -1;
			}

		input_arr[i - 1] = atoi(argv[i]);
	}

	int alg = input_arr[0];
	int num_proc = input_arr[1];

	if(argc < (2 * num_proc) + 3)
	{
		printf("Incorrect number of arguments entered! Check try again\n");
		return -1;
	}

	proc all_procs[num_proc];

	for(int i = 0; i < num_proc; i++)
	{
		num_proc[i].arv_time = input_arr[i + 2]
		num_proc[i].bst_time = input_arr[num_proc + i + 2];
	}

	switch(alg)
	{
		case 1:
				print("FCFS algo lessgoo!\n");
				break;
		
		case 2:
				printf("Shortest Job first!\n");
				break;

		case 3:
				printf("Shortest remaining time first!\n");
				break;

		case 4:
				printf("Priority Scheduling!\n");
				break;

		case 5:
				printf("Round robin scheduling!\n");
				break;
	}
	
	return(0);
}