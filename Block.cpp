#include "Block.h"
#include <conio.h>

Block_A::Block_A(char blockName[BLOCK_SUPER_NAME], int block_size)
{
	// KISS
	memcpy(this->SuperBlockName, blockName, BLOCK_SUPER_NAME);
	this->Block_Size = block_size;
}

Block_A::~Block_A()
{
}


Block_A::SuperBlock Block_A::CreateSuperBlk()
{
	// SuperBlock
	Block_A::SuperBlock sBlk;
	memset(&sBlk, BLOCK_PADDING, sizeof(sBlk));
	sBlk.magic_0 = BLOCK_SUPER_B_0;
	sBlk.magic_1 = BLOCK_SUPER_B_1;
	sBlk.magic_2 = BLOCK_SUPER_B_2;
	sBlk.blk_Size = this->Block_Size;
	sBlk.numTags = 0;
	memcpy(sBlk.name, this->SuperBlockName, BLOCK_SUPER_NAME);
	memset(sBlk.padding, BLOCK_PADDING, 4);

	return sBlk;
}

Block_A::Block Block_A::CreateBlock(SuperBlock sBlk, char* dataIN)
{
	// Block
	Block_A::Block blk;
	memset(&blk, BLOCK_PADDING, sizeof(blk));
	blk.sBlock = sBlk;
	blk.magic_3 = BLOCK_SUPER_B_3;
	blk.magic_4 = BLOCK_SUPER_B_4;
	memcpy(blk.exit_Statagey, this->SuperBlockName, BLOCK_SUPER_NAME);

	// Insert the data into the Block
	memset(blk.data, BLOCK_PADDING, BLOCK_MAX_SIZE);
	memcpy(blk.data, dataIN, strlen(dataIN));

	return blk;
}

Block_A::Blockv2 Block_A::CreateBlockv2(char* dataIN)
{
	// Block
	Block_A::Blockv2 blk;
	memset(&blk, BLOCK_PADDING, sizeof(blk));
	blk.magic_3 = BLOCK_SUPER_B_3;
	blk.magic_4 = BLOCK_SUPER_B_4;
	memcpy(blk.exit_Statagey, this->SuperBlockName, BLOCK_SUPER_NAME);

	// Insert the data into the Block
	memset(blk.data, BLOCK_PADDING, BLOCK_MAX_SIZE);
	memcpy(blk.data, dataIN, strlen(dataIN));

	memset(blk.blkTag, BLOCK_PADDING, BLOCK_MAX_TAG_NAME);
	memcpy(blk.blkTag, (char*)"TAG1/", strlen("TAG1/"));

	return blk;
}

void Block_A::CreateDrive(SuperBlock sBlk)
{
	// We need a file steam of somesort
	std::ofstream blockFile;
	int blockLength = 0;

	// Open the file to read
	blockFile.open("D:\\BlockART\\Drive.bin", std::ios::binary | std::ios::out);

	if (blockFile)
	{
		// Read the files contents
		if (blockLength == -1 || blockLength == 0)
		{
			// Write the block to file
			blockFile.write((char*)& sBlk, sizeof(sBlk));
		}

		blockFile.close();
	}
	else
	{
		printf("Unable to open the file!!");
	}

}

bool Block_A::Create()
{
	// We need a file steam of somesort
	std::ofstream blockFile;
	int blockLength = 0;

	// Open the file to read
	blockFile.open("D:\\BlockART\\BLOCK.bin", std::ios::binary | std::ios::out);
	if (blockFile)
	{

		// Read the files contents
		if (blockLength == -1 || blockLength == 0)
		{
			// This file is okay to create a block
			// Create a Block and a SuperBlock

			// SuperBlock
			Block_A::SuperBlock sBlk;
			sBlk = this->CreateSuperBlk();

			// Block
			Block_A::Block blk;
			blk = this->CreateBlock(sBlk, (char*)"This_is_some_sample_data");			

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

void Block_A::ReadBytes()
{
	// We need a file steam of somesort
	std::fstream blockFile;
	int blockLength = 0;

	// Open the file to read
	blockFile.open("D:\\BlockART\\BLOCK.bin", std::ios::in | std::ios::binary);
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
			char *buffer = new char[blockLength];
			memset(buffer, BLOCK_PADDING, blockLength);
			blockFile.read(buffer, blockLength);
			int lC = 0, c = 1;
			const int eC = 15;
			printf("\nOffset\t\t\t\tBlock File Raw Dump\t\t\n\n");
			printf(" 0x%02X\t", c - 1);
			for (size_t i = 0; i < blockLength; i++)
			{
				printf("0x%02X ", buffer[i]);
				if (lC == eC)
				{
					printf("\n");
					printf(" 0x%02X\t", c);
					lC = 0;
					c++;
				}
				else
				{
					lC++;
				}
			}
			printf("\n");
			
			//printf("Block Exit_Stratagey Data => %s\n", blk.exit_Statagey);
		}

		blockFile.close();
	}
	else
	{
		printf("Unable to open the file!!");
	}
}

void Block_A::ReadBytes(Block_A::PDRIVE drv, int offset)
{
	int blkNum = 2;

	int c = offset + 1;

	// [TODO] Add option to show SuperBlock bytes

	// Calculate the actual offset of the blocks
	int lC = 0;
	int offsetSeeker = 0;
	int offsetPadding = 0;

	for (size_t i = 0; i < sizeof(drv->sBlock); i++)
	{
		if (lC == 15)
		{
			// Reset the 16 checker
			lC = 0;
			// Add one the offset
			c++;
		}
		else
		{
			lC++;
		}
		offsetSeeker = i;
	}

	offsetSeeker++;
	printf("Offset detcted %d\n", offsetSeeker);
	printf("Offset detcted %d\n", offsetSeeker % 16);

	if (offsetSeeker % 16)
	{
		offsetPadding = offsetSeeker % 16;
	}

	for (size_t i = 0; i < static_cast<size_t>(blkNum); i++)
	{
		int lC = 0;
		const int eC = 15;

		// Create a buffer to store the block data RAW !!!
		char* buffer = new char[sizeof(drv->Blocks[i])];
		memcpy(buffer, &drv->Blocks[i], sizeof(drv->Blocks[i]));

		printf("\n Offset\t\t\t\tBlock File Raw Dump [%d]\t\t\n\n", i);
		printf(" 0x%03X0\t", c - 1);
		// Apply the offset padding
		while (offsetPadding != 0)
		{
			printf("0x%02X ", 0x00);
			lC++;
			offsetPadding--;
		}
		// Print out the byte data to the console
		for (size_t i = 0; i < sizeof(drv->Blocks[i]); i++)
		{
			printf("0x%02X ", buffer[i]);
			if (lC == eC)
			{
				if (i + 1 == sizeof(drv->Blocks[i]))
				{
					continue;
				}
				printf("\n");
				// Print the new offset
				printf(" 0x%03X0\t", c);
				// Reset the 16 checker
				lC = 0;
				// Add one the offset
				c++;
			}
			else
			{
				lC++;
			}
		}
		printf("\n");
		c++;
	}
}


Block_A::BLOCK Block_A::Read()
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
			memset((char*)& blk, 0xFF, sizeof(blk));
			// Read the block into the char buffer
			blockFile.read((char*)& blk, sizeof(blk));
			//// Add a '\0' to the end of the buffer
			//buffer += '\0';
			// Report on the File data
			printf("RAW Data from the block => %s\n", blk.data);
			printf("Block Exit_Stratagey Data => %s\n", blk.exit_Statagey);
			
			blockFile.close();
			return blk;
		}

		blockFile.close();
	}
	else
	{
		printf("Unable to open the file!!");
	}
}

Block_A::DriveBase Block_A::ReadDrive()
{
	// We need a file steam of somesort
	std::fstream blockFile;
	int blockLength = 0;

	// Open the file to read
	blockFile.open("D:\\BlockART\\Drive.bin");
	if (blockFile)
	{
		// Seek to the end of the file
		blockFile.seekg(0, blockFile.end);
		// Store the value of bytes in the file to use later
		blockLength = blockFile.tellg();
		// Move the steam cursor back to the beginning of the file
		blockFile.seekg(0, blockFile.beg);

		// Report on the File size
		printf("The drive size determined from the bytes read => %d\n", blockLength);

		// Read the files contents
		if (blockLength != -1 && blockLength != 0)
		{
			// Create a buffer to store the block data RAW !!!
			Block_A::DriveBase drv;
			// Clear the buffer of any random pieces of memory
			memset((char*)& drv, 0xFF, sizeof(drv));
			// Read the block into the char buffer
			blockFile.read((char*)& drv, sizeof(drv));

			blockFile.close();
			return drv;
		}

		blockFile.close();
	}
	else
	{
		printf("Unable to open the file!!");
	}
	return DriveBase();
}

Block_A::DRIVE* Block_A::ReadWholeDrive(PDRIVE drvOUT, PBLOCKV2 blksOUT)
{
	// We need a file steam of somesort
	std::fstream blockFile;
	int blockLength = 0;

	// Open the file to read
	blockFile.open("D:\\BlockART\\Drive.bin");
	if (blockFile)
	{
		// Seek to the end of the file
		blockFile.seekg(0, blockFile.end);
		// Store the value of bytes in the file to use later
		blockLength = blockFile.tellg();
		// Move the steam cursor back to the beginning of the file
		blockFile.seekg(0, blockFile.beg);

		// Report on the File size
		printf("The drive size determined from the bytes read => %d\n", blockLength);

		// Read the files contents
		if (blockLength != -1 && blockLength != 0)
		{
			// Read the block into the char buffer
			blockFile.read((char*)&drvOUT->sBlock, sizeof(Block_A::SuperBlock));

			// Seek the cursor after the SuperBlock
			blockFile.seekg(sizeof(Block_A::SuperBlock), std::ios_base::beg);

			int i = 0;

			// Loop through remaning buffer and cast into a Blockv2
			while (blockFile.tellg() != blockLength)
			{
				blockFile.read((char*)& blksOUT[i], sizeof(Block_A::Blockv2));
				i++;
			}

			blockFile.close();

			// [TODO] Maybe change the sig to be void ??
			return PDRIVE();
		}

		blockFile.close();
	}
	else
	{
		printf("Unable to open the file!!");
	}
	return PDRIVE();
}

void Block_A::ReadBlocks(PBLOCKV2 drv, int blks)
{
	for (size_t i = 0; i < static_cast<size_t>(blks); i++)
	{
		printf("Block Tag Found [%s]\n", drv[i].blkTag);
		printf("Block Data Found [%s]\n\n", drv[i].data);
	}
}

bool Block_A::Write(char* data, bool overwrite)
{
	// We need a file steam of somesort
	//std::fstream blockFile;
	// Open the file to read
	//blockFile.open("D:\\BlockART\\BLOCK.bin", std::ios::binary | std::ios::out);
	// Create a buffer to store the block data
	Block_A::Block blk;
	// Populate the Struct
	blk = this->Read();
	printf("RAW Data from the block => %d\n", strlen(blk.data));
	// Check if overwrite is true
	if (overwrite)
	{
		// Clear the data and add the new data
		memcpy(blk.data, data, strlen(data));
	}
	else
	{
		memcpy(blk.data + strlen(blk.data), data, strlen(data));
	}

	printf("RAW Data from the block => %s\n", blk.data);
	printf("RAW Data from the block => %d\n", strlen(blk.data));


	// Write the block to file
	//blockFile.write((char*)& blk, sizeof(blk));
	return false;
}

bool Block_A::Write(std::vector<std::string> data, bool overwrite)
{
	// Create a buffer to store the block data
	Block_A::Block blk;
	// Populate the Struct
	blk = this->Read();
	printf("RAW Data from the block => %d\n", strlen(blk.data));
	// Conncat into one string
	string strTemp;
	for (auto d : data)
	{
		strTemp += d;
	}
	// Check if overwrite is true
	if (overwrite)
	{
		// Clear the data and add the new data
		memcpy(blk.data, strTemp.c_str(), strTemp.size());
	}
	else
	{
		memcpy(blk.data + strlen(blk.data), strTemp.c_str(), strTemp.size());
	}

	printf("RAW Data from the block => %s\n", blk.data);
	printf("RAW Data from the block => %d\n", strlen(blk.data));
	return false;
}

bool Block_A::Write2Drive(std::vector<std::string> data)
{
	// Read the Drive
	Block_A::DriveBase	drvBase;
	drvBase = this->ReadDrive();

	// Convert the Data into Blocks [v2]
	std::vector<Block_A::Blockv2> blocks;
	for (auto d : data)
	{
		// Create a Block
		Block_A::Blockv2 blk2;
		blk2 = this->CreateBlockv2((char*)d.c_str());
		blocks.emplace_back(blk2);

		// Add Tags onto the SuperBlock
		this->AddTag(&drvBase.sBlock, blk2.blkTag);
	}

	// We need a file steam of somesort
	std::ofstream blockFile;
	int blockLength = 0;

	// Open the file to read
	blockFile.open("D:\\BlockART\\Drive.bin", std::ios::binary | std::ios::out);
	if (blockFile)
	{
		// This file is okay to create a block

		// Write the block to file
		//blockFile.write((char*)&drv, sizeof(drv));
		blockFile.write((char*)&drvBase, sizeof(drvBase));
		for (size_t i = 0; i < blocks.size(); i++)
		{
			blockFile.write((char*)&blocks[i], sizeof(Block_A::Blockv2));
		}

		blockFile.close();
	}
	else
	{
		printf("Unable to open the file!!");
	}
	return false;
}

		// Tags //
void Block_A::AddTag(SuperBlock* sBlk, char* newTag)
{
	// [TODO] Read tags before attempting to write a new tag
	if (sBlk->numTags == BLOCK_MAX_TAGS)
	{
		printf("Unable to add more tags to this drive!!");
	}

	// Check if any tags exist
	if (sBlk->numTags != 0)
	{
		// Copy the existing tags and append the new tag
		int endOfTags = 0;
		for (size_t i = 0; i < strlen(sBlk->tag_List); i++)
		{
			// Loop through chars till we find a '1'
			if (sBlk->tag_List[i] == 1)
			{
				endOfTags = i;
				break;
			}
		}
		if (endOfTags == 0)
		{
			printf("An error has occured Block_A::AddTag");
		}
		else
		{
			memcpy(sBlk->tag_List + endOfTags, newTag, strlen(newTag));
			sBlk->numTags++;
		}

	}
	else
	{
		// Just add a new tag
		// Memset the container
		memset(sBlk->tag_List, 1, BLOCK_TAGS_MAX_CHAR);
		// Copy in the new tag
		memcpy(sBlk->tag_List, newTag, strlen(newTag));
		sBlk->numTags++;
	}
}

void Block_A::ReadTags(SuperBlock* sBlk)
{
	string tags(sBlk->tag_List);
	printf("Unformatted Tags: [%s]", tags.c_str());
}