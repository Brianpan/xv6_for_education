#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"


int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

// sys dump
int
sys_dump(void)
{
  int pid, size;
  char *buf;
  char *address;
  if( argint(0, &pid) < 0 || argint(3, &size) < 0 || argptr(2, &buf, size) < 0 || argptr(1, &address, 4) < 0 )
    return -1;

  return dump(pid, address, buf, size);
}
// sys getprocinfo
int
sys_getprocinfo(void)
{
  int pid, size;
  char *up;
  if( argint(0, &pid) < 0 || argint(1, &size) < 0 || argptr(2, &up, size) < 0 )
    return -1;

  return getprocinfo(pid, (void*)up);
}

int
sys_getpid2(void)
{
  int id;
  if( argint(0, &id) < 0 )
    return -1;

  return getpid2(id);
}

int
sys_getprocsize(void)
{
  int pid;
  if( argint(0, &pid) < 0 )
    return -1;

  return getprocsize(pid);
}

// threads
int
sys_thread_create(void)
{
  uint fnc_addr, arg_addr, stack_addr;
  if( argint(0, &fnc_addr) < 0 || argint(1, &arg_addr) < 0 || argint(2, &stack_addr) < 0 )
    return -1;
  // int cast to function ptr
  return thread_create( (void (*)(void *))fnc_addr, (void*)arg_addr, (void*)stack_addr );
}

int sys_thread_join(void)
{
  return thread_join();
}

int sys_thread_exit(void)
{
  thead_exit();
  return 0;
}
