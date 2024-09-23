#include "visual_emulator.h"

// Make an alternating signal as all instructions are one cycle
bool fetching = true;

// Show that if the emulator is running
bool emulating = false;

static circuit_state_t INCREMENT_PC_STATE = {
    //5, 4, 3, 38, 0, 55, 40, 45, 46, 47, 51, 52, 2, 1, 57, 36, 41, 61, 6, 9, 62
    .lines_state = {
        true, true, true, true, true, true, true, false, false, true,
        false, false, false, false, false, false, false, false, false, false,
        false, false, false, false, false, false, false, false, false, false,
        false, false, false, false, false, false, true, false, true, false,
        true, true, false, false, false, true, true, true, false, false,
        false, true, true, false, false, true, false, true, false, false,
        false, true, true, false, false, false, false, false, false, false,
        false, false, false
    }, 
    // 1, 2, 27, 31, 33, 37, 30, 32, 34, 41, 3, 5, 6, 8, 10
    .arrows_state = {
        false, true, true, true, false, true, true, false, true, false,
        true, false, true, false, false, false, false, false, false, false, 
        false, false, false, false, false, false, false, true, false, false,
        true, true, true, true, true, false, false, true, false, false,
        false, true, true, false
    },
};

// Step function to be called when step button is press, 
// runs the next cycle in the processer
void step(void) {
    circuit_state_t state;
    if (!fetching) {
        // Now update PC
        update_PC();
        fetching = true;
        put_text("Incrementing PC");
        put_state(&INCREMENT_PC_STATE);
        draw_main_components();
        draw_register_values();
        render_everything();
    } else {
        // Now run instruction
        fetching = false;
        instruction_t instruction = fetch();
        if (instruction == HALT_INSTRUCTION) {
            emulating = false;
            circuit_state_t clear_state;
            initialise_state(&clear_state);
            put_text("Halted. Please Drag and drop assembly file to run again.");
            put_state(&clear_state);
            draw_main_components();
            render_everything();
            return;
        }
        char *instruction_text = disassemble(PC);
        state = process_instruction(instruction);
        if (PC_branched) {
            update_PC();
            fetching = true;
        }
        put_text(instruction_text);
        put_state(&state);
        draw_main_components();
        draw_register_values();
        render_everything();
    }
}

// Setup when a new file is loaded
void setup(void) {
    fetching = true;
    emulating = true;
}