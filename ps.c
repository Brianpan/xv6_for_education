#include "types.h"
#include "stat.h"
#include "user.h"
#include "syscall.h"
#include "param.h"

void ls_process()
{
  uint pstruct_size = sizeof(struct uproc);
  struct uproc *pstat = malloc(pstruct_size);
  
  int pid;
  
  int i = 0;
  for(i=0;i<NPROC;i++)
  {
    // get pid
    pid = getpid(i);

    // printing
    if(getprocinfo(pid, pstruct_size, (void*)pstat) < 0)
      printf(1, "syscall err");

    // printing process
    printf(1, "pname | pid | ppid | msize | pstate | iswait | killed \n");
    printf(1, "%s | ", pstat->name);
    printf(1, "%d | ", pstat->pid);
    printf(1, "%d | ", pstat->ppid);
    printf(1, "%d | ", pstat->sz);
    switch(pstat->state)
    {
      case UUNUSED: printf(1, "%s | ", "UNUSED");
                   break;
      case UEMBRYO: printf(1, "%s | ", "EMBRYO");
                   break; 
      case USLEEPING: printf(1, "%s | ", "SLEEPING");
                   break;
      case URUNNABLE: printf(1, "%s | ", "UEMBRYO");
                   break;
      case URUNNING: printf(1, "%s | ", "RUNNING");
                   break;
      case UZOMBIE: printf(1, "%s | ", "ZOMBIE");
                   break;
    }
    printf(1, "%d | ", pstat->waiting);
    printf(1, "%d\n", pstat->killed);
    }
}

int main(int argc, char* argv[])
{
  ls_process();
  exit();
}