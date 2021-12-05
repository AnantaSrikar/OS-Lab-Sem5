/*
	Program to simulate a memory system with variable size partitions
	
	Author: Srikar
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int main(int argc, char** argv)
{
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

	printf("Profile: %d\nPolicy: %d\n", profile, policy);

	
	return(0);
}