#include "types.h"
#include "stat.h"
#include "user.h"
#include "syscall.h"

#define PGSIZE 4096

void ls_process()
{
  char *buffer = malloc(PGSIZE);
  memset(buffer, 0, PGSIZE);

  struct uproc *pstat = malloc(sizeof(struct uproc));
  int pid = 0;
  if(getprocinfo(pid, pstat) < 0)
    printf(1, "syscall err");

  printf(1, "Process id: %d", pstat->pid);
}

int main(int argc, char* argv[])
{
  ls_process();
  exit();
}