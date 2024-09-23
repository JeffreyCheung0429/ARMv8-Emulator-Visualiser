#include "process_instructions.h"

// Calls the appropriate function to execute the instruction by categorizing it
// and calls the respective decoding function to obtain the values of the fields

// Create a clear state
void initialise_state(circuit_state_t *state) {
    for (int i = 0; i < LINES_STATE_SIZE; i++) {
        state->lines_state[i] = false;
    }
    for (int i = 0; i < ARROWS_STATE_SIZE; i++) {
        state->arrows_state[i] = false;
    }
}

// Process the instruction and return the state of the circuit, and
// executing as we did in previous part
circuit_state_t process_instruction(instruction_t instruction) {
    // Generating and returning array of boolean for datapath visualisation
    circuit_state_t state;
    initialise_state(&state);

    if (uextract_bits(
            instruction,
            OP0_IMMEDIATE_VALUE_1,
            OP0_IMMEDIATE_VALUE_2
        ) == OP0_IMMEDIATE_BIT_VALUE) {
        // DP (Immediate)
        int *sf = malloc(sizeof(int)), *opc = malloc(sizeof(int));
        int *opi = malloc(sizeof(int)), *operand = malloc(sizeof(int));
        register_encoding_t *rd = malloc(sizeof(register_encoding_t));
        decode_immediate(instruction, sf, opc, opi, operand, rd);

        if (*opi == OPI_010) {
            // Arithmetic

            // ADD, SUB, ADDS, SUBS

            // Lines
            state.lines_state[63] = true;
            state.lines_state[17] = true;
            state.lines_state[22] = true;
            state.lines_state[23] = true;
            state.lines_state[21] = true;
            state.lines_state[66] = true;
            state.lines_state[69] = true;
            state.lines_state[24] = true;
            state.lines_state[25] = true;
            state.lines_state[26] = true;
            state.lines_state[70] = true;
            state.lines_state[71] = true;
            state.lines_state[72] = true;
            state.lines_state[27] = true;
            state.lines_state[28] = true;
            state.lines_state[31] = true;
            state.lines_state[56] = true;
            state.lines_state[54] = true;
            state.lines_state[45] = true;
            state.lines_state[68] = true;
            state.lines_state[32] = true;
            state.lines_state[34] = true;
            state.lines_state[40] = true;
            state.lines_state[41] = true;

            // Arrows
            state.arrows_state[15] = true;
            state.arrows_state[14] = true;
            state.arrows_state[19] = true;
            state.arrows_state[21] = true;
            state.arrows_state[22] = true;
            state.arrows_state[24] = true;
            state.arrows_state[28] = true;
            state.arrows_state[43] = true;
            state.arrows_state[33] = true;
            state.arrows_state[34] = true;
            state.arrows_state[40] = true;
            state.arrows_state[18] = true;
            state.arrows_state[17] = true;
            state.arrows_state[23] = true;
            state.arrows_state[31] = true;
            state.arrows_state[32] = true;
            state.arrows_state[42] = true;
            
            if (*opc == ADDS_DECIMAL_VALUE || *opc == SUBS_DECIMAL_VALUE) {
                // ADDS, SUBS 
                
                // Lines
                state.lines_state[44] = true;
                state.lines_state[43] = true;

                // Arrows
                state.arrows_state[36] = true;
                state.arrows_state[0] = true;
            }

            if (*sf == SF_64) {
                execute_immediate_arithmetic_64(*sf, *opc, *opi, *operand, *rd);
            } else {
                execute_immediate_arithmetic_32(*sf, *opc, *opi, *operand, *rd);
            }
        } else if (*opi == OPI_101) {
            // Wide Move (MOVN, MOVZ, MOVK)
            
            // Lines
            state.lines_state[21] = true;
            state.lines_state[66] = true;
            state.lines_state[69] = true;
            state.lines_state[70] = true;
            state.lines_state[71] = true;
            state.lines_state[72] = true;
            state.lines_state[41] = true;
            state.lines_state[45] = true;
            state.lines_state[68] = true;
            state.lines_state[54] = true;
            state.lines_state[56] = true;
            state.lines_state[31] = true;
            state.lines_state[28] = true;
            state.lines_state[27] = true;
            state.lines_state[24] = true;
            state.lines_state[25] = true;
            state.lines_state[26] = true;
            
            // Arrows
            state.arrows_state[15] = true;
            state.arrows_state[18] = true;
            state.arrows_state[22] = true;
            state.arrows_state[23] = true;
            state.arrows_state[43] = true;
            state.arrows_state[32] = true;
            state.arrows_state[34] = true;
            state.arrows_state[42] = true;
            state.arrows_state[40] = true;

            if (*opc == MOVZ_DECIMAL_VALUE) {
                // Lines
                state.lines_state[22] = true;
                state.lines_state[23] = true;

                // Arrows
                state.arrows_state[14] = true;
                state.arrows_state[17] = true;
                state.arrows_state[21] = true;
            } else if (*opc == MOVK_DECIMAL_VALUE) {
                // Lines
                state.lines_state[64] = true;
                state.lines_state[65] = true;
                state.lines_state[18] = true;
                state.lines_state[32] = true;
                state.lines_state[34] = true;
                state.lines_state[40] = true;

                // Arrows
                state.arrows_state[20] = true;
                state.arrows_state[23] = true;
                state.arrows_state[24] = true;
                state.arrows_state[28] = true;
                state.arrows_state[31] = true;
            }

            if (*sf == SF_64) {
                execute_immediate_wide_move_64(*sf, *opc, *opi, *operand, *rd);
            } else {
                execute_immediate_wide_move_32(*sf, *opc, *opi, *operand, *rd);
            }
        }

        free(sf); free(opc); free(opi); free(operand); free(rd);
        return state;

    } else if (uextract_bits(
            instruction,
            OP0_REGISTER_VALUE_1,
            OP0_REGISTER_VALUE_2
        ) == OP0_REGISTER_BIT_VALUE) {

        int *sf = malloc(sizeof(int)), *opc = malloc(sizeof(int));
        int *M = malloc(sizeof(int)), *opr = malloc(sizeof(int));
        int *operand = malloc(sizeof(int));
        register_encoding_t *rm = malloc(sizeof(register_encoding_t));
        register_encoding_t *rn = malloc(sizeof(register_encoding_t));
        register_encoding_t *rd = malloc(sizeof(register_encoding_t));
        decode_register(instruction, sf, opc, M, opr, rm, operand, rn, rd);

        // Register Arithmetic, Register Bit Logic, & Register Multiply 

        // Lines
        state.lines_state[63] = true;
        state.lines_state[64] = true;
        state.lines_state[65] = true;
        state.lines_state[17] = true;
        state.lines_state[18] = true;
        state.lines_state[32] = true;
        state.lines_state[23] = true;
        state.lines_state[21] = true;
        state.lines_state[66] = true;
        state.lines_state[22] = true;
        state.lines_state[34] = true;
        state.lines_state[33] = true;
        state.lines_state[35] = true;
        state.lines_state[67] = true;
        state.lines_state[40] = true;
        state.lines_state[41] = true;
        state.lines_state[45] = true;
        state.lines_state[68] = true;
        state.lines_state[54] = true;
        state.lines_state[56] = true;
        state.lines_state[31] = true;
        state.lines_state[28] = true;
        state.lines_state[27] = true;
        state.lines_state[26] = true;
        state.lines_state[25] = true;
        state.lines_state[24] = true;

        // Arrows
        state.arrows_state[19] = true;
        state.arrows_state[20] = true;
        state.arrows_state[23] = true;
        state.arrows_state[24] = true;
        state.arrows_state[14] = true;
        state.arrows_state[21] = true;
        state.arrows_state[25] = true;
        state.arrows_state[28] = true;
        state.arrows_state[33] = true;
        state.arrows_state[29] = true;
        state.arrows_state[34] = true;
        state.arrows_state[42] = true;
        state.arrows_state[40] = true;
        state.arrows_state[15] = true;
        state.arrows_state[18] = true;
        state.arrows_state[22] = true;
        state.arrows_state[17] = true;
        state.arrows_state[31] = true;
        state.arrows_state[32] = true;

        if (*M == M_FALSE_VALUE &&
            (*opr & OPR_REGISTER_ARITHMETIC_MASK) == 
                OPR_REGISTER_ARITHMETIC_VALUE
        ) {
            // Register Arithmetic

            if (*opc == ADDS_DECIMAL_VALUE || *opc == SUBS_DECIMAL_VALUE) {
                // ADDS, SUBS 
                
                // Lines
                state.lines_state[44] = true;
                state.lines_state[43] = true;

                // Arrows
                state.arrows_state[36] = true;
                state.arrows_state[0] = true;
            }

            if (*sf == SF_64) {
                execute_register_arithmetic_64(
                    *sf,
                    *opc,
                    *M,
                    *opr,
                    *rm,
                    *operand,
                    *rn,
                    *rd
                );
            } else {
                execute_register_arithmetic_32(
                    *sf,
                    *opc,
                    *M,
                    *opr,
                    *rm,
                    *operand,
                    *rn,
                    *rd
                );
            }
        } else if (*M == M_FALSE_VALUE && ~*opr & OPR_REGISTER_BIT_VALUE) {
            // Register Bit Logic

            int N = uextract_bits(*opr, N_REGISTER_VALUE_1, N_REGISTER_VALUE_2);

            if ((*opc << 1) + N == 
                    (ANDS_DECIMAL_VALUE << 1) + N_REGISTER_FALSE_VALUE || 
                (*opc << 1) + N == 
                    (BICS_DECIMAL_VALUE << 1) + N_REGISTER_TRUE_VALUE
            ) {
                // ANDS, BICS
                
                // Lines
                state.lines_state[44] = true;
                state.lines_state[43] = true;

                // Arrows
                state.arrows_state[36] = true;
                state.arrows_state[0] = true;
            }

            if (*sf == SF_64) {
                execute_register_logical_64(
                    *sf,
                    *opc,
                    *M,
                    *opr,
                    *rm,
                    *operand,
                    *rn,
                    *rd
                );
            } else {
                execute_register_logical_32(
                    *sf,
                    *opc,
                    *M,
                    *opr,
                    *rm,
                    *operand,
                    *rn,
                    *rd
                );
            }
        } else if (*M == M_TRUE_VALUE && *opr == OPR_REGISTER_MULTIPLY_VALUE) {
            // Register Multiply

            if (*sf == SF_64) {
                execute_register_multiply_64(
                    *sf,
                    *opc,
                    *M,
                    *opr,
                    *rm,
                    *operand,
                    *rn,
                    *rd
                );
            } else {
                execute_register_multiply_32(
                    *sf,
                    *opc,
                    *M,
                    *opr,
                    *rm,
                    *operand,
                    *rn,
                    *rd
                );
            }
        }

        free(sf); free(opc); free(M); free(opr);
        free(rm); free(operand); free(rn); free(rd);

        return state;
    } else if (
        (instruction & OP0_LOAD_OR_STORE_MASK) == OP0_LOAD_OR_STORE_BIT_VALUE
    ) {
        //LOAD, STORE, & LOAD LITERAL

        // Lines
        state.lines_state[54] = true;
        state.lines_state[56] = true;
        state.lines_state[31] = true;
        state.lines_state[60] = true;
        state.lines_state[8] = true;
        state.lines_state[7] = true;
        state.lines_state[6] = true;
        state.lines_state[21] = true;
        state.lines_state[66] = true;
        state.lines_state[69] = true;
        state.lines_state[70] = true;
        state.lines_state[71] = true;
        state.lines_state[72] = true;
        state.lines_state[41] = true;
        state.lines_state[45] = true;
        state.lines_state[68] = true;
        state.lines_state[40] = true;
        state.lines_state[64] = true;
        state.lines_state[65] = true;

        // Arrows
        state.arrows_state[4] = true;
        state.arrows_state[5] = true;
        state.arrows_state[6] = true;
        state.arrows_state[8] = true;
        state.arrows_state[9] = true;
        state.arrows_state[43] = true;
        state.arrows_state[32] = true;
        state.arrows_state[34] = true;
        state.arrows_state[23] = true;
        state.arrows_state[42] = true;
        state.arrows_state[40] = true;
        state.arrows_state[33] = true;

        // Assuming load literal determined by bit 31

        if (instruction & OP0_SINGLE_DATA_TRANSFER_VALUE) {

            int *sf = malloc(sizeof(int)), *U = malloc(sizeof(int));
            int *L = malloc(sizeof(int)), *offset = malloc(sizeof(int));
            register_encoding_t *xn = malloc(sizeof(register_encoding_t));
            register_encoding_t *rt = malloc(sizeof(register_encoding_t));
            decode_single_data_transfer(instruction, sf, U, L, offset, xn, rt);

            if (*L == L_DECIMAL_VALUE) { 
                //LOAD

                // Lines
                state.lines_state[63] = true;
                state.lines_state[17] = true;
                state.lines_state[19] = true;
                state.lines_state[20] = true;
                state.lines_state[23] = true;
                state.lines_state[9] = true;
                state.lines_state[10] = true;
                state.lines_state[58] = true;
                state.lines_state[29] = true;
                state.lines_state[26] = true;
                state.lines_state[25] = true;
                state.lines_state[24] = true;
                state.lines_state[32] = true;
                state.lines_state[34] = true;

                // Arrows
                state.arrows_state[11] = true;
                state.arrows_state[13] = true;
                state.arrows_state[16] = true;
                state.arrows_state[17] = true;
                state.arrows_state[18] = true;
                state.arrows_state[19] = true;
                state.arrows_state[21] = true;
                state.arrows_state[22] = true;
                state.arrows_state[24] = true;
                state.arrows_state[28] = true;
                state.arrows_state[31] = true;
                
                if (*sf == SF_64) {
                    execute_load_64(*sf, *U, *L, *offset, *xn, *rt);
                } else {
                    execute_load_32(*sf, *U, *L, *offset, *xn, *rt);
                }
            } else { 
                //STORE

                // Lines
                state.lines_state[63] = true;
                state.lines_state[17] = true;
                state.lines_state[18] = true;
                state.lines_state[32] = true;
                state.lines_state[34] = true;
                state.lines_state[33] = true;
                state.lines_state[35] = true;
                state.lines_state[37] = true;
                state.lines_state[30] = true;
                state.lines_state[12] = true;
                state.lines_state[11] = true;

                // Arrows
                state.arrows_state[7] = true;
                state.arrows_state[19] = true;
                state.arrows_state[20] = true;
                state.arrows_state[24] = true;
                state.arrows_state[25] = true;
                state.arrows_state[28] = true;
                state.arrows_state[31] = true;

                if (*sf == SF_64) {
                    execute_store_64(*sf, *U, *L, *offset, *xn, *rt);
                } else {
                    execute_store_32(*sf, *U, *L, *offset, *xn, *rt);
                }
            }

            free(sf); free(U); free(L); free(offset); free(xn); free(rt);
        } else {
            int *sf = malloc(sizeof(int)), *simm19 = malloc(sizeof(int));
            register_encoding_t *rt = malloc(sizeof(register_encoding_t));
            decode_load_literal(instruction, sf, simm19, rt);

            // Load Literal

            // Lines
            state.lines_state[9] = true;
            state.lines_state[10] = true;
            state.lines_state[58] = true;
            state.lines_state[29] = true;
            state.lines_state[19] = true;
            state.lines_state[20] = true;
            state.lines_state[23] = true;
            state.lines_state[26] = true;
            state.lines_state[25] = true;
            state.lines_state[24] = true;
            state.lines_state[5] = true;
            state.lines_state[4] = true;
            state.lines_state[3] = true;
            state.lines_state[38] = true;
            state.lines_state[0] = true;
            state.lines_state[55] = true;

            // Arrows
            state.arrows_state[11] = true;
            state.arrows_state[16] = true;
            state.arrows_state[18] = true;
            state.arrows_state[13] = true;
            state.arrows_state[17] = true;
            state.arrows_state[21] = true;
            state.arrows_state[22] = true;
            state.arrows_state[27] = true;
            state.arrows_state[31] = true;

            if (*sf == SF_64) { //load literal
                execute_load_literal_64(*sf, *simm19, *rt);
            } else {
                execute_load_literal_32(*sf, *simm19, *rt);
            }

            free(sf); free(simm19); free(rt);
        }

        return state;
    } else if ((instruction & OP0_BRANCH_MASK) == OP0_BRANCH_BIT_VALUE) {

        int *operand = malloc(sizeof(int));
        decode_branch(instruction, operand);

        int opc = uextract_bits(
            instruction,
            OPC_BRANCH_VALUE_1,
            OPC_BRANCH_VALUE_2
        );
        if (opc == OPC_BRANCH_UNCONDITIONAL_DECIMAL_VALUE ||
            opc == OPC_BRANCH_CONDITIONAL_DECIMAL_VALUE
        ) {
            // B and BCOND

            // Lines
            state.lines_state[21] = true;
            state.lines_state[16] = true;
            state.lines_state[13] = true;
            state.lines_state[59] = true;
            state.lines_state[51] = true;
            state.lines_state[52] = true;
            state.lines_state[2] = true;
            state.lines_state[1] = true;
            state.lines_state[57] = true;

            // Arrows
            state.arrows_state[26] = true;
            state.arrows_state[39] = true;
            state.arrows_state[1] = true;
            state.arrows_state[41] = true;
            state.arrows_state[2] = true;

            if (opc == OPC_BRANCH_UNCONDITIONAL_DECIMAL_VALUE) {
                execute_branch_unconditional(*operand);
            } else if (opc == OPC_BRANCH_CONDITIONAL_DECIMAL_VALUE) {
                execute_branch_conditional(*operand);
            }
        } else if (opc == OPC_BRANCH_REGISTER_DECIMAL_VALUE) {
            // BR

            // Lines
            state.lines_state[64] = true;
            state.lines_state[65] = true;
            state.lines_state[18] = true;
            state.lines_state[33] = true;
            state.lines_state[35] = true;
            state.lines_state[67] = true;
            state.lines_state[41] = true;
            state.lines_state[45] = true;
            state.lines_state[46] = true;
            state.lines_state[47] = true;
            state.lines_state[51] = true;
            state.lines_state[52] = true;
            state.lines_state[2] = true;
            state.lines_state[1] = true;
            state.lines_state[57] = true;

            // Arrows
            state.arrows_state[20] = true;
            state.arrows_state[23] = true;
            state.arrows_state[25] = true;
            state.arrows_state[29] = true;
            state.arrows_state[32] = true;
            state.arrows_state[34] = true;
            state.arrows_state[42] = true;
            state.arrows_state[37] = true;
            state.arrows_state[41] = true;
            state.arrows_state[2] = true;

            execute_branch_register(*operand);
        }

        free(operand);

        return state;
    } else {
        exit(EXIT_FAILURE);
        return state; // Unknown instruction
    }
}
