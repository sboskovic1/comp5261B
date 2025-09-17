#include "global.h"
#include <string.h>
#include <stdio.h>

extern struct pipelineReg PR[];
extern struct pipelineReg SHADOW_PR[];
extern int forwardMEM_WBOp1, forwardMEM_WBOp2, forwardEX_MEMOp1, forwardEX_MEMOp2;
extern int stallIF;


void checkReg(int reg, int o3, int o4);
int isWrite(int opcode);

void handleForwarding() {

  /* Set the four signals to control the inputs to the multiplexers to the ALU in the EX stage. 
      
      forwardEX_MEMOp1: set to TRUE if and only if "src1" of the instruction in the EX stage has a RAW dependency 
      on the instruction in the  EX_MEM pipeline register.
      forwardMEM_WBOp1: set to TRUE if and only if "src1" of the instruction in the EX stage has a RAW dependency 
      on the instruction in the MEM_WB pipeline register.
    
      forwardEX_MEMOp2:  Same as "forwardEX_MEMOp1" for "src2" of instruction in the EX stage.
      forwardMEM_WBOp2:  Same as "forwardMEM_WBOp1" for "src2" of instruction in the EX stage.
  */
    forwardEX_MEMOp1 = FALSE;
    forwardEX_MEMOp2 = FALSE;
    forwardMEM_WBOp1 = FALSE;
    forwardMEM_WBOp2 = FALSE;
    if (SHADOW_PR[2].opCode != 0 && SHADOW_PR[2].opCode != HALT) {
        if ((SHADOW_PR[3].destReg != -1) && (SHADOW_PR[3].opCode == ADD || SHADOW_PR[3].opCode == ADDI || SHADOW_PR[3].opCode == SUB || SHADOW_PR[3].opCode == MUL || SHADOW_PR[3].opCode == COPYFP)) {
            if (SHADOW_PR[2].srcReg1 == SHADOW_PR[3].destReg) {
                forwardEX_MEMOp1 = TRUE;
            }
            if (SHADOW_PR[2].srcReg2 == SHADOW_PR[3].destReg) {
                forwardEX_MEMOp2 = TRUE;
            }
        }
        if ((SHADOW_PR[4].destReg != -1) && (SHADOW_PR[4].opCode == ADD || SHADOW_PR[4].opCode == ADDI || SHADOW_PR[4].opCode == SUB || SHADOW_PR[4].opCode == MUL || SHADOW_PR[4].opCode == COPYFP)) {
            if (SHADOW_PR[2].srcReg1 == SHADOW_PR[4].destReg) {
                forwardMEM_WBOp1 = TRUE;
            }
            if (SHADOW_PR[2].srcReg2 == SHADOW_PR[4].destReg) {
                forwardMEM_WBOp2 = TRUE;
            }
        }
    }
}



void checkDataHazard() {

  /* Set the signal "stallIF" to stall the instruction in the ISSUE stage for an additional cycle.
   stallIF: Set to TRUE if and only if the instruction in the ISSUE stage has a RAW dependency with 
   a LOAD instruction immediately ahead of it in the pipeline.
  */
    if (SHADOW_PR[2].opCode != 0 && SHADOW_PR[2].opCode != HALT) {
        checkReg(SHADOW_PR[2].srcReg1, SHADOW_PR[3].opCode, SHADOW_PR[4].opCode);
        checkReg(SHADOW_PR[2].srcReg2, SHADOW_PR[3].opCode, SHADOW_PR[4].opCode);
    }
  
}


void checkReg(int reg, int o3, int o4) {
    if (reg == -1) return;
    if (((SHADOW_PR[3].destReg == reg) && (o3 == LOAD)) || ((SHADOW_PR[4].destReg == reg) && (o4 == LOAD))) {
        stallIF = TRUE;
    }
}



