#include  "global.h"

extern struct pipelineReg PR[];
extern struct pipelineReg SHADOW_PR[];
extern int MEM[];
extern unsigned branchTargetPC;
extern int isTakenBranch;;
extern int isHALT;

void do_mem();

void memstage(){
  while(!isHALT){	
    if (TRACE)
      printf("In MEM Stage at time %2.0f Instruction: %08X\n", GetSimTime(), PR[3].INSTRUCTION);
    do_mem();
    ProcessDelay(1.000);
  }
}

void do_mem() {
  unsigned address = PR[3].result;
  int  data = PR[3].operand2;
  
  isTakenBranch = FALSE;
  SHADOW_PR[4] = PR[3];
    
  if (PR[3].control &0x2)  // LOAD; 
    SHADOW_PR[4].result = MEM[address];
  
  if (PR[3].control &0x4) // STORE;
    MEM[address] = data;
  
  if (PR[3].control &0x8) { // BNEZ
    if ( PR[3].result) {
      isTakenBranch = TRUE;
      branchTargetPC =  PR[3].PC4 + PR[3].offset; 
      }
  }
}


