#include <stdio.h>

#include "framework.h"

#define LINE_COUNT 60
#define LINE_LENGTH 60

void init_disassemble(FILE *file);

char *disassemble(uint64_t pc);