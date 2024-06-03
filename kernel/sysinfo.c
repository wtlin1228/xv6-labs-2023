#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
#include "sysinfo.h"

uint64 
sys_info(void)
{
  // addr is a user virtual address, pointing to a struct sysinfo
  uint64 addr;
  struct proc *p = myproc();
  struct sysinfo info;

  info.freemem = get_free_memory();
  info.nproc = get_number_of_processes();
  
  argaddr(0, &addr);
  if(copyout(p->pagetable, addr, (char *)&info, sizeof(info)) < 0)
      return -1;
  return 0;
}
