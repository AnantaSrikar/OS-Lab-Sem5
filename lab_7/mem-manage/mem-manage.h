/*
	Header file for all the contiguos memory management operations.

	Author: Ananta Srikar
*/

# define MAX_MEM 1024

// Function prototypes
int getRandNum(int, int);
void allocMemoryBest(int, int);
// void allocMemoryWorst(int, int);
// void allocMemoryFirst(int, int);
void printMem();
void printHoles();

// Structure definitions
struct jobs_struct
{
	int pid;
	int beg;
	int end;
	struct jobs_struct *next;
};

struct hole_struct
{
	int beg;
	int end;
	struct hole_struct *next;
};

typedef struct jobs_struct jobs_struct;
typedef struct hole_struct hole_struct;