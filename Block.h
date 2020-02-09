#pragma once

/**
 * block.h
 * This is a simple Class which can perform I/O on blocks
 * Author: KillerDucks
 * Licence: MIT
*/

#include <fstream>
#include <string>
#include <vector>

//#include "Block_Data.h"

using std::string;

#ifndef BLOCK_A_H
#define BLOCK_A_H

constexpr unsigned char BLOCK_SUPER_B_0 = 0x53;
constexpr unsigned char BLOCK_SUPER_B_1 = 0x55;
constexpr unsigned char BLOCK_SUPER_B_2 = 0x42;
constexpr unsigned char BLOCK_SUPER_B_3 = 0x4c;
constexpr unsigned char BLOCK_SUPER_B_4 = 0x4b;

constexpr unsigned char BLOCK_PADDING = 0x00;

		// Macros //
// Block Super Name Length
#define BLOCK_SUPER_NAME 15

// Block Tag Settings
#define BLOCK_MAX_TAGS 5
#define BLOCK_MAX_TAG_NAME 10
#define BLOCK_TAGS_MAX_CHAR BLOCK_MAX_TAG_NAME * BLOCK_MAX_TAGS

// Block Max Size
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
		int		numTags;
		char	tag_List[BLOCK_MAX_TAGS * BLOCK_MAX_TAG_NAME];
	} SUPERBLOCK, *PSUPERBLOCK;

	// Actual Data Block
	typedef struct Block {
		SuperBlock		sBlock;
		char			blkTag[BLOCK_MAX_TAG_NAME];
		char			data[BLOCK_MAX_SIZE];
		int				magic_3 = BLOCK_SUPER_B_3; // BLOCK_SUPER_B_3
		char			exit_Statagey[BLOCK_SUPER_NAME];
		int				magic_4 = BLOCK_SUPER_B_4; // BLOCK_SUPER_B_4
	} BLOCK, *PBLOCK;

	// Actual Data Blockv2
	typedef struct Blockv2 {
		char			blkTag[BLOCK_MAX_TAG_NAME];
		char			data[BLOCK_MAX_SIZE];
		int				magic_3 = BLOCK_SUPER_B_3; // BLOCK_SUPER_B_3
		char			exit_Statagey[BLOCK_SUPER_NAME];
		int				magic_4 = BLOCK_SUPER_B_4; // BLOCK_SUPER_B_4
	} BLOCKV2, *PBLOCKV2;

	//// Drive Structure -- This is only used to read a Drive File
	//typedef struct Drive {
	//	SuperBlock					sBlock;
	//	PBLOCKV2					Blocks;
	//} DRIVE, *PDRIVE;

	// Drive Structure -- This is only used to read a Drive File
	typedef struct DriveBase {
		SuperBlock					sBlock;
	} DRIVEBASE, *PDRIVEBASE;

	char	SuperBlockName[BLOCK_SUPER_NAME] = ""; // [TODO] Change how the charArray is init.
	int		Block_Size = 0;

public:
	// Drive Structure -- This is only used to read a Drive File
	typedef struct Drive {
		SuperBlock					sBlock;
		PBLOCKV2					Blocks;
	} DRIVE, * PDRIVE;

	typedef PBLOCKV2 pBlock;
	typedef BLOCKV2 nBlock;
	typedef PDRIVEBASE pDrvBase;
	typedef DRIVEBASE DrvBase;
	
	typedef PDRIVE pDrv;
	typedef DRIVE Drv;

	// Default constructor
	Block_A(char blockName[BLOCK_SUPER_NAME], int block_size);

	// Default deconstructor
	~Block_A();

	// Create
	bool Create();
	SuperBlock CreateSuperBlk();
	Block CreateBlock(SuperBlock sBlk, char* dataIN);

	Blockv2 CreateBlockv2(char* dataIN);
	void CreateDrive(SuperBlock sBlk);

	// Write
	bool Write(char *data, bool overwrite);
	bool Write(std::vector<std::string> data, bool overwrite);

	bool Write2Drive(std::vector<std::string> data); // Just writes blocks and not the super block

	// Delete
	// bool DeleteBlock(char* tagName);
	// bool DeleteBlock(int tagIndex);

	// Read
	BLOCK Read();
	DRIVEBASE ReadDrive();
	DRIVE* ReadWholeDrive(PDRIVE drvOUT, PBLOCKV2 blksOUT);
	void ReadBytes();
	void ReadBytes(PDRIVE drv, int offset = 0);
	void ReadBlocks(PBLOCKV2 drv, int blks);

	// Tags
	void AddTag(SuperBlock* sBlk, char* newTag);
	void ReadTags(SuperBlock* sBlk);
	void RemoveTag(SuperBlock *sBlk, int tagIndex);
};

#endif