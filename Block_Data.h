#pragma once

#include <string>
#include <vector>

#ifndef BLOCK_DATA_H
#define BLOCK_DATA_H

using std::vector;

class Block_Data
{
private:
	int max_data_size = 0;

public:
	Block_Data(int max_data_size);
	~Block_Data();

	// Data Manips
	int CalcBlock(char* dataIn); // This will calculate the number of blocks needed to store the given data
	vector<std::string> Data2BData(char* dataIn); // This will break down the data to the size of the block space
};

#endif // !BLOCK_DATA_H