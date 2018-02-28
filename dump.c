#include "types.h"
#include "stat.h"
#include "user.h"
#include "syscall.h"

#define PGSIZE 4096
#define DUMPSIZE 1024

void dump_mem()
{
	/* Fork a new process to play with */
  	/* We don't have a good way to list all pids in the system
    so forking a new process works for testing */ 
	int pid = fork();

	if(pid == 0)
	{
		while(1)
		{
			sleep(5);
		};
	}

	/* parent dumps memory of the child */
	char *buf = malloc(PGSIZE);
	memset(buf, 0, PGSIZE);

	unsigned int procMemSize = (unsigned int) sbrk(0);
	uint address = 0x0;
	printf(1, "proc mem: %d", procMemSize);

	// VA is from 0 to p->sz
	// based on allouvm -> mappages VA is the oldsz ( a = PGROUNDUP(oldsz); )
	// while(  procMemSize > 0 )
	// {
	// 	if( PGSIZE != dump(pid, (char*) address, buf, PGSIZE) )
	// 	{
	// 		printf("size not matched %i", shiftSize);
	// 	}
	// 	// print the address
		
	// 	// increment
	// 	procMemSize -= PGSIZE;
	// 	address += PGSIZE;
	// }
	
	int s = dump(pid, (void*)&address, (void*)buf, PGSIZE);
	for(int i=0;i<1024;i++)
	{
		int a = *(int*)(buf+i*4);
		printf(1, "0x%x\n", a);
	}

	printf(1, "int return from dump: %d", s);

	
}


int main(int argc, char* argv[])
{
	dump_mem();
	exit();
}