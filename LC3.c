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
 * OP_BR: branch
 * OP_ADD: add
 * OP_LD: load
 * OP_ST: store
 * OP_JSR: jump register
 * OP_AND: bitwise and
 * OP_LDR: load register
 * OP_STR: store register
 * OP_RTI: unused
 * OP_NOT: bitwise not 
 * OP_LDI: load indirect
 * OP_STI: store indirect
 * OP_JMP: jump
 * OP_RES: reserved (unused)
 * OP_LEA: load effective address
 * OP_TRAP: execute trap
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

/*
 * create an enum for the condition flags
 * these indicate the sign for the last calculation
 * FL_POS: last calculation was positive
 * FL_ZRO: last calculation was 0
 * FL_NEG: last calculation was negative
 */
enum 
{
    FL_POS = 1 << 0,
    FL_ZRO = 1 << 1,
    FL_NEG = 1 << 2
};

/*
 * this is the main bulk of the virtual machine logic
 * it handles the execution of the pieces of code passed into the emulator
 * logic is as follows:
 * 1. load one instruction from memory at the address of the PC register
 * 2. increment the PC register
 * 3. look at the opcode to determine which type of instruction it should perform
 * 4. perform the instruction using the parameters in the instruction
 * 5. go back to step 1
 */
int main(int argc, const char* argv[])
{
    enum { PC_START = 0x3000};
    // the hex value is used to iterate through the array not with indices, but with raw memory values
    reg[R_PC] = PC_START;
}

