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

int getHoleSize(hole_struct *hole)
{
	return hole -> end - hole -> beg + 1;
}

void deleteHole(hole_struct *hole)
{
	hole_struct *temp = holes_mem;

	while(temp -> next != hole)
		temp = temp -> next;

	temp -> next = temp -> next -> next;

	free(hole);
}

void insertIntoMem(int pid, int beg, int end)
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

void insertHole(int beg, int end)
{
	hole_struct *new_hole = (hole_struct*)malloc(sizeof(hole_struct));
	new_hole -> beg = beg;
	new_hole -> end = end;
	new_hole -> next = NULL;

	if(holes_mem == NULL)
	{
		aloc_struct **temp = &holes_mem;
		*temp = new_hole;
	}

	else
	{
		aloc_struct *temp = holes_mem;

		while(temp -> next != NULL)
			temp = temp -> next;

		temp -> next = new_hole;
	}
}

void deleteProcess(int pid)
{
	// Delete the node with the given pid
	printf("Deleting PID: %d\n", pid);
	return;
}

void allocMemoryBest(int pid, int mem_size)
{
	// The whole memory is a hole initially
	if(jobs_mems == NULL)
	{
		insertIntoMem(pid, 0, mem_size - 1);
		insertHole(mem_size, MAX_MEM);
	}
	
	else
	{
		hole_struct *temp = holes_mem;
		hole_struct *best_hole = NULL;

		while(temp -> next != NULL)
		{
			int hole_size = getHoleSize(temp);

			if(hole_size >= mem_size)
				if(best_hole == NULL || (getHoleSize(temp) < getHoleSize(best_hole)))
					best_hole = temp;

			temp = temp -> next;
		}

		if(best_hole == NULL)
		{
			printf("Memory full, oof!\n");
			return;
		}

		// Delete the best hole
		insertIntoMem(pid, best_hole -> beg, best_hole -> beg + mem_size - 1);

		if(best_hole -> beg + mem_size - 1 != best_hole -> end)
			insertHole(best_hole -> beg + mem_size - 1, best_hole -> end);
		
		deleteHole(best_hole);
	}
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