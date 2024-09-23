#include "draw.h"

// Define the rectangles for the circuit components that
// will be drawn repeatedly
SDL_Rect pc_rect = PC_RECT;
SDL_Rect mux1_rect = MUX1_RECT;
SDL_Rect mem_rect = Mem_RECT;
SDL_Rect ir_rect = IR_RECT;
SDL_Rect mdr_rect = MDR_RECT;
SDL_Rect mux2_rect = MUX2_RECT;
SDL_Rect mux3_rect = MUX3_RECT;
SDL_Rect registers_rect = Registers_RECT;
SDL_Rect a_rect = A_RECT;
SDL_Rect b_rect = B_RECT;
SDL_Rect const4_rect = CONST4_RECT;
SDL_Rect mux4_rect = MUX4_RECT;
SDL_Rect mux5_rect = MUX5_RECT;
SDL_Rect sl2_rect = SL2_RECT;
SDL_Rect alu_rect = ALU_RECT;
SDL_Rect aluout_rect = ALUout_RECT;
SDL_Rect mux6_rect = MUX6_RECT;
SDL_Rect flags_rec = FLAGS_RECT;

// Declare the rectangles for the labels that will be drawn
SDL_Rect pc_box_rect;
SDL_Rect mux1_box_rect;
SDL_Rect mem_box_rect;
SDL_Rect mem_write_box_rect;
SDL_Rect mem_read_box_rect;
SDL_Rect address_box_rect;
SDL_Rect mem_write_data_box_rect;
SDL_Rect ir_box_rect;
SDL_Rect mdr_box_rect;
SDL_Rect mux2_box_rect;
SDL_Rect mux3_box_rect;
SDL_Rect registers_box_rect;
SDL_Rect read_reg_1_box_rect;
SDL_Rect read_reg_2_box_rect;
SDL_Rect write_reg_box_rect;
SDL_Rect write_data_box_rect;
SDL_Rect read_data_1_box_rect;
SDL_Rect read_data_2_box_rect;
SDL_Rect a_box_rect;
SDL_Rect b_box_rect;
SDL_Rect const4_box_rect;
SDL_Rect mux4_box_rect;
SDL_Rect mux5_box_rect;
SDL_Rect sl2_box_rect;
SDL_Rect alu_box_rect;
SDL_Rect aluout_box_rect;
SDL_Rect mux6_box_rect;
SDL_Rect flags_box_rect;
SDL_Rect ir_write_box_rect;
SDL_Rect reg_write_box_rect;
SDL_Rect alu_src_a_box_rect;
SDL_Rect alu_src_b_box_rect;
SDL_Rect alu_control_box_rect;
SDL_Rect pc_source_box_rect;
SDL_Rect reg_dst_box_rect;
SDL_Rect mem_to_reg_box_rect;
SDL_Rect i_or_d_box_rect;
SDL_Rect mem_data_box_rect;
SDL_Rect instruction_1_box_rect;
SDL_Rect instruction_2_box_rect;
SDL_Rect instruction_3_box_rect;
SDL_Rect alu_result_box_rect;

// Declare the textures for the labels
SDL_Texture *pc_box_texture;
SDL_Texture *mux1_box_texture;
SDL_Texture *mem_box_texture;
SDL_Texture *mem_write_box_texture;
SDL_Texture *mem_read_box_texture;
SDL_Texture *address_box_texture;
SDL_Texture *mem_write_data_box_texture;
SDL_Texture *ir_box_texture;
SDL_Texture *mdr_box_texture;
SDL_Texture *mux2_box_texture;
SDL_Texture *mux3_box_texture;
SDL_Texture *registers_box_texture;
SDL_Texture *read_reg_1_box_texture;
SDL_Texture *read_reg_2_box_texture;
SDL_Texture *write_reg_box_texture;
SDL_Texture *write_data_box_texture;
SDL_Texture *read_data_1_box_texture;
SDL_Texture *read_data_2_box_texture;
SDL_Texture *a_box_texture;
SDL_Texture *b_box_texture;
SDL_Texture *const4_box_texture;
SDL_Texture *mux4_box_texture;
SDL_Texture *mux5_box_texture;
SDL_Texture *sl2_box_texture;
SDL_Texture *alu_box_texture;
SDL_Texture *aluout_box_texture;
SDL_Texture *mux6_box_texture;
SDL_Texture *flags_box_texture;
SDL_Texture *ir_write_box_texture;
SDL_Texture *reg_write_box_texture;
SDL_Texture *alu_src_a_box_texture;
SDL_Texture *alu_src_b_box_texture;
SDL_Texture *alu_control_box_texture;
SDL_Texture *pc_source_box_texture;
SDL_Texture *reg_dst_box_texture;
SDL_Texture *mem_to_reg_box_texture;
SDL_Texture *i_or_d_box_texture;
SDL_Texture *mem_data_box_texture;
SDL_Texture *instruction_1_box_texture;
SDL_Texture *instruction_2_box_texture;
SDL_Texture *instruction_3_box_texture;
SDL_Texture *alu_result_box_texture;

// Other locally global variables
char *output_text_buffer = NULL;
circuit_state_t *state_buffer;
SDL_Renderer *renderer;
TTF_Font *arial_24;
TTF_Font *consolas_12;

// Helper function to center a box in a rectangle
SDL_Rect centeredBox(SDL_Rect rect, SDL_Surface *box) {
    return (SDL_Rect){
        rect.x + (rect.w - box->w) / 2,
        rect.y + (rect.h - box->h) / 2,
        box->w,
        box->h,
    };
}

// Initialize the drawing tools, and also get values of components that are
// going to be drawn repeatedly
void init_draw(SDL_Window *window) {
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_RenderClear(renderer);

    // Defining the Arial font of size 24
    arial_24 = TTF_OpenFont("fonts/arial.ttf", 24);
    if (arial_24 == NULL) {
        printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    // Defining the Consolas font of size 12
    consolas_12 = TTF_OpenFont("fonts/consola.ttf", 12);
    if (consolas_12 == NULL) {
        printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    // Opening the fonts
    TTF_Font *font = TTF_OpenFont("fonts/arial.ttf", 12);
    TTF_Font *small_font = TTF_OpenFont("fonts/arial.ttf", 8);

    // Render the PC
    SDL_Surface *pc_box = TTF_RenderText_Blended(font, "PC", BLACK);
    pc_box_texture = SDL_CreateTextureFromSurface(renderer, pc_box);
    pc_box_rect = centeredBox(pc_rect, pc_box);

    // Render MUX 1
    SDL_Surface *mux1_box = TTF_RenderText_Blended(font, "MUX", BLACK);
    mux1_box_texture = SDL_CreateTextureFromSurface(renderer, mux1_box);
    mux1_box_rect = centeredBox(mux1_rect, mux1_box);
    SDL_Surface *i_or_d_box = TTF_RenderText_Blended(small_font, "IorD", BLACK);
    i_or_d_box_texture = SDL_CreateTextureFromSurface(renderer, i_or_d_box);
    i_or_d_box_rect = centeredBox((SDL_Rect) {
        .x = mux1_rect.x + mux1_rect.w / 4,
        .y = mux1_rect.y + 5,
        .w = mux1_rect.w / 2,
        .h = i_or_d_box->h
    }, i_or_d_box);

    // Render Memory
    SDL_Surface *mem_box = TTF_RenderText_Blended(font, "MEM", BLACK);
    mem_box_texture = SDL_CreateTextureFromSurface(renderer, mem_box);
    mem_box_rect = centeredBox(mem_rect, mem_box);
    SDL_Surface *mem_read_box = TTF_RenderText_Blended(
        small_font,
        "MemRead",
        BLACK
    );
    mem_read_box_texture = SDL_CreateTextureFromSurface(renderer, mem_read_box);
    mem_read_box_rect = centeredBox((SDL_Rect) {
        .x = mem_rect.x - 5,
        .y = mem_rect.y - 5 - mem_read_box->h,
        .w = mem_rect.w / 2,
        .h = mem_read_box->h
    }, mem_read_box);
    SDL_Surface *mem_write_box = TTF_RenderText_Blended(
        small_font,
        "MemWrite",
        BLACK
    );
    mem_write_box_texture = SDL_CreateTextureFromSurface(
        renderer,
        mem_write_box
    );
    mem_write_box_rect = centeredBox((SDL_Rect) {
        .x = mem_rect.x + mem_rect.w / 2 + 5,
        .y = mem_rect.y - 5 - mem_write_box->h,
        .w = mem_rect.w / 2,
        .h = mem_write_box->h
    }, mem_write_box);
    SDL_Surface *address_box = TTF_RenderText_Blended(
        small_font,
        "Address",
        BLACK
    );
    address_box_texture = SDL_CreateTextureFromSurface(renderer, address_box);
    address_box_rect = (SDL_Rect) {
        .x = LINES[6].x2 + 5,
        .y = LINES[6].y1 - address_box->h / 2,
        .w = address_box->w,
        .h = address_box->h,
    };
    SDL_Surface *mem_write_data_box = TTF_RenderText_Blended(
        small_font,
        "Write Data",
        BLACK
    );
    mem_write_data_box_texture = SDL_CreateTextureFromSurface(
        renderer,
        mem_write_data_box
    );
    mem_write_data_box_rect = (SDL_Rect) {
        .x = LINES[11].x2 + 5,
        .y = LINES[11].y1 - mem_write_data_box->h / 2,
        .w = mem_write_data_box->w,
        .h = mem_write_data_box->h,
    };
    SDL_Surface *mem_data_box = TTF_RenderText_Blended(
        small_font,
        "MemData",
        BLACK
    );
    mem_data_box_texture = SDL_CreateTextureFromSurface(renderer, mem_data_box);
    mem_data_box_rect = (SDL_Rect) {
        .x = LINES[9].x1 - 5 - mem_data_box->w,
        .y = LINES[9].y1 - mem_data_box->h / 2,
        .w = mem_data_box->w,
        .h = mem_data_box->h,
    };

    // Render Instruction Register
    SDL_Surface *ir_box = TTF_RenderText_Blended(font, "IR", BLACK);
    ir_box_texture = SDL_CreateTextureFromSurface(renderer, ir_box);
    ir_box_rect = centeredBox(ir_rect, ir_box);
    SDL_Surface *ir_write_box = TTF_RenderText_Blended(
        small_font,
        "IRWrite",
        BLACK
    );
    ir_write_box_texture = SDL_CreateTextureFromSurface(renderer, ir_write_box);
    ir_write_box_rect = centeredBox((SDL_Rect) {
        .x = ir_rect.x + ir_rect.w / 4,
        .y = ir_rect.y + 5,
        .w = ir_rect.w / 2,
        .h = ir_write_box->h
    }, ir_write_box);
    SDL_Surface *instruction_1_box = TTF_RenderText_Blended(
        small_font,
        "Instruction",
        BLACK
    );
    instruction_1_box_texture = SDL_CreateTextureFromSurface(
        renderer,
        instruction_1_box
    );
    instruction_1_box_rect = (SDL_Rect) {
        .x = LINES[63].x1 - 5 - instruction_1_box->w,
        .y = LINES[63].y1 - instruction_1_box->h / 2,
        .w = instruction_1_box->w,
        .h = instruction_1_box->h,
    };
    SDL_Surface *instruction_2_box = TTF_RenderText_Blended(
        small_font,
        "Instruction",
        BLACK
    );
    instruction_2_box_texture = SDL_CreateTextureFromSurface(
        renderer,
        instruction_2_box
    );
    instruction_2_box_rect = (SDL_Rect) {
        .x = LINES[64].x1 - 5 - instruction_2_box->w,
        .y = LINES[64].y1 - instruction_2_box->h / 2,
        .w = instruction_2_box->w,
        .h = instruction_2_box->h,
    };
    SDL_Surface *instruction_3_box = TTF_RenderText_Blended(
        small_font,
        "Instruction",
        BLACK
    );
    instruction_3_box_texture = SDL_CreateTextureFromSurface(
        renderer,
        instruction_3_box
    );
    instruction_3_box_rect = (SDL_Rect) {
        .x = LINES[21].x1 - 5 - instruction_3_box->w,
        .y = LINES[21].y1 - instruction_3_box->h / 2,
        .w = instruction_3_box->w,
        .h = instruction_3_box->h,
    };

    // Render Memory Data Register
    SDL_Surface *mdr_box = TTF_RenderText_Blended(font, "MDR", BLACK);
    mdr_box_texture = SDL_CreateTextureFromSurface(renderer, mdr_box);
    mdr_box_rect = centeredBox(mdr_rect, mdr_box);

    // Render MUX 2
    SDL_Surface *mux2_box = TTF_RenderText_Blended(font, "MUX", BLACK);
    mux2_box_texture = SDL_CreateTextureFromSurface(renderer, mux2_box);
    mux2_box_rect = centeredBox(mux2_rect, mux2_box);
    SDL_Surface *mem_to_reg_box = TTF_RenderText_Blended(
        small_font,
        "MemtoReg",
        BLACK
    );
    mem_to_reg_box_texture = SDL_CreateTextureFromSurface(
        renderer,
        mem_to_reg_box
    );
    mem_to_reg_box_rect = centeredBox((SDL_Rect) {
        .x = mux2_rect.x + mux2_rect.w / 4,
        .y = mux2_rect.y + mux2_rect.h - 5 - mem_to_reg_box->h,
        .w = mux2_rect.w / 2,
        .h = mem_to_reg_box->h
    }, mem_to_reg_box);

    // Render MUX 3
    SDL_Surface *mux3_box = TTF_RenderText_Blended(font, "MUX", BLACK);
    mux3_box_texture = SDL_CreateTextureFromSurface(renderer, mux3_box);
    mux3_box_rect = centeredBox(mux3_rect, mux3_box);
    SDL_Surface *reg_dst_box = TTF_RenderText_Blended(
        small_font,
        "RegDst",
        BLACK
    );
    reg_dst_box_texture = SDL_CreateTextureFromSurface(renderer, reg_dst_box);
    reg_dst_box_rect = centeredBox((SDL_Rect) {
        .x = mux3_rect.x + mux3_rect.w / 4,
        .y = mux3_rect.y + 5,
        .w = mux3_rect.w / 2,
        .h = reg_dst_box->h
    }, reg_dst_box);

    // Render Registers
    SDL_Surface *registers_box = TTF_RenderText_Blended(
        font,
        "REGISTERS",
        BLACK
    );
    registers_box_texture = SDL_CreateTextureFromSurface(
        renderer,
        registers_box
    );
    registers_box_rect = centeredBox(registers_rect, registers_box);
    SDL_Surface *read_reg_1_box = TTF_RenderText_Blended(
        small_font,
        "ReadReg1",
        BLACK
    );
    read_reg_1_box_texture = SDL_CreateTextureFromSurface(
        renderer,
        read_reg_1_box
    );
    read_reg_1_box_rect = (SDL_Rect) {
        .x = LINES[17].x1 + 5,
        .y = LINES[17].y1 - read_reg_1_box->h / 2,
        .w = read_reg_1_box->w,
        .h = read_reg_1_box->h,
    };
    SDL_Surface *read_reg_2_box = TTF_RenderText_Blended(
        small_font,
        "ReadReg2",
        BLACK
    );
    read_reg_2_box_texture = SDL_CreateTextureFromSurface(
        renderer,
        read_reg_2_box
    );
    read_reg_2_box_rect = (SDL_Rect) {
        .x = LINES[18].x1 + 5,
        .y = LINES[18].y1 - read_reg_2_box->h / 2,
        .w = read_reg_2_box->w,
        .h = read_reg_2_box->h,
    };
    SDL_Surface *write_reg_box = TTF_RenderText_Blended(
        small_font,
        "WriteReg",
        BLACK
    );
    write_reg_box_texture = SDL_CreateTextureFromSurface(
        renderer,
        write_reg_box
    );
    write_reg_box_rect = (SDL_Rect) {
        .x = LINES[23].x2 + 5,
        .y = LINES[23].y1 - write_reg_box->h / 2,
        .w = write_reg_box->w,
        .h = write_reg_box->h,
    };
    SDL_Surface *write_data_box = TTF_RenderText_Blended(
        small_font,
        "Write Data",
        BLACK
    );
    write_data_box_texture = SDL_CreateTextureFromSurface(
        renderer,
        write_data_box
    );
    write_data_box_rect = (SDL_Rect) {
        .x = LINES[24].x2 + 5,
        .y = LINES[24].y1 - write_data_box->h / 2,
        .w = write_data_box->w,
        .h = write_data_box->h,
    };
    SDL_Surface *read_data_1_box = TTF_RenderText_Blended(
        small_font,
        "ReadData1",
        BLACK
    );
    read_data_1_box_texture = SDL_CreateTextureFromSurface(
        renderer,
        read_data_1_box
    );
    read_data_1_box_rect = (SDL_Rect) {
        .x = LINES[32].x1 - read_data_1_box->w - 5,
        .y = LINES[32].y1 - read_data_1_box->h / 2,
        .w = read_data_1_box->w,
        .h = read_data_1_box->h,
    };
    SDL_Surface *read_data_2_box = TTF_RenderText_Blended(
        small_font,
        "ReadData2",
        BLACK
    );
    read_data_2_box_texture = SDL_CreateTextureFromSurface(
        renderer,
        read_data_2_box
    );
    read_data_2_box_rect = (SDL_Rect) {
        .x = LINES[33].x1 - read_data_2_box->w - 5,
        .y = LINES[33].y1 - read_data_2_box->h / 2,
        .w = read_data_2_box->w,
        .h = read_data_2_box->h,
    };
    SDL_Surface *reg_write_box = TTF_RenderText_Blended(
        small_font,
        "RegWrite",
        BLACK
    );
    reg_write_box_texture = SDL_CreateTextureFromSurface(
        renderer,
        reg_write_box
    );
    reg_write_box_rect = centeredBox((SDL_Rect) {
        .x = registers_rect.x + registers_rect.w / 4,
        .y = registers_rect.y + 5,
        .w = registers_rect.w / 2,
        .h = reg_write_box->h
    }, reg_write_box);

    // Render A
    SDL_Surface *a_box = TTF_RenderText_Blended(font, "A", BLACK);
    a_box_texture = SDL_CreateTextureFromSurface(renderer, a_box);
    a_box_rect = centeredBox(a_rect, a_box);

    // Render B
    SDL_Surface *b_box = TTF_RenderText_Blended(font, "B", BLACK);
    b_box_texture = SDL_CreateTextureFromSurface(renderer, b_box);
    b_box_rect = centeredBox(b_rect, b_box);

    // Render Constant 4
    SDL_Surface *const4_box = TTF_RenderText_Blended(font, "4", BLACK);
    const4_box_texture = SDL_CreateTextureFromSurface(renderer, const4_box);
    const4_box_rect = centeredBox(const4_rect, const4_box);

    // Render MUX 4
    SDL_Surface *mux4_box = TTF_RenderText_Blended(font, "MUX", BLACK);
    mux4_box_texture = SDL_CreateTextureFromSurface(renderer, mux4_box);
    mux4_box_rect = centeredBox(mux4_rect, mux4_box);
    SDL_Surface *alu_src_a_box = TTF_RenderText_Blended(
        small_font,
        "ALUSrcA",
        BLACK
    );
    alu_src_a_box_texture = SDL_CreateTextureFromSurface(
        renderer,
        alu_src_a_box
    );
    alu_src_a_box_rect = centeredBox((SDL_Rect) {
        .x = mux4_rect.x + mux4_rect.w / 4,
        .y = mux4_rect.y + 5,
        .w = mux4_rect.w / 2,
        .h = alu_src_a_box->h
    }, alu_src_a_box);

    // Render MUX 5
    SDL_Surface *mux5_box = TTF_RenderText_Blended(font, "MUX", BLACK);
    mux5_box_texture = SDL_CreateTextureFromSurface(renderer, mux5_box);
    mux5_box_rect = centeredBox(mux5_rect, mux5_box);
    SDL_Surface *alu_src_b_box = TTF_RenderText_Blended(
        small_font,
        "ALUSrcB",
        BLACK
    );
    alu_src_b_box_texture = SDL_CreateTextureFromSurface(
        renderer,
        alu_src_b_box
    );
    alu_src_b_box_rect = centeredBox((SDL_Rect) {
        .x = mux5_rect.x + mux5_rect.w / 4,
        .y = mux5_rect.y + mux5_rect.h - 5 - alu_src_b_box->h,
        .w = mux5_rect.w / 2,
        .h = alu_src_b_box->h
    }, alu_src_b_box);

    // Render Shift Left 2
    SDL_Surface *sl2_box = TTF_RenderText_Blended(font, "SL2", BLACK);
    sl2_box_texture = SDL_CreateTextureFromSurface(renderer, sl2_box);
    sl2_box_rect = centeredBox(sl2_rect, sl2_box);

    // Render Arithmetic Logic Unit
    SDL_Surface *alu_box = TTF_RenderText_Blended(font, "ALU", BLACK);
    alu_box_texture = SDL_CreateTextureFromSurface(renderer, alu_box);
    alu_box_rect = centeredBox(alu_rect, alu_box);
    SDL_Surface *alu_control_box = TTF_RenderText_Blended(
        small_font,
        "ALU Control",
        BLACK
    );
    alu_control_box_texture = SDL_CreateTextureFromSurface(
        renderer,
        alu_control_box
    );
    alu_control_box_rect = centeredBox((SDL_Rect) {
        .x = alu_rect.x + alu_rect.w / 4,
        .y = alu_rect.y + alu_rect.h - 5 - alu_control_box->h,
        .w = alu_rect.w / 2,
        .h = alu_control_box->h
    }, alu_control_box);
    SDL_Surface *alu_result_box = TTF_RenderText_Blended(
        small_font,
        "ALU result",
        BLACK
    );
    alu_result_box_texture = SDL_CreateTextureFromSurface(
        renderer,
        alu_result_box
    );
    alu_result_box_rect = (SDL_Rect) {
        .x = LINES[45].x1 - alu_result_box->w - 5,
        .y = LINES[45].y1 - alu_result_box->h / 2,
        .w = alu_result_box->w,
        .h = alu_result_box->h,
    };

    // Render Arithmetic Logic Unit Out
    SDL_Surface *aluout_box = TTF_RenderText_Blended(font, "ALUOUT", BLACK);
    aluout_box_texture = SDL_CreateTextureFromSurface(renderer, aluout_box);
    aluout_box_rect = centeredBox(aluout_rect, aluout_box);

    // Render MUX 6
    SDL_Surface *mux6_box = TTF_RenderText_Blended(font, "MUX", BLACK);
    mux6_box_texture = SDL_CreateTextureFromSurface(renderer, mux6_box);
    mux6_box_rect = centeredBox(mux6_rect, mux6_box);
    SDL_Surface *pc_source_box = TTF_RenderText_Blended(
        small_font,
        "PCSource",
        BLACK
    );
    pc_source_box_texture = SDL_CreateTextureFromSurface(
        renderer,
        pc_source_box
    );
    pc_source_box_rect = centeredBox((SDL_Rect) {
        .x = mux6_rect.x + mux6_rect.w / 4,
        .y = mux6_rect.y - 5 - pc_source_box->h,
        .w = mux6_rect.w / 2,
        .h = pc_source_box->h
    }, pc_source_box);

    // Render Flags
    SDL_Surface *flags_box = TTF_RenderText_Blended(font, "FLAGS", BLACK);
    flags_box_texture = SDL_CreateTextureFromSurface(renderer, flags_box);
    flags_box_rect = centeredBox(flags_rec, flags_box);

    // Free all temp surfaces
    SDL_FreeSurface(pc_box);
    SDL_FreeSurface(mux1_box);
    SDL_FreeSurface(mem_box);
    SDL_FreeSurface(mem_write_box);
    SDL_FreeSurface(mem_read_box);
    SDL_FreeSurface(address_box);
    SDL_FreeSurface(mem_write_data_box);
    SDL_FreeSurface(ir_box);
    SDL_FreeSurface(mdr_box);
    SDL_FreeSurface(mux2_box);
    SDL_FreeSurface(mux3_box);
    SDL_FreeSurface(registers_box);
    SDL_FreeSurface(read_reg_1_box);
    SDL_FreeSurface(read_reg_2_box);
    SDL_FreeSurface(write_reg_box);
    SDL_FreeSurface(write_data_box);
    SDL_FreeSurface(read_data_1_box);
    SDL_FreeSurface(read_data_2_box);
    SDL_FreeSurface(a_box);
    SDL_FreeSurface(b_box);
    SDL_FreeSurface(const4_box);
    SDL_FreeSurface(mux4_box);
    SDL_FreeSurface(mux5_box);
    SDL_FreeSurface(sl2_box);
    SDL_FreeSurface(alu_box);
    SDL_FreeSurface(aluout_box);
    SDL_FreeSurface(mux6_box);
    SDL_FreeSurface(flags_box);
    SDL_FreeSurface(ir_write_box);
    SDL_FreeSurface(reg_write_box);
    SDL_FreeSurface(alu_src_a_box);
    SDL_FreeSurface(alu_src_b_box);
    SDL_FreeSurface(alu_control_box);
    SDL_FreeSurface(pc_source_box);
    SDL_FreeSurface(reg_dst_box);
    SDL_FreeSurface(mem_to_reg_box);
    SDL_FreeSurface(i_or_d_box);
    SDL_FreeSurface(mem_data_box);
    SDL_FreeSurface(instruction_1_box);
    SDL_FreeSurface(instruction_2_box);
    SDL_FreeSurface(instruction_3_box);
    SDL_FreeSurface(alu_result_box);
}

// Update output text buffer
void put_text(char *output_text) {
    output_text_buffer = output_text;
}

// Update state buffer
void put_state(circuit_state_t *state) {
    state_buffer = state;
}

// Draw the output text
void draw_output_text(void) {
    if (output_text_buffer == NULL) {
        return;
    }
    SDL_Surface *output_text = TTF_RenderText_Blended(
        arial_24,
        output_text_buffer,
        BLACK
    );
    SDL_Texture *output_texture = SDL_CreateTextureFromSurface(
        renderer,
        output_text
    );
    SDL_Rect output_rect = {
        .x = 25,
        .y = 620,
        .w = output_text->w,
        .h = output_text->h
    };
    SDL_RenderCopy(renderer, output_texture, NULL, &output_rect);

    SDL_FreeSurface(output_text);
    SDL_DestroyTexture(output_texture);
}

// Draw the current state of the registers for debugging
void draw_register_values(void) {
    char *register_output = output_registers();
    SDL_Surface *registers_text = TTF_RenderText_Blended_Wrapped(
        consolas_12,
        register_output,
        BLACK,
        0
    );
    SDL_Texture *registers_texture = SDL_CreateTextureFromSurface(
        renderer,
        registers_text
    );
    SDL_Rect registers_rect = {
        .x = 1005,
        .y = 30,
        .w = registers_text->w,
        .h = registers_text->h
    };
    SDL_RenderCopy(renderer, registers_texture, NULL, &registers_rect);

    free(register_output);
    SDL_FreeSurface(registers_text);
    SDL_DestroyTexture(registers_texture);
}

// Create new window to display memory values
void draw_memory_values(SDL_Window *memory_window) {
    SDL_Renderer *memory_renderer = SDL_CreateRenderer(
        memory_window,
        -1,
        SDL_RENDERER_ACCELERATED
    );
    if (memory_renderer == NULL) {
        printf(
            "Renderer could not be created! SDL_Error: %s\n",
            SDL_GetError()
        );
        exit(EXIT_FAILURE);
    }
    SDL_RenderClear(memory_renderer);
    SDL_SetRenderDrawColor(memory_renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(memory_renderer, NULL);

    char *memory_output = output_memory();
    SDL_Surface *memory_text = TTF_RenderText_Blended_Wrapped(
        consolas_12,
        memory_output,
        BLACK,
        0
    );
    SDL_Texture *memory_texture = SDL_CreateTextureFromSurface(
        memory_renderer,
        memory_text
    );
    SDL_Rect memory_rect = {
        .x = 15,
        .y = 15,
        .w = memory_text->w,
        .h = memory_text->h
    };
    SDL_RenderCopy(memory_renderer, memory_texture, NULL, &memory_rect);
    SDL_RenderPresent(memory_renderer);

    free(memory_output);
    SDL_FreeSurface(memory_text);
    SDL_DestroyTexture(memory_texture);
}

// Draw the main circuit graph
void draw_circuit_graph(circuit_state_t state) {
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);

    // Circuit border
    SDL_Rect rect = CIRCUIT_BORDER;
    SDL_RenderDrawRect(renderer, &rect);

    // Draw all the boxes
    SDL_SetRenderDrawColor(renderer, 0x00, 0x34, 0x59, SDL_ALPHA_OPAQUE);
    TTF_Font *font = TTF_OpenFont("fonts/arial.ttf", 12);

    SDL_RenderDrawRect(renderer, &pc_rect);
    SDL_RenderCopy(renderer, pc_box_texture, NULL, &pc_box_rect);

    // Draw PC
    char pc_value[22];
    sprintf(pc_value, "PC = %016" PRIx64 "", PC);
    SDL_Surface *pc_value_text = TTF_RenderText_Blended(font, pc_value, BLACK);
    SDL_Texture *pc_value_texture = SDL_CreateTextureFromSurface(
        renderer,
        pc_value_text
    );
    SDL_Rect pc_value_rect = {
        .x = pc_box_rect.x,
        .y = 72,
        .w = pc_value_text->w,
        .h = pc_value_text->h
    };
    SDL_RenderCopy(renderer, pc_value_texture, NULL, &pc_value_rect);
    SDL_FreeSurface(pc_value_text);
    SDL_DestroyTexture(pc_value_texture);

    // Draw MUX 1
    SDL_RenderDrawRect(renderer, &mux1_rect);
    SDL_RenderCopy(renderer, mux1_box_texture, NULL, &mux1_box_rect);
    SDL_RenderCopy(renderer, i_or_d_box_texture, NULL, &i_or_d_box_rect);

    // Draw Memory
    SDL_RenderDrawRect(renderer, &mem_rect);
    SDL_RenderCopy(renderer, mem_box_texture, NULL, &mem_box_rect);
    SDL_RenderCopy(renderer, mem_read_box_texture, NULL, &mem_read_box_rect);
    SDL_RenderCopy(renderer, mem_write_box_texture, NULL, &mem_write_box_rect);
    SDL_RenderCopy(renderer, address_box_texture, NULL, &address_box_rect);
    SDL_RenderCopy(
        renderer,
        mem_write_data_box_texture,
        NULL,
        &mem_write_data_box_rect
    );
    SDL_RenderCopy(renderer, mem_data_box_texture, NULL, &mem_data_box_rect);

    // Draw Instruction Register
    SDL_RenderDrawRect(renderer, &ir_rect);
    SDL_RenderCopy(renderer, ir_box_texture, NULL, &ir_box_rect);
    SDL_RenderCopy(renderer, ir_write_box_texture, NULL, &ir_write_box_rect);
    SDL_RenderCopy(
        renderer,
        instruction_1_box_texture,
        NULL,
        &instruction_1_box_rect
    );
    SDL_RenderCopy(
        renderer,
        instruction_2_box_texture,
        NULL,
        &instruction_2_box_rect
    );
    SDL_RenderCopy(
        renderer,
        instruction_3_box_texture,
        NULL,
        &instruction_3_box_rect
    );

    // Draw Memory Data Register
    SDL_RenderDrawRect(renderer, &mdr_rect);
    SDL_RenderCopy(renderer, mdr_box_texture, NULL, &mdr_box_rect);

    // Draw MUX 2
    SDL_RenderDrawRect(renderer, &mux2_rect);
    SDL_RenderCopy(renderer, mux2_box_texture, NULL, &mux2_box_rect);
    SDL_RenderCopy(
        renderer,
        mem_to_reg_box_texture,
        NULL,
        &mem_to_reg_box_rect
    );

    // Draw MUX 3
    SDL_RenderDrawRect(renderer, &mux3_rect);
    SDL_RenderCopy(renderer, mux3_box_texture, NULL, &mux3_box_rect);
    SDL_RenderCopy(renderer, reg_dst_box_texture, NULL, &reg_dst_box_rect);

    // Draw Registers
    SDL_RenderDrawRect(renderer, &registers_rect);
    SDL_RenderCopy(renderer, registers_box_texture, NULL, &registers_box_rect);
    SDL_RenderCopy(
        renderer,
        read_reg_1_box_texture,
        NULL,
        &read_reg_1_box_rect
    );
    SDL_RenderCopy(
        renderer,
        read_reg_2_box_texture,
        NULL,
        &read_reg_2_box_rect
    );
    SDL_RenderCopy(renderer, write_reg_box_texture, NULL, &write_reg_box_rect);
    SDL_RenderCopy(
        renderer,
        write_data_box_texture,
        NULL,
        &write_data_box_rect
    );
    SDL_RenderCopy(
        renderer,
        read_data_1_box_texture,
        NULL,
        &read_data_1_box_rect
    );
    SDL_RenderCopy(
        renderer,
        read_data_2_box_texture,
        NULL,
        &read_data_2_box_rect
    );
    SDL_RenderCopy(renderer, reg_write_box_texture, NULL, &reg_write_box_rect);

    // Draw A
    SDL_RenderDrawRect(renderer, &a_rect);
    SDL_RenderCopy(renderer, a_box_texture, NULL, &a_box_rect);

    // Draw B
    SDL_RenderDrawRect(renderer, &b_rect);
    SDL_RenderCopy(renderer, b_box_texture, NULL, &b_box_rect);

    // Draw Constant 4
    SDL_RenderDrawRect(renderer, &const4_rect);
    SDL_RenderCopy(renderer, const4_box_texture, NULL, &const4_box_rect);

    // Draw MUX 4
    SDL_RenderDrawRect(renderer, &mux4_rect);
    SDL_RenderCopy(renderer, mux4_box_texture, NULL, &mux4_box_rect);
    SDL_RenderCopy(renderer, alu_src_a_box_texture, NULL, &alu_src_a_box_rect);

    // Draw MUX 5
    SDL_RenderDrawRect(renderer, &mux5_rect);
    SDL_RenderCopy(renderer, mux5_box_texture, NULL, &mux5_box_rect);
    SDL_RenderCopy(renderer, alu_src_b_box_texture, NULL, &alu_src_b_box_rect);

    // Draw Shift Left 2
    SDL_RenderDrawRect(renderer, &sl2_rect);
    SDL_RenderCopy(renderer, sl2_box_texture, NULL, &sl2_box_rect);

    // Draw Arithmetic Logic Unit
    SDL_RenderDrawRect(renderer, &alu_rect);
    SDL_RenderCopy(renderer, alu_box_texture, NULL, &alu_box_rect);
    SDL_RenderCopy(
        renderer,
        alu_control_box_texture,
        NULL,
        &alu_control_box_rect
    );
    SDL_RenderCopy(
        renderer,
        alu_result_box_texture,
        NULL,
        &alu_result_box_rect
    );

    // Draw Arithmetic Logic Unit Out
    SDL_RenderDrawRect(renderer, &aluout_rect);
    SDL_RenderCopy(renderer, aluout_box_texture, NULL, &aluout_box_rect);

    // Draw MUX 6
    SDL_RenderDrawRect(renderer, &mux6_rect);
    SDL_RenderCopy(renderer, mux6_box_texture, NULL, &mux6_box_rect);
    SDL_RenderCopy(renderer, pc_source_box_texture, NULL, &pc_source_box_rect);

    // Draw Flags
    SDL_RenderDrawRect(renderer, &flags_rec);
    SDL_RenderCopy(renderer, flags_box_texture, NULL, &flags_box_rect);

    // Draw all the lines

    // Draw inactive lines first:
    SDL_SetRenderDrawColor(renderer, 0x00, 0x34, 0x59, SDL_ALPHA_OPAQUE);
    for (int i = 0; i < LINES_STATE_SIZE; i++) {
        if (!state.lines_state[i]) {
            SDL_RenderDrawLine(
                renderer,
                LINES[i].x1,
                LINES[i].y1,
                LINES[i].x2,
                LINES[i].y2
            );
        }
    }
    // Draw active lines then:
    SDL_SetRenderDrawColor(renderer, 0x9B, 0x00, 0x00, SDL_ALPHA_OPAQUE);
    for (int i = 0; i < LINES_STATE_SIZE; i++) {
        if (state.lines_state[i]) {
            SDL_RenderDrawLine(
                renderer,
                LINES[i].x1,
                LINES[i].y1,
                LINES[i].x2,
                LINES[i].y2
            );
        }
    }

    // Draw Arrows

    // Draw active arrows then:
    for (int i = 0; i < ARROWS_STATE_SIZE; i++) {
        if (state.arrows_state[i]) {
            draw_arrow(ARROWS[i]);
        }
    }

    // Draw inactive arrows then:
    SDL_SetRenderDrawColor(renderer, 0x00, 0x34, 0x59, SDL_ALPHA_OPAQUE);
    for (int i = 0; i < ARROWS_STATE_SIZE; i++) {
        if (!state.arrows_state[i]) {
            draw_arrow(ARROWS[i]);
        }
    }

    // Draw dots
    for (int i = 0; i < DOTS_SIZE; i++) {
        SDL_RenderFillRect(renderer, &DOTS[i]);
    }

    TTF_CloseFont(font);

    return;
}

// Custom function that draws arrow
void draw_arrow(arrow_t arrow) {
    SDL_RenderDrawLine(
        renderer,
        arrow.line1.x1,
        arrow.line1.y1,
        arrow.line1.x2,
        arrow.line1.y2
    );
    SDL_RenderDrawLine(
        renderer,
        arrow.line2.x1,
        arrow.line2.y1,
        arrow.line2.x2,
        arrow.line2.y2
    );
}

// Custome function that draws button
void draw_button(button_t *button) {
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
    int offset;
    if (button->pressing) {
        offset = 2;
    } else {
        offset = 5;
    }
    SDL_Rect offset_rect = (SDL_Rect){
        .x = button->rect.x + offset,
        .y = button->rect.y - offset,
        .w = button->rect.w,
        .h = button->rect.h
    };
    SDL_RenderDrawRect(renderer, &offset_rect);
    SDL_RenderDrawLine(
        renderer,
        button->rect.x,
        button->rect.y,
        offset_rect.x,
        offset_rect.y
    );
    SDL_RenderDrawLine(
        renderer,
        button->rect.x,
        button->rect.y,
        button->rect.x,
        button->rect.y + button->rect.h
    );
    SDL_RenderDrawLine(
        renderer,
        button->rect.x,
        button->rect.y + button->rect.h,
        offset_rect.x,
        offset_rect.y + offset_rect.h
    );
    SDL_RenderDrawLine(
        renderer,
        button->rect.x,
        button->rect.y + button->rect.h,
        button->rect.x + button->rect.w,
        button->rect.y + button->rect.h
    );
    SDL_RenderDrawLine(
        renderer,
        button->rect.x + button->rect.w,
        button->rect.y + button->rect.h,
        offset_rect.x + offset_rect.w,
        offset_rect.y + offset_rect.h
    );

    SDL_Surface *text_surface = TTF_RenderText_Blended(
        arial_24,
        button->text,
        (SDL_Color){0, 0, 0, SDL_ALPHA_OPAQUE}
    );
    SDL_Texture *text_texture = SDL_CreateTextureFromSurface(
        renderer,
        text_surface
    );

    SDL_Rect text_rect = {
        .x = offset_rect.x + offset_rect.w / 2 - text_surface->w / 2,
        .y = offset_rect.y + offset_rect.h / 2 - text_surface->h / 2,
        .w = text_surface->w,
        .h = text_surface->h
    };

    SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);

    SDL_FreeSurface(text_surface);
    SDL_DestroyTexture(text_texture);

    return;
}

// Draw the main components of the window
void draw_main_components(void) {
    // Fill background with white
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, NULL);

    // Draw buttons
    for (int i = 0; i < BUTTON_COUNT; i++) {
        draw_button(buttons[i]);
    }

    // Draw circuit layout
    draw_circuit_graph(*state_buffer);

    // Draw output text
    draw_output_text();

    return;
}

// Render everything to the screen, 'presenting' it to the user
void render_everything(void) {
    SDL_RenderPresent(renderer);
}
