/*
	Code to manage all the contiguos memory management operations.

	Author: Srikar
*/

#include<stdio.h>
#include<stdlib.h>

#include "mem-manage.h"

// Linked list to store all the current memory allocations
jobs_struct *jobs_mems = NULL;
hole_struct *holes_mem = NULL;

int getHoleSize(hole_struct *hole)
{
	return hole -> end - hole -> beg + 1;
}

void insertHole(int beg, int end)
{
	hole_struct *new_hole = (hole_struct*)malloc(sizeof(hole_struct));
	new_hole -> beg = beg;
	new_hole -> end = end;
	new_hole -> next = NULL;

	if(holes_mem == NULL)
	{
		hole_struct **temp = &holes_mem;
		*temp = new_hole;
	}

	else
	{
		hole_struct *temp = holes_mem;

		while(temp -> next != NULL)
			temp = temp -> next;

		temp -> next = new_hole;
	}
}

void deleteHole(hole_struct *hole)
{
	if(hole == NULL)
		return;

	// Node to be deleted is first node
	if(holes_mem == hole)
	{
		hole_struct **temp = &holes_mem;
		
		if(hole -> next == NULL)
			*temp = NULL;

		else
			*temp = hole -> next;

		free(hole);
	}

	else
	{
		hole_struct *temp = holes_mem;

		while(temp -> next != hole)
			temp = temp -> next;

		temp -> next = temp -> next -> next;

		free(hole);
	}
}

// To ensure we don't partition the holes accidentally
void normalizeHoles()
{
	hole_struct *t1 = holes_mem;
	hole_struct *t2;

	while(t1 -> next != NULL)
	{
		t2 = t1 -> next;

		while(t2 != NULL)
		{
			if(t1 -> end == t2 -> beg - 1)
			{
				insertHole(t1 -> beg, t2 -> end);
				
				hole_struct *temp1 = t1;
				hole_struct *temp2 = t2;
				t1 = t1 -> next;
				t2 = t2 -> next;
				deleteHole(temp1);
				deleteHole(temp2);
				break;
			}
			t2 = t2 -> next;
		}

		t1 = t1 -> next;
	}
}

int getMemSize(jobs_struct *mem)
{
	return mem -> end - mem -> beg + 1;
}

void insertIntoMem(int pid, int beg, int end)
{
	jobs_struct *new_alloc = (jobs_struct*)malloc(sizeof(jobs_struct));
	new_alloc -> pid = pid;
	new_alloc -> beg = beg;
	new_alloc -> end = end;
	new_alloc -> next = NULL;

	if(jobs_mems == NULL)
	{
		jobs_struct **temp = &jobs_mems;
		*temp = new_alloc;
	}

	else
	{
		jobs_struct *temp = jobs_mems;

		while(temp -> next != NULL)
			temp = temp -> next;

		temp -> next = new_alloc;
	}
}

int getNumJobs()
{
	jobs_struct *temp = jobs_mems;
	int num_jobs = 0;

	while(temp != NULL)
	{
		num_jobs++;
		temp = temp -> next;
	}

	return num_jobs;
}

void deleteProcess(jobs_struct *job)
{
	if(job == NULL)
		return;

	// Node to be deleted is first node
	if(jobs_mems == job)
	{
		jobs_struct **temp = &jobs_mems;
		
		if(job -> next == NULL)
			*temp = NULL;

		else
			*temp = job -> next;

		free(job);
	}

	else
	{
		jobs_struct *temp = jobs_mems;

		while(temp -> next != job)
			temp = temp -> next;

		temp -> next = temp -> next -> next;

		free(job);
	}
}

void deleteRandomJob()
{
	int proc_list = getRandNum(1, getNumJobs());
	jobs_struct *temp = jobs_mems;

	for(int i = 0; i < proc_list; i++)
		temp = temp -> next;
	
	insertHole(temp -> beg, temp -> end);
	normalizeHoles();
	deleteProcess(temp);
}

hole_struct *getHole(int mem_size)
{
	hole_struct *temp = holes_mem;
	hole_struct *best_hole = NULL;

	while(temp != NULL)
	{
		int hole_size = getHoleSize(temp);

		if(hole_size >= mem_size)
			if(best_hole == NULL || (getHoleSize(temp) < getHoleSize(best_hole)))
				best_hole = temp;

		temp = temp -> next;
	}

	return best_hole;
}

void allocMemoryBest(int pid, int mem_size)
{
	printf("Mem size: %d, ", mem_size);
	// The whole memory is a hole initially
	if(jobs_mems == NULL)
	{
		insertIntoMem(pid, 0, mem_size - 1);
		insertHole(mem_size, MAX_MEM - 1);
	}
	
	else
	{
		// First, see if there's a hole big enough
		hole_struct *best_hole = NULL;

		while(best_hole == NULL)
		{
			deleteRandomJob();
			best_hole = getHole(mem_size);
		}

		// if no hole that is big enough is present
		if(best_hole == NULL)
		{
			printf("Memory full, oof!\n");
			return;
		}
		
		else
		{
			printf("Memory, not full, continuing\n");

			printf("Best hole: %d, %d\n", best_hole -> beg, best_hole -> end);

			// Delete the best hole
			insertIntoMem(pid, best_hole -> beg, best_hole -> beg + mem_size - 1);

			if(best_hole -> beg + mem_size - 1 != best_hole -> end)
				insertHole(best_hole -> beg + mem_size, best_hole -> end);
			
			deleteHole(best_hole);
		}
	}
}

void printMem()
{
	printf("Print the mem allocs ez\n\n");

	int sum = 0;
	
	jobs_struct *temp = jobs_mems;

	if(temp == NULL)
		printf("No allocations yet!\n");

	while(temp != NULL)
	{
		sum += getMemSize(temp);
		printf("%d, %d, %d, %d\n", temp -> pid, temp -> beg, temp -> end, getMemSize(temp));
		temp = temp -> next;
	}
	printf("Sum = %d\n", sum);
	printf("No of jobs in mem = %d\n", getNumJobs());
}

void printHoles()
{
	printf("Printing the holes ez\n\n");
	
	hole_struct *temp = holes_mem;

	if(temp == NULL)
		printf("No Holes yet!\n");

	while(temp != NULL)
	{
		printf("%d, %d\n", temp -> beg, temp -> end);
		temp = temp -> next;
	}
}