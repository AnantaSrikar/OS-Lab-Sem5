/*
	Header file for all the contiguos memory management operations.

	Author: Ananta Srikar
*/

# define MAX_MEM 1024

// Function prototypes
void allocMemoryBest(int, int);
// void allocMemoryWorst(int, int);
// void allocMemoryFirst(int, int);
void printMem();
void printHoles();

// Structure definitions
struct aloc_struct
{
	int pid;
	int beg;
	int end;
	struct aloc_struct *next;
};

struct hole_struct
{
	int beg;
	int end;
	struct hole_struct *next;
};

typedef struct aloc_struct aloc_struct;
typedef struct hole_struct hole_struct;