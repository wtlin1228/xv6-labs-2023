#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "spinlock.h"
#include "proc.h"

int sys_sigalarm(void)
{
  int interval;
  uint64 handler;
  struct proc *p = myproc();

  argint(0, &interval);
  argaddr(1, &handler);

  p->alarm_interval = interval;
  p->alarm_handler = handler;
  p->alarm_ticks = 0;

  return 0;
}

int sys_sigreturn(void)
{
  struct proc *p = myproc();
  memmove(p->trapframe, p->alarm_trapframe, sizeof(struct trapframe));
  kfree((void*)p->alarm_trapframe);
  p->alarm_trapframe = 0;
  p->alarm_lock = 0;
  return 0;
}
