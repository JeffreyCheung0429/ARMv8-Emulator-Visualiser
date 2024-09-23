#include <stdbool.h>

#include "framework.h"

#define BUTTON_COUNT 2
#define STEP_BUTTON_RECT {.x = 1040, .y = 555, .w = 100, .h = 50}
#define MEMORY_BUTTON_RECT {.x = 1007, .y = 620, .w = 166, .h = 50}

typedef struct {
    SDL_Rect rect;
    char *text;
    void (*callback)();
    bool pressing;
} button_t;

extern button_t *buttons[BUTTON_COUNT];

bool check_button_press (button_t *button, SDL_Event *event);