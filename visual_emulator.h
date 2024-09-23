#include <stdbool.h>
#include <stdint.h>

#include "disassembler.h"
#include "memory_window.h"

extern bool PC_branched;

extern bool emulating;

void step(void);

void setup(void);