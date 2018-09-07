#include "types.h"
#include "defs.h"
#include "fs.h"
#include "file.h"
#include "memlayout.h"
#include "mmu.h"
#include "int32.h"


int displaywrite(struct file *f, char* buf, int n) {
  //add code to copy buf to the display here
  return 0;
}

int
displayioctl(struct file *f, int param, int value) {  
  regs16_t regs;
  memset(&regs,0,sizeof(regs));
  if(param==1) {    

    // save character buffer before switching
    if(value==0x13) {
      consolesave();
    }

    regs.ax=0xff & ((char)value);
    bios_int(0x10,&regs);

    // restore after switching
    if(value!=0x13) {
      consolerestore();
    }

    return 0;
  }    
  if(param==2) {
    return 0;
  }
  return -1;
}


void displayinit() {
  devsw[DISPLAY].write = displaywrite;
}
