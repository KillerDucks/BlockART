// Block_ART.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Block.h"

int main()
{
	char blkName[BLOCK_SUPER_NAME] = "SUPERBLOCKTRAN";
	int blkSize = 125;
	Block_A BlockART = Block_A(blkName, blkSize);
	//BlockART.Create();
	BlockART.Read();
	return 0;
}
