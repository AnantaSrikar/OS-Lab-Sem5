/*
	Header file for all the contiguos memory management operations.

	Author: Ananta Srikar
*/

// Function prototypes
void insert(int pid, int beg, int end);
void delete(int pid);
void print();

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