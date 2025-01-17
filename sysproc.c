#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_random(void)
{
  return random();
}

int
sys_nice(void)
{
  int inc;
  
  argint(0, &inc);

  if (inc > 20 || proc->nice + inc > 20) // prevent nice val > 20
    proc->nice = 20;
  else if (inc < -20 || proc->nice + inc < 0) // prevent nice val < 0
    proc->nice = 0;
  else
    proc->nice += inc;

  return (int) proc->nice;
}

int
sys_wolfie(void)
{
  // image modified from: https://www.asciiart.eu/animals/wolves
  char wolfie[] = "                     .\n"
                  "                    / V\\\n"
                  "                  / `  /\n"
                  "                 <<   |\n"
                  "                 /    |\n"
                  "               /      |\n"
                  "             /        |\n"
                  "           /    \\  \\ /\n"
                  "          (      ) | |\n"
                  ".~~~~~~~~~|    _/_ | |\n"
                  "`~~~~~~~~~\\______ )\\__)\n";

  const uint len = 320;
  void *buf;
  uint size;  
  if ((argptr(0, (void*)&buf, sizeof(*buf)) < 0) || (argint(1, (int*)&size) < 0))
    return -1;
  if (size < len)
    return -1;

  memmove(buf, wolfie, len);
  return 0;
}

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
  return proc->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = proc->sz;
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
    if(proc->killed){
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
