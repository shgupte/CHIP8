
#include <fstream>
#include <iostream>
#include <chrono>
#include <cstdlib>
#include "raylib.h"
#include "Display.h"

class CPU {

private:
	//Constants
	const static int num_registers = 16;
	const static int ram_size = 4096;
	const static int stack_size = 16;

	const static int fontset_address0 = 0x50;
	const static int fontset_size = 80;
	//This is the spot in memory where the program expects to begin
	const static unsigned int starting_location = 0x200;

public:
	//Defining different parts of the emulator.
	uint8_t registers[num_registers];

	//Points to current instruction.
	uint16_t program_counter;

	//Memory
	uint8_t ram[ram_size];

	//Index???
	uint16_t index;

	//Stack for memory
	uint16_t stack[stack_size];
	uint8_t stack_pointer;

	//Timers
	uint8_t delayTimer;
	uint8_t soundTimer;

	uint16_t opcode;

	//unsigned int video[64][32];
	unsigned int video[64 * 32];

	//Class constructor
	CPU() {

		std::cout << "CPU created";

		program_counter = starting_location;

		// Load fonts into memory
		for (unsigned int i = 0; i < fontset_size; ++i)
		{
			ram[fontset_address0 + i] = fontset[i];
		}


	}

	~CPU() {
		std::cout << "CPU destroyed";
	}


	//This function reads the rom file and places it into the memory, starting at address 0x200.
	void readROM(char const* filename) {
		std::ifstream file(filename, std::ios::binary | std::ios::ate);
		std::cout << "Reading ROM...";
		if (file.is_open())
		{
			// Get size of file and allocate a buffer to hold the contents
			std::streampos size = file.tellg();
			std::cout << "test";
			char* buffer = new char[size];

			// Go back to the beginning of the file and fill the buffer
			file.seekg(0, std::ios::beg);
			file.read(buffer, size);
			file.close();

			// Load the ROM contents into the Chip8's memory, starting at 0x200
			for (long i = 0; i < size; ++i)
			{
				//std::cout << "Working";
				ram[starting_location + i] = buffer[i];
			}

			// Free the buffer
			delete[] buffer;
		}
	}

	uint8_t fontset[fontset_size] =
{
	0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
	0x20, 0x60, 0x20, 0x20, 0x70, // 1
	0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
	0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
	0x90, 0x90, 0xF0, 0x10, 0x10, // 4
	0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
	0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
	0xF0, 0x10, 0x20, 0x40, 0x40, // 7
	0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
	0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
	0xF0, 0x90, 0xF0, 0x90, 0x90, // A
	0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
	0xF0, 0x80, 0x80, 0x80, 0xF0, // C
	0xE0, 0x90, 0x90, 0x90, 0xE0, // D
	0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
	0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};



	////////////////////////////// FUNCTIONS ///////////////////////////////

	void execute() {
		//std::cout << ((opcode & 0xF000u) >> 12u) << " ";
		switch ((opcode & 0xF000u) >> 12u) {
			case 0:
				if (opcode == 0x00E0) {
					OP_00E0();
				}

			/* if (opcode == 0x00EE) {
					OP_00EE();
				} */

				//std::cout << " INS 0 ";
				break;
			case 1:
				OP_1NNN();
				//std::cout << " INS 1 ";
				break;
		/*	case 2:
				OP_2NNN();
				break;
			case 3:
				OP_3XKK();
				break;
			case 4: 
				OP_4XKK();
				break;
			case 5:
				OP_5XY0();
				break; */
			case 6:
				OP_6XKK();
				break;
			case 7:
				OP_7XKK();
				break;
		/*	case 8:
				runCorrectEight();
				break;
			case 9:
				OP_9XY0();
				break; */
			case 0xA:
				OP_ANNN();
				break;
		/*	case 0xB:
				OP_BNNN();
				break;
			case 0xC:
				OP_CXKK();
				break; */
			case 0xD:
				std::cout << "Drawing";
				OP_DXYN();
				break;
			/*case 0xF:
				runCorrectF();
				break; */
			default:
				std::cout << "Error. Instruction was called for but not found";
				std::cout << ((opcode & 0xF000u) >> 12u);
		}
	}

	void fetch() {
		uint16_t opc = (ram[program_counter] << 8) | ram[program_counter + 1]; //Maybe remove the OR
		program_counter += 2;
		opcode = opc;
		
	}

	void CycleCPU() {
		fetch();
		execute();
	}

	uint8_t randomByte() {
		return rand() % 256;
	}


	//Instructions:

	//Clear Screen
	void OP_00E0()
	{
		memset(video, 0, sizeof(video));
	}

	void runCorrectEight(){
		switch (opcode & 0x000F) {
			case 0:
				OP_8XY0();
				break;
			case 1:
				OP_8XY1();
				break;
			case 2:
				OP_8XY2();
				break;
			case 3:
				OP_8XY3();
				break;
			case 4:
				OP_8XY4();
				break;
			case 5: 
				OP_8XY5();
				break;
			case 6:
				OP_8XY6();
				break;
			case 7:
				OP_8XY7();
				break;
			default:
				break;
			}

	}

	void runCorrectF() {
		switch (opcode & 0x00FF) {
			case 0x07: 
				OP_FX07();
				break;
			case 0x15:
				OP_FX15();
				break;
			case 0x1E: 
				OP_FX1E();
				break;
			case 0x29:
				OP_FX29();
				break;
			case 0x33:
				OP_FX33();
				break;
			case 0x55:
				OP_FX55();
				break;
			case 0x65:
				OP_FX65();
				break;
		}
	}

	//Return from subroutine
	void OP_00EE() {
		//The stack pointer always points to the top of the stack.
		--stack_pointer;
		program_counter = stack[stack_pointer];
		
	}

	//Jump
	void OP_1NNN() {
		program_counter = opcode & 0x0FFF;
		//Only last 12 bits of this opcode represent instructions.
	}

	//What does the order need to be here?
	void OP_2NNN() {
		stack_pointer++;
		stack[stack_pointer] = program_counter;
		program_counter = opcode & 0x0FFF;
	}

	void OP_3XKK() {
		//Need to shift id over 8 bits so that it is 0000000000001111 not 0000111100000000, meaning it will be a small number
		unsigned int vx = (opcode & 0x0F00) >> 8;
		if (registers[vx] == (opcode & 0x00FF)) {
			//Skips the next instruction
			program_counter+=2;
		}
	}

	void OP_4XKK() {
		unsigned int vx = (opcode & 0x0F00) >> 8;
		if (registers[vx] != (opcode & 0x00FF)) {
			program_counter += 2;
		}
	}

	void OP_5XY0() {
		unsigned int vx = opcode & 0x0F00 >> 8;
		unsigned int vy = opcode & 0x00F0 >> 4;
		if (registers[vx] == registers[vy]) {
			program_counter += 2;
		}
	}

	void OP_6XKK() {
		unsigned int num = opcode & 0x00FF;
		unsigned int vx = opcode & 0x0F00 >> 8;
		registers[vx] = num;
	}

	void OP_7XKK() {
		unsigned int num = opcode & 0x00FF;
		unsigned int vx = opcode & 0x0F00 >> 8;
		registers[vx] = registers[vx] + num;
		
	}

	void OP_8XY0() {
		unsigned int vx = opcode & 0x0F00 >> 8;
		unsigned int vy = opcode & 0x00F0 >> 4;
		registers[vx] = registers[vy];
	}

	void OP_8XY1() {
		unsigned int vx = opcode & 0x0F00 >> 8;
		unsigned int vy = opcode & 0x00F0 >> 4;
		registers[vx] |= registers[vy];
	}

	void OP_8XY2() {
		unsigned int vx = opcode & 0x0F00 >> 8;
		unsigned int vy = opcode & 0x00F0 >> 4;
		registers[vx] &= registers[vy];
	}

	void OP_8XY3() {
		unsigned int vx = opcode & 0x0F00 >> 8;
		unsigned int vy = opcode & 0x00F0 >> 4;
		registers[vx] ^= registers[vy];
	}

	void OP_8XY4() {
		unsigned int vx = opcode & 0x0F00 >> 8;
		unsigned int vy = opcode & 0x00F0 >> 4;
		unsigned int sum = registers[vx] + registers[vy];

		if (sum > 255) {
			registers[0xF] = 1;
		} else {
			registers[0xF] = 0;
		}

		registers[vx] = sum & 0xFF;
	}

	void OP_8XY5() {
		unsigned int vx = opcode & 0x0F00 >> 8;
		unsigned int vy = opcode & 0x00F0 >> 4;
		if ((registers[vx] + registers[vy]) > 255) {
			registers[15] = 1;
		}
		else {
			registers[15] = 0;
		}
		registers[vx] = (registers[vx] + registers[vy]) & 0xFF;
	}

	void OP_8XY6() {
		unsigned int vx = opcode & 0x0F00 >> 8;
		if ((registers[vx] & 1) == 1) {
			registers[15] = 1;
		}
		else {
			registers[15] = 0;
		}
		//Shifting the entire thing to the right, effectively dividing by two and throwing out remainders.
		registers[vx] >>= 1;
	}

	void OP_8XY7() {
		unsigned int vx = opcode & 0x0F00 >> 8;
		unsigned int vy = opcode & 0x00F0 >> 4;
		registers[15] = (vy > vx) ? 1 : 0;
		registers[vx] = registers[vy] - registers[vx];
	}

	void OP_8XYE() {
		unsigned int vx = opcode & 0x0F00 >> 8;
		//Only anding the eight bit b/c the register is only 8 bits; then moving to right 7 times to get 1 or 0
		registers[15] = (registers[vx] & 0x80) >> 7;
		//Bit shift to the left is multiplication by 2.
		registers[vx] <<= 1;
	}

	void OP_9XY0() {
		unsigned int vx = opcode & 0x0F00 >> 8;
		unsigned int vy = opcode & 0x00F0 >> 4;
		if (registers[vx] != registers[vy]) {
			program_counter += 2;
		}
	}

	void OP_ANNN() {
		unsigned int val = opcode & 0x0FFF;
		index = val;
	}

	void OP_BNNN() {
		unsigned int val = opcode & 0x0FFF;
		program_counter = registers[0] + val;
	}

	void OP_CXKK() {
		uint8_t randVal = randomByte();
		unsigned int vx = opcode & 0x0F00 >> 8;
		unsigned int val = (opcode & 0x00FF) & randVal;
		registers[vx] = val;
	}

void OP_DXYN()
{
	uint8_t Vx = (opcode & 0x0F00u) >> 8u;
	uint8_t Vy = (opcode & 0x00F0u) >> 4u;
	uint8_t height = opcode & 0x000Fu;

	// Wrap if going beyond screen boundaries
	uint8_t xPos = registers[Vx] % 64;
	uint8_t yPos = registers[Vy] % 32 ;

	registers[0xF] = 0;

	for (unsigned int row = 0; row < height; ++row)
	{
		uint8_t spriteByte = ram[index + row];

		for (unsigned int col = 0; col < 8; ++col)
		{
			uint8_t spritePixel = spriteByte & (0x80u >> col);
			uint32_t* screenPixel = &video[(yPos + row) * 64 + (xPos + col)];

			// Sprite pixel is on
			if (spritePixel)
			{
				// Screen pixel also on - collision
				if (*screenPixel == 0xFFFFFFFF)
				{
					registers[0xF] = 1;
				}

				// Effectively XOR with the sprite pixel
				*screenPixel ^= 0xFFFFFFFF;
			}
		}
	}
}

/*
void opcodeDXYN()
{
    // Draws a sprite at coordinate (VX, VY)
    // that has a width of 8 pixels and a height of N+1 pixels.

    // n = height
	uint8_t Vx = (opcode & 0x0F00u) >> 8u;
	uint8_t Vy = (opcode & 0x00F0u) >> 4u;
    int n = (opcode & 0x000F);
    int width = 8;

    registers[0xF] = 0;

    for (int row = 0; row < n; row++)
    {
        // Get a row one of sprite data from the memory address in reg I (one byte per row)
        uint8_t spriteData = ram[index + row];

        // for each 8 pixels/bits in this sprite row
        for (int col = 0; col < width; col++)
        {
            // if the current pixel in the sprite row is on,
            // and the screen pixel at X,Y is on, set pixel to 0, set VF to 1
            if ((spriteData & 0x80) > 0)
            {
                int x = registers[Vx] + col;
                int y = registers[Vy] + row;

                if ((x >= 0 && x < 64) && (y >= 0 && y < 32))
                {
                    if (video[x][y] == 1)
                    {
                        registers[0xF] = 1;
                    }
                    video[x][y] ^= 1;
                }
            }
            // Point spriteData to the next bit
            spriteData <<= 1;
        }
    }
} */


void OP_FX07() {
	uint8_t vx = (opcode & 0x0F00u) >> 8u;
	
	registers[vx] = delayTimer;
}

void OP_FX15() {
	uint8_t vx = (opcode & 0x0F00u) >> 8u;
	
	delayTimer = registers[vx];
}

void OP_FX1E() {
	uint8_t vx = (opcode & 0x0F00u) >> 8u;
	index += registers[vx];
}

void OP_FX29() {
	uint8_t vx = (opcode & 0x0F00u) >> 8u;
	uint8_t digit = registers[vx];

	index = fontset_address0 + (5 * digit);
}

void OP_FX33() {
	uint8_t vx = (opcode & 0x0F00u) >> 8u;
	uint8_t value = registers[vx];

	ram[index + 2] = value % 10;
	value /= 10;

	ram[index + 1] = value % 10;
	value /= 10;

	ram[index] = value % 10;

}

void OP_FX55() {
	uint8_t vx = (opcode & 0x0F00u) >> 8u;

	for (uint8_t i = 0; i <= vx; ++i) {
		registers[i] = ram[index + i];
	}
}

void OP_FX65() {
	uint8_t vx = (opcode & 0x0F00u) >> 8u;

	for (uint8_t i = 0; i <= vx; ++i) {
		ram[index + i] = registers[i];
	}
}

};


int main(int argc, char* argv[])  {
	char const* filename = argv[1];
	CPU cpu = CPU();
    std::cout << "Program has started. You have selected to play " << filename << ".";
    std::cout<<(sizeof(cpu.video)/sizeof(cpu.video[0]));
	Display display = Display(20);
	cpu.readROM(filename);
	
	SetTargetFPS(5);
	while (!WindowShouldClose()) {
		cpu.CycleCPU();
		display.UpdateScreen(cpu.video);


		/*for (int i = 0; i < 32*64; ++i ){
			std::cout << " | " << cpu.video[i] << " | ";
		} */
	}
	return 0;
	
}