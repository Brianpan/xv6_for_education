#include "types.h"
#include "stat.h"
#include "user.h"
#include "syscall.h"
#include "param.h"

void ls_process()
{
  uint pstruct_size = sizeof(struct uproc);
  int pid;
  
  int i = 0;
  struct uproc *pstat = malloc(pstruct_size);
  printf(1, "pname | pid | ppid | msize | pstate | iswait | killed \n");
  for(i=0;i<NPROC;i++)
  {
    memset(pstat, 0, pstruct_size);
    
    pid = getpid2(i);
    if(pid <= 0)
      continue;

    // printing
    int flag = getprocinfo(pid, pstruct_size, (void*)pstat);
    if( flag < 0)
    {  
      printf(1, "syscall err");
      break;
    }
    else if(flag == 0)
    {
      // printf(1, "%s | ", pstat->name);
      // printf(1, "%d | ", pstat->pid);
      // printf(1, "%s | ", "UNUSED\n");
      // memset(pstat, 0, pstruct_size);
      continue;
    }
    // printing process
    
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

  free(pstat);
}

int main(int argc, char* argv[])
{
  ls_process();
  exit();
}