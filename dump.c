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
	int pid = fork();

	if(pid == 0)
	{
		while(1)
		{
			sleep(5);
		};
	}

	/* parent dumps memory of the child */
	char buf[PGSIZE];
	memset(buf, 0, PGSIZE);
	// uint procMemSize = sbrk(0);
	uint address = 0x0;
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
	printf(1, "int return from dump:");
	
}


int main(int argc, char* argv[])
{
	dump_mem();
	exit();
}