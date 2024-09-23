#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "framework.h"
#include "visual_emulator.h"

#if defined(_WIN32) || defined(_WIN64)
    #define ASSEMBLER_PATH "assemble.exe"
#elif defined(__APPLE__)
    #define ASSEMBLER_PATH "./assemble"
#elif defined(__linux__)
    #define ASSEMBLER_PATH "./assemble"
#endif

#define BLACK (SDL_Color){0, 0, 0, SDL_ALPHA_OPAQUE}
#define TEMP_BIN_PATH "temp.bin"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

int main(int argc, char *argv[]);