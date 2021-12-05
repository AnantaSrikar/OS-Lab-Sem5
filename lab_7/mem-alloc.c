/*
	Program to simulate a memory system with variable size partitions
	
	Author: Srikar
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>

int main(int argc, char** argv)
{
	// Function prototypes
	int getRandNum(int, int);

	// Initial code to get all command line values
	
	if(argc != 3)
	{
		printf("Incorrect number of arguments! Please go through README.md\n");
		return -1;
	}

	int const input_size = 2;
	int input_arr[input_size];

	for(int i = 1; i < argc; i++)
	{
		for(int j = 0; j < strlen(argv[i]); j++)
			if(!isdigit(argv[i][j]))
			{
				printf("Please enter only numbers!\n");
				return -1;
			}

		input_arr[i - 1] = atoi(argv[i]);
	}

	// Input sanitisation
	for(int i = 0; i < input_size; i++)
		if(!(input_arr[i] >= 1 && input_arr[i] <= 3))
		{
			printf("Incorrect choice entered. Please check README.md\n");
			return -1;
		}

	int profile = input_arr[0];
	int policy = input_arr[1];

	// Seeding the random number generator
	// NOTE: seed it only ONCE in the code
	srand(time(0));

	printf("Random number: %d\n", getRandNum(1, 1024));
	printf("Random number: %d\n", getRandNum(1, 100));
	printf("Random number: %d\n", getRandNum(500, 1000));
	
	switch(policy)
	{
		case 1:
				printf("Use best fit, lessgoo\n");
				break;

		case 2:
				printf("Use worst fit, lessgoo\n");
				break;

		case 3:
				printf("Use first fit, lessgoo\n");
				break;
		
		default:
				printf("What did you do!? Something very bad happened!\nTerminating immediately!\n");
	}
	
	return(0);
}

// Function to generate random numbers in a given range
int getRandNum(int min, int max)
{
	return (rand() % (max - min + 1) + 1);
}