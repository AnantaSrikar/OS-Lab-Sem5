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
	void sortedPermutations(int**, int**, int*, int, int, int*);

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
	int nums[n];
	for(int i = 0; i < n; i++)
		nums[i] = i;

	sortedPermutations(max, alloc, resource, n, m, nums);

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

// Below functions are used to generate permutations of numbers in a lexicographical (dictionary) order

// Following function is needed for library function qsort().
int compare (const void *a, const void * b)
{
	return(*(int *)a - *(int *)b);
}

// Function to swap integer values at a given memory location
void swap(int *x, int *y)
{
	int temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

// This function finds the index of the smallest number which is greater than 'first' and is present in str[l..h]
int findCeil(int nums[], int first, int l, int h)
{
	// initialize index of ceiling element
	int ceilIndex = l;

	// Now iterate through rest of the elements and find the smallest number greater than 'first'
	for (int i = l+1; i <= h; i++)
	if (nums[i] > first && nums[i] < nums[ceilIndex])
			ceilIndex = i;

	return ceilIndex;
}

// Print all permutations of nums in sorted order
void sortedPermutations(int **max, int **alloc, int *resource, int n, int m, int *nums)
{
	int size = n;

	// Sort the numbers in increasing order
	qsort(nums, size, sizeof(nums[0]), compare);

	// Print permutations one by one
	int isFinished = 0;
	while(!isFinished)
	{
		// if the permutation is a safe execution, save it
		if(checkSafety(max, alloc, resource, nums, n, m))
		{
			printf("Safe ig: ");
			for(int i = 0; i < size; i++)
				printf ("%d ", nums[i]);
			printf("\n");
		}

		// Find the rightmost number which is smaller than its next
		// number. Let us call it 'first char'
		int i;
		for (i = size - 2; i >= 0; --i)
			if (nums[i] < nums[i+1])
				break;

		// If there is no such number, all are sorted in decreasing order,
		// means we just printed the last permutation and we are done.
		if(i == -1)
			isFinished = 1;
		
		else
		{
			// Find the ceil of 'first number' in right of first number.
			// Ceil of a number is the smallest number greater than it
			int ceilIndex = findCeil(nums, nums[i], i + 1, size - 1);

			// Swap first and second numbers
			swap(&nums[i], &nums[ceilIndex]);

			// Sort the string on right of 'first number'
			qsort(nums + i + 1, size - i - 1, sizeof(nums[0]), compare);
		}
	}
}