#include "main.h"

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    };

    if (TTF_Init() < 0) {
        printf(
            "SDL_ttf could not initialize! SDL_ttf Error: %s\n", 
            TTF_GetError()
        );
        return EXIT_FAILURE;
    };

    SDL_Window *window = SDL_CreateWindow(
        "Emulator Visualiser",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    TTF_Font *font = TTF_OpenFont("fonts/arial.ttf", 24);
    if (font == NULL) {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        return EXIT_FAILURE;
    }

    SDL_EnableScreenSaver();  // So the screen turns off

    // Initiliase drawing elements
    init_draw(window);
    button_t step_button = {
        .rect = STEP_BUTTON_RECT,
        .text = "Step",
        .callback = &step,
        .pressing = false
    };
    button_t memory_button = {
        .rect = MEMORY_BUTTON_RECT,
        .text = "Memory",
        .callback = &show_memory,
        .pressing = false
    };
    buttons[0] = &step_button;
    buttons[1] = &memory_button;

    // Draw main components
    circuit_state_t clear_state;
    initialise_state(&clear_state);
    // Drag and drop file please user
    put_text("Please drag and drop assembly file here.");
    put_state(&clear_state);
    draw_main_components();


    // Render everything
    render_everything();

    FILE *assembly_file = NULL;

    // Main loop
    SDL_Event event;
    while (1) {
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                break;
            }
            if (reading_memory) {
                memory_process_events(event);
                continue;
            }
            switch (event.type) {
                case SDL_MOUSEBUTTONDOWN:
                    // Check if the user has clicked on a button
                    if (event.button.button == SDL_BUTTON_LEFT && emulating) {
                        for (int i = 0; i < BUTTON_COUNT; i++) {
                            if (check_button_press(buttons[i], &event)) {
                                // Call corresponding button function
                                buttons[i]->pressing = true;
                                draw_main_components();
                                draw_register_values();
                                render_everything();
                                break;
                            }
                        }
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    // Check if the user has clicked on a button
                    if (event.button.button == SDL_BUTTON_LEFT && emulating) {
                        for (int i = 0; i < BUTTON_COUNT; i++) {
                            if (check_button_press(buttons[i], &event) &&
                                buttons[i]->pressing) {
                                // Call corresponding button function
                                buttons[i]->pressing = false;
                                buttons[i]->callback();
                                break;
                            } 
                            if (buttons[i]->pressing) {
                                buttons[i]->pressing = false;
                                draw_main_components();
                                draw_register_values();
                                render_everything();
                                break;
                            }
                        }
                    }
                    break;
                case SDL_DROPFILE:
                    // Method to receive assembly file
                    {
                        fclose(assembly_file);
                        SDL_RaiseWindow(window);  // Bring window to front

                        char *dropped_filedir = event.drop.file;

                        // Call assembler
                        char *assembler_command = malloc(
                            strlen(dropped_filedir) + 200
                        );

                        if (assembler_command != NULL) {
                            sprintf(
                                assembler_command,
                                "%s \"%s\" %s",
                                ASSEMBLER_PATH,
                                dropped_filedir,
                                TEMP_BIN_PATH
                            );
                            if (system(assembler_command) != 0) {
                                printf("Error assembling file\n");
                                free(assembler_command);
                                continue;
                            }
                            free(assembler_command);
                        } else {
                            printf(
                                "Error allocating memory for assembler command\n"
                            );
                            continue;
                        }

                        // Open assembler file for reading
                        assembly_file = fopen(dropped_filedir, "r");
                        if (assembly_file == NULL) {
                            printf("Error opening file\n");
                            continue;
                        }
                        init_disassemble(assembly_file);

                        // Open binary file for emulating
                        FILE *binary_file = fopen(TEMP_BIN_PATH, "rb");
                        if (binary_file == NULL) {
                            printf("Error opening binary file\n");
                            fclose(assembly_file);
                            continue;
                        }

                        // Run the modified version of emulator
                        setup();
                        initialise_memory(binary_file);
                        initialise_registers();
                        fclose(binary_file);

                        put_text("Received assembly file and successfully assembled, press Step to begin emulation.");
                        put_state(&clear_state);
                        draw_main_components();

                        render_everything();
                        break;
                    }
            }
        }
    }

    // Close memory window if it is open
    if (reading_memory) {
        close_memory_window();
    }

    // Close assembly file
    if (assembly_file != NULL) {
        fclose(assembly_file);
    }
    remove(TEMP_BIN_PATH);

    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
    
    return EXIT_SUCCESS;
}
