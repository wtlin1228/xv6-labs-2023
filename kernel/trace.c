#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

uint64 
sys_trace(void)
{
  int mask;
  argint(0, &mask);

  struct proc *p = myproc();
  p->trace_mask = mask;

  return 0;
}
