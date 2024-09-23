#include "disassembler.h"

// Store the lines of the original file in 2D array
char line[LINE_COUNT][LINE_LENGTH];

void init_disassemble(FILE *file) {
    // This is not the right implementation and will fail when
    // branching later written instructions,
    // but due to time constraints, I chose this implementation
    rewind(file);
    int lines = 0;

    while (fgets(line[lines], sizeof(line[lines]), file) != NULL) {
        size_t len = strlen(line[lines]);
        
        // Ignore empty lines
        if (len == 1) {
            continue;
        }

        // Remove new line character
        while (
            line[lines][len - 1] == '\n' ||
            line[lines][len - 1] == ' '
        ) {
            line[lines][len - 1] = '\0';
            len--;
        }
        
        // Ignore lines with only labels
        if (line[lines][len - 1] == ':') {
            continue;
        }

        lines++;

        if (lines == LINE_COUNT) {
            break;
        }
    }
}

// Return line associated with the program counter value in the original file
char *disassemble(uint64_t pc) {
    if (pc / 4 >= LINE_COUNT) {
        return NULL;
    }
    return line[pc / 4];
}