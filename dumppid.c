#include "types.h"
#include "stat.h"
#include "user.h"
#include "syscall.h"

#define PGSIZE 4096

void dump_pid_mem(int pid)
{
	/* Fork a new process to play with */
  	/* We don't have a good way to list all pids in the system
    so forking a new process works for testing */ 
	int procMemSize = getprocsize(pid);
	if(procMemSize < 0)
	{
		printf(1, "no such pid !");
		return;
	}

	/* parent dumps memory of the child */
	char *buf = malloc(PGSIZE);
	memset(buf, 0, PGSIZE);

	uint address = 0x0;

	// VA is from 0 to p->sz
	// based on allouvm -> mappages VA is the oldsz ( a = PGROUNDUP(oldsz); )
	int reachText = 1;
	int reachGuard = 0;
	int reachStack = 0;
	while(  procMemSize > 0 )
	{
		memset(buf, 0, PGSIZE);
		int flag = dump(pid, (void*) address, (void*)buf, PGSIZE);

		if(  flag < 0 )
		{
			printf(1, "size not matched!");
			break;
		}
		// define which part is Text, Guard Page, Stack, Heap
		if(reachText == 1)
		{
			printf(1, "\n-------Text Page--------\n");
			reachText = 0;
		}
		else if(reachGuard == 0 && flag == 1)
		{
			printf(1, "\n-------Guard Page--------\n");
			reachGuard = 1;
		}
		else if(reachGuard == 1 && flag == 0)
		{
			printf(1, "\n-------Guard Page End User Stack Page--------\n");
			reachGuard = 0;
			reachStack = 1;
		}
		else if(reachStack == 1 && flag == 0)
		{
			printf(1, "\n-------User Stack End Heap Page--------\n");
			reachStack = 0;
		}
		printf(1, "\n");
		
		// print the address
		int i;
		for(i=0;i<PGSIZE/4;i++)
		{
			if(i%4 == 0)
			{
				printf(1, "\n");
				printf(1, "0x%x: ", address);
			}

			uint val = *(uint*)(buf+i*4);
			printf(1, "0x%x  ", val);
			address += 4;
		}

		// increment
		procMemSize -= PGSIZE;
	}
	printf(1, "\n");
}


int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		printf(1, "param should be 2");
		exit();
	}

	int pid = atoi(argv[1]);
	dump_pid_mem(pid);
	exit();
}