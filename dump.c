#include "types.h"
#include "stat.h"
#include "user.h"
#include "syscall.h"

#define PGSIZE 4096


void dump2()
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
	memset(buf, PGSIZE, 0);
	// uint procMemSize = sbrk(0);
	uint address = 0;
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
	cprintf("int return from dump: %d", s);
}


int main(int argc, char* argv[])
{
	dump2();
	exit();
}