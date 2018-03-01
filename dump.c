#include "types.h"
#include "stat.h"
#include "user.h"
#include "syscall.h"

#define PGSIZE 4096

void dump_mem()
{
	/* Fork a new process to play with */
  	/* We don't have a good way to list all pids in the system
    so forking a new process works for testing */ 
	uint procMemSize = (uint) sbrk(0);

	uint pid = fork();

	if(pid == 0)
	{
		while(1)
		{
			sleep(5);
		};
	}

	/* parent dumps memory of the child */
	char *buf = malloc(PGSIZE);
	memset(buf, 0, procMemSize);

	uint address = 0x0;
	printf(1, "proc mem: %d\n", procMemSize);

	// VA is from 0 to p->sz
	// based on allouvm -> mappages VA is the oldsz ( a = PGROUNDUP(oldsz); )
	while(  procMemSize > 0 )
	{
		if( PGSIZE != dump(pid, (void*) &address, (void*)buf, PGSIZE) )
			printf(1, "size not matched!");
		printf("---------------\n\n");
		// print the address
		int i= 0;
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
	
	// uint s = dump(pid, (void*)&address, (void*)buf, procMemSize);
	// printf(1, "Total process size: %d(Bytes)\n", s); 
	
	// int i= 0;
	// for(i=0;i<procMemSize/4;i++)
	// {
	// 	if(i%4 == 0)
	// 	{
	// 		printf(1, "\n");
	// 		printf(1, "0x%x: ", address);
	// 	}

	// 	uint val = *(uint*)(buf+i*4);
	// 	printf(1, "0x%x  ", val);
	// 	address += 4;
	// }
}


int main(int argc, char* argv[])
{
	dump_mem();
	exit();
}