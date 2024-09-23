### C Project Extension (Emulator Visualiser)

#### Running the Visualiser:

##### Windows
1. Drag and drop your assembler executable into this folder (extension) 
2. Run the executable by `./main.exe`
3. Drag and drop your assembly file into the application
4. Click on `Step` to execute and see the next instruction
5. Click on `Memory` to view the memory state

##### MacOS
1. Drag and drop your assembler executable into this folder (extension)  
2. Run the executable by `./main`
3. Drag and drop your assembly file into the application
4. Click on `Step` to execute and see the next instruction
5. Click on `Memory` to view the memory state

##### Linux
We have not provided an executable for the Linux OS as we were not able to install the SDL2 and SDL2_ttf libraries on the Lab Machines.

1. Drag and drop your assembler executable into this folder (extension) 
2. Install the `SDL2` Library [here](https://www.libsdl.org/)
3. Install the `SDL2_ttf` Library [here](https://www.libsdl.org/projects/SDL_ttf/release/)
4. Compile the executable by, ensure to change `your_SDL2_path` and `your_SDL2_ttf_path` to your actual path to `SDL2` and `SDL2_ttf`
```
gcc *.c ../src/emulator_decode.c ../src/emulator_execute.c ../src/emulator_instructions.c ../src/emulator_memory.c ../src/emulator_registers.c -o main \
-I/your_SDL2_path/include/SDL2 \
-I/your_SDL2_ttf_path/include/SDL2 \
-L/your_SDL2_path/lib \
-L/your_SDL2_ttf_path/lib \
-lSDL2 -lSDL2_ttf
```
5.  Run the executable by `./main`
6. Drag and drop your assembly file into the application
7. Click on `Step` to execute and see the next instruction
8. Click on `Memory` to view the memory state
