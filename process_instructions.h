#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "../src/emulator_decode.h"
#include "../src/emulator_types.h"
#include "../src/emulator_execute.h"

// Halt Instruction
#define HALT_INSTRUCTION 0x8a000000

// OPCODE

// OPCODE IMMEDIATE
#define OP0_IMMEDIATE_VALUE_1 26
#define OP0_IMMEDIATE_VALUE_2 29
#define OP0_IMMEDIATE_BIT_VALUE 0x4U

// OPCODE REGISTERS
#define OP0_REGISTER_VALUE_1 25
#define OP0_REGISTER_VALUE_2 28
#define OP0_REGISTER_BIT_VALUE 0x5U

#define OPR_REGISTER_ARITHMETIC_MASK 0x9U
#define OPR_REGISTER_ARITHMETIC_VALUE 0x8U

#define OPR_REGISTER_BIT_VALUE 0x8U

#define OPR_REGISTER_MULTIPLY_VALUE 0x8U

#define M_TRUE_VALUE 1

#define M_FALSE_VALUE 0

// OPCODE LOAD OR STORE
#define OP0_LOAD_OR_STORE_MASK 0x0a000000U
#define OP0_LOAD_OR_STORE_BIT_VALUE 0x08000000U
#define OP0_SINGLE_DATA_TRANSFER_VALUE 0x80000000U
#define L_DECIMAL_VALUE 1

// OPCODE BRANCH
#define OP0_BRANCH_MASK 0x1c000000U
#define OP0_BRANCH_BIT_VALUE 0x14000000U

// SF Condition for choosing either 64 or 32 bit width
#define SF_64 1

// Immediate Arithmetic
// OPI = 010
#define OPI_010 0x2U

// Immediate Wide Move
// OPI = 101
#define OPI_101 0x5U

// Branch Op Code
#define OPC_BRANCH_UNCONDITIONAL_DECIMAL_VALUE 0
#define OPC_BRANCH_REGISTER_DECIMAL_VALUE 3
#define OPC_BRANCH_CONDITIONAL_DECIMAL_VALUE 1

#define OPC_BRANCH_VALUE_1 30
#define OPC_BRANCH_VALUE_2 32

// Number of Lines and Arrows
#define LINES_STATE_SIZE 73
#define ARROWS_STATE_SIZE 44

typedef struct {
    bool lines_state[LINES_STATE_SIZE];
    bool arrows_state[ARROWS_STATE_SIZE];
} circuit_state_t;

void initialise_state(circuit_state_t *state);

circuit_state_t process_instruction(instruction_t instruction);