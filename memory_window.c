#include "memory_window.h"

bool reading_memory = false;

SDL_Window *memory_window;

// Initiate the memory window
void show_memory(void) {
    reading_memory = true;
    memory_window = SDL_CreateWindow(
        "Memory", 
        SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED, 
        200, 
        720, 
        SDL_WINDOW_SHOWN
    );
    draw_memory_values(memory_window);
}

// Event loop for the memory window
void memory_process_events(SDL_Event event) {
    if (event.window.windowID != SDL_GetWindowID(memory_window)) {
        SDL_RaiseWindow(memory_window);
    } else if (event.type == SDL_WINDOWEVENT &&
        event.window.event == SDL_WINDOWEVENT_CLOSE) {
        close_memory_window();
    }
}

void close_memory_window(void) {
    reading_memory = false;
    SDL_DestroyWindow(memory_window);

    // Redraw the main window
    draw_main_components();
    draw_register_values();
    render_everything();
}