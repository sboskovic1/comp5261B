#include "global.h"

extern unsigned REG_FILE[];
extern struct pipelineReg PR[];
extern struct pipelineReg SHADOW_PR[];
extern int isHALT;

void do_write();

void writestage(){
  int job_num;
  job_num = ActivityArgSize(ME) - 1;
  while(!isHALT){	
    if (TRACE) {
      printf("In WRITE Stage at time %2.0f  Instruction: %08X\n", GetSimTime(), PR[4].INSTRUCTION);
    }
    do_write();
    ProcessDelay(1.000);
  }
}

void do_write() {
  int destReg;

  destReg = PR[4].destReg;
  if (PR[4].writeBack)
    REG_FILE[destReg] = PR[4].result;   
}

