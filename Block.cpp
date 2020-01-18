#include "Block.h"

Block_A::Block_A(char blockName[BLOCK_SUPER_NAME], int block_size)
{
	// KISS
	memcpy(this->SuperBlockName, blockName, BLOCK_SUPER_NAME);
	this->Block_Size = block_size;
}

Block_A::~Block_A()
{
}


bool Block_A::Create()
{
	// We need a file steam of somesort
	std::ofstream blockFile;
	int blockLength = 0;

	// Open the file to read
	blockFile.open("D:\\BlockART\\BLOCK.bin", std::ios::binary);
	if (blockFile)
	{

		// Read the files contents
		if (blockLength == -1 || blockLength == 0)
		{
			// This file is okay to create a block
			// Create a Block and a SuperBlock

			// SuperBlock
			Block_A::SuperBlock sBlk;
			memset(&sBlk, 0xFF, sizeof(sBlk));
			sBlk.magic_0 = BLOCK_SUPER_B_0;
			sBlk.magic_1 = BLOCK_SUPER_B_1;
			sBlk.magic_2 = BLOCK_SUPER_B_2;
			sBlk.blk_Size = this->Block_Size;
			memcpy(sBlk.name, this->SuperBlockName, BLOCK_SUPER_NAME);
			memset(sBlk.padding, 0xFF, 4);

			// Block
			Block_A::Block blk;
			memset(&blk, 0xFF, sizeof(blk));
			blk.sBlock = sBlk;
			blk.magic_3 = BLOCK_SUPER_B_3;
			blk.magic_4 = BLOCK_SUPER_B_4;
			memcpy(blk.exit_Statagey, this->SuperBlockName, BLOCK_SUPER_NAME);

			// Insert the data into the Block
			/*blk.data = (char*)"This_is_some_sampledata\0";*/
			/*memcpy(blk.data, (char*)"This_is_some_sampledata\0", 25);*/
			memset(blk.data, 0xFF, BLOCK_MAX_SIZE);
			memcpy(blk.data, (char*)"This_is_some_sample_data", 25);

			// Report on the Block
			printf("The block size => %d\n", this->Block_Size);
			printf("The block data => %s\n", blk.data);

			// Write the block to file
			blockFile.write((char*)&blk, sizeof(blk));
		}

		blockFile.close();
	}
	else
	{
		printf("Unable to open the file!!");
	}

	return false;
}

int Block_A::Read()
{
	// We need a file steam of somesort
	std::fstream blockFile;
	int blockLength = 0;

	// Open the file to read
	blockFile.open("D:\\BlockART\\BLOCK.bin");
	if (blockFile)
	{
		// Seek to the end of the file
		blockFile.seekg(0, blockFile.end);
		// Store the value of bytes in the file to use later
		blockLength = blockFile.tellg();
		// Move the steam cursor back to the beginning of the file
		blockFile.seekg(0, blockFile.beg);

		// Report on the File size
		printf("The block size determined from the bytes read => %d\n", blockLength);

		// Read the files contents
		if (blockLength != -1 && blockLength != 0)
		{
			// Create a buffer to store the block data RAW !!!
			Block_A::Block blk;
			// Clear the buffer of any random pieces of memory
			memset((char*)&blk, 0xFF, sizeof(blk));
			// Read the block into the char buffer
			blockFile.read((char*)& blk, sizeof(blk));
			//// Add a '\0' to the end of the buffer
			//buffer += '\0';
			// Report on the File data
			printf("RAW Data from the block => %s\n", blk.data);
			printf("Block Exit_Stratagey Data => %s\n", blk.exit_Statagey);
		}

		blockFile.close();
	}
	else
	{
		printf("Unable to open the file!!");
	}
	return 0;
}
