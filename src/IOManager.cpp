#include "IOManager.h"
#include <iostream>
#include <fstream>
void IOManager::readFileToBuffer(std::string filepath, std::vector<unsigned char>& buffer)
{
	std::ifstream file(filepath,std::ios::binary);
	if(file.fail())
	{
		std::cout << "Couldn't open file: " << filepath << std::endl;
		exit(EXIT_FAILURE);
	}

	// Seek to end
	file.seekg(0,std::ios::end);
	// Get file size
	size_t fileSize = file.tellg();
	// return to beginning
	file.seekg(0,std::ios::beg);
	// Remove header from the size
	fileSize -= file.tellg();

	buffer.resize(fileSize);
	// Read in bytes
	file.read((char *)&buffer[0],fileSize);

	file.close();

}
