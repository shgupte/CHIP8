#pragma once


#include <fstream>
#include <iostream>
#include <chrono>
#include <cstdlib>

class CPU {

public:

	//Class constructor
	CPU();

	~CPU();

	////////////////////////////// FUNCTIONS ///////////////////////////////

    //This function reads the rom file and places it into the memory, starting at address 0x200.
    void readROM(char const* filename);

	void execute(uint16_t opc);

	uint16_t fetch();

	void cycleCPU();

}; 
/*
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

	uint8_t opcode;

	unsigned int video[64 * 32];

	//Class constructor
	CPU();

	~CPU();


	//This function reads the rom file and places it into the memory, starting at address 0x200.
	void readROM(char const* filename);

	uint8_t fontset[fontset_size];



	////////////////////////////// FUNCTIONS ///////////////////////////////

	void execute(uint16_t opc);

	uint16_t fetch();
	void cycleCPU();

	uint8_t randomByte();


	//Instructions:

	//Clear Screen
	void OP_00E0();

	//Return from subroutine
	void OP_00EE();

	//Jump
	void OP_1NNN();

	//What does the order need to be here?
	void OP_2NNN();

	void OP_3XKK();

	void OP_4XKK();

	void OP_5XY0();

	void OP_6XKK();

	void OP_7XKK();

	void OP_8XY0();

	void OP_8XY1();

	void OP_8XY2();

	void OP_8XY3();

	void OP_8XY4();

	void OP_8XY5();

	void OP_8XY6();

	void OP_8XY7();

	void OP_8XYE();

	void OP_9XY0();

	void OP_ANNN();

	void OP_BNNN();

	void OP_CXKK();

	void OP_DXYN();

}; */





