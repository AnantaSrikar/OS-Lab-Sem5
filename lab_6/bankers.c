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
	void permute(int**, int**, int*, int, int, int*, int, int);

	FILE *inFPtr = NULL;

	inFPtr = fopen("input.txt", "r");

	if(inFPtr == NULL)
	{
		printf("input.txt is missing in the current directory!\n");
		return -1;
	}

	int m, n;	// m : num of resources, n: num of procs

	fscanf(inFPtr, "%d %d", &m, &n);

	printf("m = %d\nn = %d\n\n", m, n);

	// Defining the matrices
	int **alloc = getMatrix(n, m);
	int **max = getMatrix(n, m);
	int **need = getMatrix(n, m);
	int *resource = (int*)malloc(m * sizeof(int));
	int *avail = (int*)malloc(m * sizeof(int));

	// avail
	for(int i = 0; i < m; i++)
		fscanf(inFPtr, "%d ", &resource[i]);

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

	printf("resource:\n");
	for(int i = 0; i < m; i++)
		printf("%d ", resource[i]);

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

	// Making a temporary array
	int a[n];
	for(int i = 0; i < n; i++)
		a[i] = i;

	permute(max, alloc, resource, n, m, a, 0, n - 1);

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

void delMatrix(int **matrix, int n)
{
	for(int i = 0; i < n; i++)
		free(matrix[i]);
	free(matrix);
}

// To check if the given order of execution is safe or not
int checkSafety(int **max, int **init_alloc, int *resource, int *order, int n, int m)
{
	int cur_alloc[n][m];
	int avail[m];

	// Copying initial allocation into temp matrix
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
			cur_alloc[i][j] = init_alloc[i][j];

	// Calculating inital availability
	for(int i = 0; i < m; i++)
		avail[i] = resource[i];

	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
			avail[j] -= init_alloc[i][j];

	// Running the safety check for the given order
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
			if(cur_alloc[order[i]][j] + avail[j] >= max[order[i]][j])
				avail[j] += cur_alloc[order[i]][j];
			else
				return 0;

	return 1;
}

// Function to swap integer values at a given memory location
void swap(int *x, int *y)
{
	int temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

// Bad time complexity ;-;
void permute(int **max, int **alloc, int *resources, int n, int m, int *a, int l, int r)
{
	int i;
	if (l == r)
	{
		if(checkSafety(max, alloc, resources, a, n, m))
		{
			for(int j = 0; j < 5; j++)
				printf("%d", a[j]);
			printf("\n");
		}
	}

	else
	{
		for (i = l; i <= r; i++)
		{
			swap((a+l), (a+i));
			permute(max, alloc, resources, n, m, a, l+1, r);
			swap((a+l), (a+i));	//backtrack
		}
	}
}