#include "global.h"
extern unsigned  MEM[];
extern unsigned insMEM[];


extern unsigned REG_FILE[];

/* ******************************   PROGRAM  1 *********************************** */

void loadProgram() {
  int i;

  for (i=0; i < INSTR_MEM_SIZE; i++)  // Initialize all Instruction memory to NOPs 
      insMEM[i] =  0;  
  
  // PROGRAM  1  In ORDER  solution with Branch NOPs
  // Accumulates the sum of an array of n consecutive memory words into Register R2
  // The base address of the array is in Register R1
  // R8 is initialized with the number of iterations n.
  
  insMEM[0] = 0x10200000;       // LOAD  R0,(R1)       top:  R0 = MEM[R1];
  insMEM[1] = 0X04401000;       // ADD   R2, R2, R0           sum = sum + R0;
  insMEM[2] = 0x14210001;       // ADDI  R1, R1, 1            R1 = R1 + 1;     
  insMEM[3] = 0x1508FFFF;       // ADDI  R8, R8, -1           count = count - 1;
  insMEM[4] = 0x2500FFEC;       // BNEZ  R8  -20              if (count != 0) goto top 
  insMEM[5] = 0x00000000;       // NOP   
  insMEM[6] = 0x00000000;       // NOP   
  insMEM[7] = 0x00000000;       // NOP   
  insMEM[8] = 0x28000000;       // HALT    
 }

void loadRegFile() {  
  REG_FILE[0] = 0;  
  REG_FILE[1] = BASE_ARRAY;  
  REG_FILE[2] = BASE_ARRAY_SRC1;  
  REG_FILE[3] = 1;    
  REG_FILE[4] = BASE_ARRAY_SRC2;  
  REG_FILE[5] = 0;  
  REG_FILE[6] = BASE_ARRAY_DEST;  
  REG_FILE[7] = 0;  
  REG_FILE[8] = NUM_ITERATIONS;
  REG_FILE[9] = -1;
}


/* ******************************   PROGRAM  2 *********************************** */

// void loadProgram() {
//   int i;

//   for (i=0; i < INSTR_MEM_SIZE; i++) 
//       insMEM[i] =  0;  
    
//   // PROGRAM  2   In order Solution with Branch NOPs
//   // Adds two arrays element-by-element and stores the result in a third array
//   //  The base addresses of the source arrays are in Registers R2 and R4
//   // The base address  of the destination array is R6
//   // R8 is initialized with the number of iterations.
  
//   insMEM[0] = 0x14420001;       // ADDI  R2, R2, 1          top: index1 = index1 + 1
//   insMEM[1] = 0x10400000;       // LOAD R0, 0(R2)                R0 = MEM[index1]
//   insMEM[2] = 0x14840001;       // ADDI  R4, R4, 1               index2 = index2 + 1 
//   insMEM[3] = 0x10810000;       // LOAD R1, 0(R4)                R1 = MEM[index2]
//   insMEM[4] = 0x04012800;       // ADD R5, R0, R1                sum = R0 + R1
//   insMEM[5] = 0x18C50000;       // STORE R5, 0(R6)               MEM[destindex] = sum
//   insMEM[6] = 0x14C60001;       // ADDI  R6, R6, 1               destindex = destindex + 1 
//   insMEM[7] = 0x1508FFFF;       // ADDI  R8, R8, -1              count = count-1
//   insMEM[8] = 0x2500FFDC;       // BNEZ R8  -36                  if (count ne 0) goto top
//   insMEM[9] = 0x00000000;       //NOP   
//   insMEM[10] = 0x00000000;      //NOP  
//   insMEM[11] = 0x00000000;      //NOP   
//   insMEM[12] = 0x28000000;      //HALT 
// }

// void loadRegFile() {  
//   REG_FILE[0] = 0;  
//   REG_FILE[1] = BASE_ARRAY;  
//   REG_FILE[2] = BASE_ARRAY_SRC1-1;  
//   REG_FILE[3] = 1;    
//   REG_FILE[4] = BASE_ARRAY_SRC2-1;  
//   REG_FILE[5] = 0;  
//   REG_FILE[6] = BASE_ARRAY_DEST;  
//   REG_FILE[7] = 0;  
//   REG_FILE[8] = NUM_ITERATIONS;
//   REG_FILE[9] = -1;
// }

/* ******************************   PROGRAM  3 *********************************** */

// void loadProgram() {
//   int i;

//   for (i=0; i < INSTR_MEM_SIZE; i++) 
//       insMEM[i] =  0;  
  
//   // PROGRAM  3   Array Copy
//   // Copies words from one array to another
//   // The base address of the source array is in Register R1 and the destination is 512(R1)
//   // R8 is initialized with the number of iterations n.
    
//   insMEM[0] = 0x10200000;       // LD   R0, 0(R1)         COPY: R0 = MEM[index];
//   insMEM[1] = 0x18200200;       // STORE  R0, 512(R1)           MEM[index+512] = R0
//   insMEM[2] = 0x1508FFFF;       // ADDI  R8, R8, -1             count = count - 1;
//   insMEM[3] = 0x14210001;       // ADDI  R1, R1, 1              index  = index + 1;
//   insMEM[4] = 0x2500FFEC;       // BNEZ R8  -20                  if (count != 0) goto COPY 
//   insMEM[5] = 0x00000000;       //NOP   
//   insMEM[6] = 0x00000000;       //NOP   
//   insMEM[7] = 0x00000000;       //NOP   
//   insMEM[8] = 0x28000000;       //HALT 
// }

// void loadRegFile() {  
//   REG_FILE[0] = 0;  
//   REG_FILE[1] = BASE_ARRAY;  
//   REG_FILE[2] = BASE_ARRAY_SRC1-1;  
//   REG_FILE[3] = 1;    
//   REG_FILE[4] = BASE_ARRAY_SRC2-1;  
//   REG_FILE[5] = 0;  
//   REG_FILE[6] = BASE_ARRAY_DEST;  
//   REG_FILE[7] = 0;  
//   REG_FILE[8] = NUM_ITERATIONS;
//   REG_FILE[9] = -1;
// }

// /* ******************************   PROGRAM  3 *********************************** */
