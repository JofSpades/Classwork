#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "fs.h"
#include "file.h"

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

int mappages(pde_t *pgdir, void *va, uint size, uint pa, int perm);

int check_mmaps(char* address) {
  int i=0;
  for(i=0;i<proc->mmapcount;i++) {
    // found the mmap
    if(address >= proc->mmaps[i].start && 
       address < proc->mmaps[i].start+PGROUNDUP(proc->ofile[proc->mmaps[i].fd]->ip->size)) {

      char *p = kalloc();
      mappages(proc->pgdir,(char*)PGROUNDDOWN((int)address),PGSIZE,V2P(p),PTE_U|PTE_W);
      int fd = proc->mmaps[i].fd;

      // read the one page
      begin_op();
      ilock(proc->ofile[fd]->ip);
      readi(proc->ofile[fd]->ip,p,PGROUNDDOWN((int)address)-(int)proc->mmaps[i].start,PGSIZE);
      iunlockput(proc->ofile[fd]->ip);
      end_op();

      return 1;
    }
  }
  return 0;
}

int sys_evict() {
  int addr;
  if(argint(0,&addr) < 0) {
    return -1;
  }
  else {        
    evict((char*)addr);
    return 0;
  }
}

int sys_mmap() {
  int fd;
  int flags;
  if(argint(0,&fd) < 0 || argint(1,&flags) < 0) {
    return -1;
  }
  char *returnptr = proc->mmaptop;

  if(proc->mmapcount >= NOMMAP) {
    cprintf("Error: Ran out of mmaps in struct proc.\n");
    return -1;
  }

  // populate the proc->mmaps table
  proc->mmaps[proc->mmapcount].fd=fd;
  proc->mmaps[proc->mmapcount].start=proc->mmaptop;
  proc->mmapcount++;

  // eager
  if(flags==0) {
    begin_op();
    ilock(proc->ofile[fd]->ip);

    // allocate and map memory immediately
    while(proc->mmaptop < returnptr+proc->ofile[fd]->ip->size) {
      char *p = kalloc();
      mappages(proc->pgdir,proc->mmaptop,PGSIZE,V2P(p),PTE_U|PTE_W);
      proc->mmaptop+=PGSIZE;
    }

    readi(proc->ofile[fd]->ip,returnptr,0,proc->ofile[fd]->ip->size);
    iunlockput(proc->ofile[fd]->ip);
    end_op();
  }
  else {
    proc->mmaptop+=PGROUNDUP(proc->ofile[fd]->ip->size);
  }
  return (int)returnptr;

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
