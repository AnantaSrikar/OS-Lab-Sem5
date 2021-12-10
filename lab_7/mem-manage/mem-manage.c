/*
	Code to manage all the contiguos memory management operations.

	Author: Srikar
*/

#include<stdio.h>
#include<stdlib.h>

#include "mem-manage.h"

// Linked list to store all the current memory allocations
aloc_struct *jobs_mems = NULL;
hole_struct *holes_mem = NULL;

void insert(int pid, int beg, int end)
{
	aloc_struct *new_alloc = (aloc_struct*)malloc(sizeof(aloc_struct));
	new_alloc -> pid = pid;
	new_alloc -> beg = beg;
	new_alloc -> end = end;
	new_alloc -> next = NULL;

	if(jobs_mems == NULL)
	{
		aloc_struct **temp = &jobs_mems;
		*temp = new_alloc;
	}

	else
	{
		aloc_struct *temp = jobs_mems;

		while(temp -> next != NULL)
			temp = temp -> next;

		temp -> next = new_alloc;
	}
}

void delete(int pid)
{
	// Delete the node with the given pid
	printf("Deleting PID: %d\n", pid);
	return;
}

void print()
{
	printf("Print the linked list ez\n\n");
	
	aloc_struct *temp = jobs_mems;

	if(temp == NULL)
		printf("No allocations yet!\n");

	while(temp != NULL)
	{
		printf("%d, %d, %d\n", temp -> pid, temp -> beg, temp -> end);
		temp = temp -> next;
	}
}