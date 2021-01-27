/* 
 * This is an LC3 virtual machine I am building to learn more about computer architecture.
 * It was created by following along with this tutorial https://justinmeiners.github.io/lc3-vm/
 * All of the credits for this code go the person who created that tutorial ^^^
 */

 /*
  * unix specific include statements
  */
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/termios.h>
#include <sys/mman.h>

/*
 * create a an array filled with 16 bit integers
 * these will represent the memory locations
 */
uint16_t memory[UINT16_MAX];

/*
 * create an enum to store the registers
 * there will be 10 of them
 * R_PC is the program counter(instruction pointer)
 * R_COND is the conditional flag
 */
enum
{
    R_R0 = 0,
    R_R1 = 1,
    R_R2 = 2,
    R_R3 = 3,
    R_R4 = 4,
    R_R5 = 5,
    R_R6 = 6,
    R_R7 = 7,
    R_PC = 8,
    R_COND = 9,
    R_COUNT = 10
};

/*
 * store the register values in an array of 16 bit values
 */
uint16_t reg[R_COUNT];

/*
 * create an enum to store the opcodes
 * opcodes are the numbers associated with the instructions 
 */
enum 
{
    OP_BR = 0,
    OP_ADD = 1,
    OP_LD = 2,
    OP_ST = 3,
    OP_JSR = 4,
    OP_AND = 5,
    OP_LDR = 6,
    OP_STR = 7,
    OP_RTI = 8,
    OP_NOT = 9,
    OP_LDI = 10,
    OP_STI = 11,
    OP_JMP = 12,
    OP_RES = 13,
    OP_LEA = 14,
    OP_TRAP = 15
};


