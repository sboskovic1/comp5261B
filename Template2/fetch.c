#include "global.h"

extern struct  pipelineReg   SHADOW_PR[];
extern unsigned  PC;
extern unsigned SHADOW_PC;
extern unsigned insMEM[];  
extern int isHALT;
extern int isTakenBranch;
extern unsigned branchTargetPC;
extern int numStallCycles;  // Statistics Counter

void do_fetch();

void fetchstage() {
  int job_num;
  job_num = ActivityArgSize(ME) - 1;
  
  while(!isHALT){
    if (TRACE)
      printf("In FETCH  Stage at time %2.0f  PC: %08X\n", GetSimTime(), PC);
    do_fetch();
    ProcessDelay(1.0);
  }
}

void do_fetch() {
  SHADOW_PR[1].INSTRUCTION = insMEM[PC/4];
  SHADOW_PR[1].PC4 = PC+4;
 
  SHADOW_PC = isTakenBranch ? branchTargetPC : PC+4;
  if (TRACE)
    printf("SHADOW_PC: %x\n", SHADOW_PC);
}




