#include "Block_Data.h"



Block_Data::Block_Data(int max_data_size)
{
	this->max_data_size = max_data_size;
}


Block_Data::~Block_Data()
{
}

int Block_Data::CalcBlock(char* dataIn)
{
	// Use the variable set on class init to calculate the number of blocks needed
	int bNeeded = 0;

	// If the given data is smaller only return 1
	if (static_cast<int>(strlen(dataIn)) < this->max_data_size)
	{
		return 1;
	}

	bNeeded = strlen(dataIn) / this->max_data_size;

	return bNeeded + 1;
}

vector<std::string> Block_Data::Data2BData(char* dataIn)
{
	// Run Block_Data::CalcBlock to get the divisions
	int dataDivs = this->CalcBlock(dataIn);
	int dLength = strlen(dataIn);
	vector<std::string> dividedData;
	// Divde up the data
	int rPos = 0;
	for (int i = 0; i < dataDivs; i++)
	{
		std::string tString;
		for (size_t i = 0; i < static_cast<size_t>(this->max_data_size); i++)
		{
			tString += dataIn[rPos];
			rPos++;
		}
		dividedData.emplace_back(tString);
	}

	//for (auto s : dividedData)
	//{
	//	printf("Data Segment Length [%d]\n", s.length());
	//	printf("%s\n\n", s.c_str());
	//}
	return dividedData;
}