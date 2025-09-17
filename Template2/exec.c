#include "global.h"

extern  struct pipelineReg  PR[];
extern  struct pipelineReg  SHADOW_PR[];
extern void displayPipelineReg(int);
extern void displaySHadowPipelineReg(int);
extern int isHALT;

void do_execute();
extern  void handleForwarding();

int forwardMEM_WBOp1, forwardMEM_WBOp2, forwardEX_MEMOp1, forwardEX_MEMOp2;

void executestage(){
  while(!isHALT){	
    if (TRACE)
      printf("\nIn EXECUTE Stage at time %2.0f Instruction: %08X\n", GetSimTime(), PR[2].INSTRUCTION);
    do_execute();
    ProcessDelay(1.000);
  }
}


// New: Added for multiplexing forwarded and normal inputs
int getOperand1() {
  return (forwardEX_MEMOp1 ? PR[3].result : (forwardMEM_WBOp1 ? PR[4].result : PR[2].operand1));
}

int getOperand2() {
  return (forwardEX_MEMOp2 ? PR[3].result : (forwardMEM_WBOp2 ? PR[4].result : PR[2].operand2));
}


void do_execute() {
  int operation;
  int  operand1, operand2;
  int result;
  int offset;
  int control;

  // New: Added for handling Data Hazards
  handleForwarding();
 

  operand1 = getOperand1();
  operand2 = getOperand2();
  operation = PR[2].opCode;
  offset = PR[2].offset;
  control = PR[2].control;
  
  switch (operation) {		  
  case   ADD:  result = operand1 + operand2;   break;		  
  case  ADDI:  result = operand1 + offset;     break;	  
  case  LOAD:  result = operand1 + offset;     break;
  case STORE:  result = operand1 + offset;     break;
  case  BNEZ:  result = (operand1 != 0) ? TRUE : FALSE; break;
  }

  SHADOW_PR[3] = PR[2];
  SHADOW_PR[3].operand1 = operand1;
  SHADOW_PR[3].operand2 = operand2;
  SHADOW_PR[3].result = result;
}


