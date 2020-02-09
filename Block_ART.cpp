// Block_ART.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Block.h"

#include "Block_Data.h"

int main()
{
			// Block Data //

	Block_Data BlockDATA = Block_Data(255);
	int z = 0;
	std::vector<string> data;
	//z = BlockDATA.CalcBlock((char*)"/HELLO_WORLD_THIS_IS_A_TEST/HELLO_WORLD_THIS_IS_A_TEST/HELLO_WORLD_THIS_IS_A_TEST/HELLO_WORLD_THIS_IS_A_TEST/HELLO_WORLD_THIS_IS_A_TEST/HELLO_WORLD_THIS_IS_A_TEST/HELLO_WORLD_THIS_IS_A_TEST/HELLO_WORLD_THIS_IS_A_TEST/HELLO_WORLD_THIS_IS_A_TEST/HELLO_WORLD_THIS_IS_A_TEST");
	data = BlockDATA.Data2BData((char*)"/HELLO_WORLD_THIS_IS_A_TEST/HELLO_WORLD_THIS_IS_A_TEST/HELLO_WORLD_THIS_IS_A_TEST/HELLO_WORLD_THIS_IS_A_TEST/HELLO_WORLD_THIS_IS_A_TEST/HELLO_WORLD_THIS_IS_A_TEST/HELLO_WORLD_THIS_IS_A_TEST/HELLO_WORLD_THIS_IS_A_TEST/HELLO_WORLD_THIS_IS_A_TEST/HELLO_WORLD_THIS_IS_A_TEST##");
	//printf("%d\n", z);

			// Blocks //

	char blkName[BLOCK_SUPER_NAME] = "SUPERBLOCKTRAN";
	int blkSize = 125;
	Block_A BlockART = Block_A(blkName, blkSize);

			// Classic Block //

	//BlockART.Create();
	//BlockART.ReadBytes();
	//BlockART.Write((char*)"/HELLO_WORLD_THIS_IS_A_TEST", false);


			// Drives //
	Block_A::PDRIVE drv = new Block_A::DRIVE;
	drv->Blocks = new Block_A::nBlock[2];
	Block_A::pDrvBase pdrvBase = new Block_A::DrvBase;
	Block_A::pBlock pBlk = new Block_A::nBlock[2];
	//BlockART.CreateDrive(BlockART.CreateSuperBlk());
	//BlockART.Write2Drive(data);
	//BlockART.ReadWholeDrive();
	BlockART.ReadWholeDrive(drv, drv->Blocks);
	//BlockART.ReadBlocks(drv->Blocks, drv->sBlock.numTags);
	BlockART.ReadBytes(drv);
	//BlockART.ReadBlocks(*BlockART.ReadWholeDrive());

			// Tags //

	//BlockART.AddTag((char*)"TAGZ/");
	//BlockART.AddTag((char*)"TAGZ2/");
	//BlockART.ReadTags();
	return 0;
}
