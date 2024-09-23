#include "button.h"

// A button_t array of fixed size to store the buttons
button_t *buttons[BUTTON_COUNT];

// Checking if a button is pressed using the button_t passed and 
// by the coordinates in the SDL_Event passed
bool check_button_press (button_t *button, SDL_Event *event) {
    return event->button.x >= button->rect.x && 
        event->button.x <= button->rect.x + button->rect.w &&
        event->button.y >= button->rect.y &&
        event->button.y <= button->rect.y + button->rect.h;
}