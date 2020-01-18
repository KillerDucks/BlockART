#pragma once

/**
 * block.hpp
 * This is a simple Class which can perform I/O on blocks
 * Author: KillerDucks
 * Licence: MIT
*/

#include <fstream>
#include <string>

using std::string;

#ifndef BLOCK_A_H
#define BLOCK_A_H

#define BLOCK_SUPER_B_0 0x53 
#define BLOCK_SUPER_B_1 0x55 
#define BLOCK_SUPER_B_2 0x42 
#define BLOCK_SUPER_B_3 0x4c 
constexpr auto BLOCK_SUPER_B_4 = 0x4b;

#define BLOCK_SUPER_NAME 15

#define BLOCK_MAX_SIZE 255

class Block_A
{
private:
	// SuperBlock
	typedef struct SuperBlock {
		char	padding[4];
		int		magic_0 = BLOCK_SUPER_B_0; // BLOCK_SUPER_B_0
		char	name[BLOCK_SUPER_NAME];
		int		magic_1 = BLOCK_SUPER_B_1; // BLOCK_SUPER_B_1
		int		blk_Size;
		int		magic_2 = BLOCK_SUPER_B_2; // BLOCK_SUPER_B_2
	} SUPERBLOCK, *PSUPERBLOCK;

	// Actual Data Block
	typedef struct Block {
		SuperBlock		sBlock;
		char			data[BLOCK_MAX_SIZE];
		int				magic_3 = BLOCK_SUPER_B_3; // BLOCK_SUPER_B_3
		char			exit_Statagey[BLOCK_SUPER_NAME];
		int				magic_4 = BLOCK_SUPER_B_4; // BLOCK_SUPER_B_4
	} BLOCK, *PBLOCK;

	char	SuperBlockName[BLOCK_SUPER_NAME] = "FFFFFFFFFFFFFF"; // [TODO] Change how the charArray is init.
	int		Block_Size = 0;

public:
	// Default constructor
	Block_A(char blockName[BLOCK_SUPER_NAME], int block_size);

	// Default deconstructor
	~Block_A();

	// Create
	bool Create();

	// Delete
	// PLACEHOLDER_FUNCTION();

	// Read
	int Read();
};

#endif