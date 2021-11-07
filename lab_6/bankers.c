/*
	Implementation of Bankers Algorithm in C

	Author: Ananta Srikar
*/

#include<stdio.h>
#include<stdlib.h>

int main()
{
	// Funtion prototypes
	int **getMatrix(int, int);


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

	// Defining the matrices
	int **alloc = getMatrix(n, m);
	int **max = getMatrix(n, m);
	int **need = getMatrix(n, m);
	int *avail = (int*)malloc(m * sizeof(int));

	// avail
	for(int i = 0; i < m; i++)
		fscanf(inFPtr, "%d ", &avail[i]);

	// max
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
			fscanf(inFPtr, "%d", &max[i][j]);

	// alloc
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
			fscanf(inFPtr, "%d", &alloc[i][j]);

	// calculating the need matrix
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
			need[i][j] = max[i][j] - alloc[i][j];

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
			printf("%d ", alloc[i][j]);

		printf("\n");
	}

	printf("\nneed:\n");
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < m; j++)
			printf("%d ", need[i][j]);

		printf("\n");
	}

	return(0);
}

// Function that returns the pointer to a matrix
int** getMatrix(int n, int m)
{
	int **matrix = (int**)malloc(n * sizeof(int*));
	for(int i = 0; i < n; i++)
		matrix[i] = (int*)malloc(m * sizeof(int));

	return matrix;
}