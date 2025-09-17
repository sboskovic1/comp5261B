#include  "global.h"

extern int numInsCompleted;
extern int isHALT;
extern int stallIF;
extern unsigned  PC;
extern unsigned SHADOW_PC;
extern struct pipelineReg  PR[];
extern struct pipelineReg SHADOW_PR[];
extern struct pipelineReg dummy;

extern void displayPipelineReg(int);
extern void displayRegisterFile();

void do_sync();

void syncstage(){
  while(!isHALT){	
    if (TRACE)
      printf("In SYNC  Stage:  Time %2.0f\n", GetSimTime());
    do_sync();
    ProcessDelay(1.000);
  }
}

void do_sync() {  
  if (DEBUG)
    printf("stallIF: %d\n", stallIF);

  PR[4] = SHADOW_PR[4];
  PR[3] = SHADOW_PR[3];
  PR[2] = (!stallIF) ? SHADOW_PR[2] : dummy;
  PR[1] = (!stallIF) ? SHADOW_PR[1] : PR[1];
  PC = (!stallIF) ? SHADOW_PC : PC;

  numInsCompleted++;
  if (TRACE) {
    printf("*************************************************************\n");
    printf("State at end of cycle %5.0f\n", GetSimTime());
    
    printf("\nPC: %d \n", PC);
  
    printf("\nPipeline Register 1\n");
    displayPipelineReg(1);
    
    printf("\nPipeline Register 2\n");
    displayPipelineReg(2);
    
    printf("\nPipeline Register 3\n");
    displayPipelineReg(3);
    
    printf("\nPipeline Register 4\n");
    displayPipelineReg(4);  
        
    printf("\nREGISTER FILE\n");
    displayRegisterFile();
    printf("\n*************************************************************\n");
  }
}
