#include <stdbool.h>

#include "framework.h"
#include "draw.h"

extern bool reading_memory;

void show_memory(void);

void memory_process_events(SDL_Event event);

void close_memory_window(void);