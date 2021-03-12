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

//function prototypes
uint16_t sign_extend(uint16_t x, int bit_count);
void update_flags(uint16_t r);

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
    if (argc < 2)
    {
        //show usage string
        printf("lc3 [image-file1] ...\n");
        exit(2);
    }

    for (int j = 1; j < argc; ++j)
    {
        if (!read_image(argv[j]))
        {
            printf("failed to load image %s\n", argv[j]);
            exit(1);
        }
    }
    // setup 12
    /*
     * set the PC to the starting position 
     * 0x3000 is the default
     * the hex value is used to iterate through the array not with indices, but with raw memory values
     */
    enum { PC_START = 0x3000};
    reg[R_PC] = PC_START;

    int running = 1;
    while (running) 
    {
        // FETCH INSTRUCTION FROM MEMORY
        uint16_t instr = mem_read(reg[R_PC]++);
        uint16_t op = instr >> 12;

        switch (op)
        {
            case OP_ADD:
                {
                    // destination register (DR)
                    uint16_t r0 = (instr >> 9) & 0x7;
                    // first operand (SR1)
                    uint16_t r1 = (instr >> 6) & 0x7;
                    // whether the instruction is in immediate mode
                    uint16_t imm_flag = (instr >> 5) & 0x1;

                    if (imm_flag)
                    {
                        uint16_t imm5 = sign_extend(instr & 0x1F, 5);
                        reg[r0] = reg[r1] + imm5;
                    }
                    else 
                    {
                        uint16_t r2 = (instr & 0x1F, 5);
                        reg[r0] = reg[r1] + imm5;
                    }
                    update_flags(r0);
                }
                break;
            case OP_AND:
                {

                }
                break;
            case OP_NOT:
                {
                    //destination register (DR)
                    uint16_t r0 = (intstr >> 9) & 0x7;
                    //first operand (SR1)
                    uint16_t r1 = (instr >> 6) & 0x7;
                    // whether the instruction is in immediate mode
                    uint16_t imm_flag = (instr >> 5) & 0x1;
                }
                break;
            case OP_BR:
                {BR, /*7*/}
                break;
            case OP_JMP:
                {JMP, /*7*/}
                break;
            case OP_JSR:
                {JSR, /*7*/}
                break;
            case OP_LD:
                {LD, /*7*/}
                break;
            case OP_LDI:
                { 
                    // destination register (DR)
                    uint16_t r0 = (instr >> 9) & 0x7;

                    // PC offset 9
                    uint16_t pc_offset = sign_extend(instr & 0x1FF, 9);

                    // ad pc_offset to the current PC, look at that memory location to get the final address
                    reg[r0] = mem_read(mem_read(reg[R_PC] + pc_offset));
                    update_falgs(r0);
                }
                break;
            case OP_LDR:
                {LDR, /*7*/}
                break;
            case OP_LEA:
                {LEA, /*7*/}
                break;
            case OP_ST:
                {ST, /*7*/}
                break;
            case OP_STI:
                {STI, /*7*/}
                break;
            case OP_STR:
                {STR, /*7*/}
                break;
            case OP_TRAP:
                {TRAP, /*8*/}
                break;
            case OP_RES:
            case OP_RTI:
            default:
                {BAD_OPCODE, /*8*/} 
                break;
        }
    }
    /*{Shutdown, 12}*/
}

uint16_t sign_extend(uint16_t x, int bit_count)
{
    if ((x >> (bit_count - 1)) & 1)
        x |= (0xFFFF << bit_count);
    return x;
}

void update_flags(uint16_t r)
{
    if (reg[r] == 0)
        reg[R_COND] = FL_ZRO;
    else if(reg[r] >> 15)
        reg[R_COND] = FL_NEG;
    else
        reg[R_COND] = FL_POS;
}

