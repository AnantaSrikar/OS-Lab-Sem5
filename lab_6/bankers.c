/*
	Implementation of Bankers Algorithm in C

	Author: Ananta Srikar
*/

#include<stdio.h>

int main()
{
	FILE *inFPtr = NULL;

	inFPtr = fopen("input.txt", "r");

	if(inFPtr == NULL)
	{
		printf("input.txt is missing in the current directory!\n");
		return -1;
	}

	int m, n;

	fscanf(inFPtr, "%d %d", &m, &n);

	printf("m = %d\nn = %d\n\n", m, n);

	int avail[m], max[n][m], alloc[n][m];

	// avail
	for(int i = 0; i < m; i++)
		fscanf(inFPtr, "%d ", avail[i]);

	printf("Here1\n");

	// max
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
			fscanf(inFPtr, "%d", max[i][j]);

	printf("Here2\n");

	// alloc
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
			fscanf(inFPtr, "%d", alloc[i][j]);

	printf("Here3\n");

	// Printing them:

	printf("avail:\n");
	for(int i = 0; i < m; i++)
		printf("%d ", avail[i]);

	printf("\n\nmax:\n");
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < m; j++)
			printf("%d ", max[i][j]);

		printf("\n");
	}

	printf("\nalloc:\n");
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < m; j++)
			printf("%d ", max[i][j]);

		printf("\n");
	}
	
	return(0);
}