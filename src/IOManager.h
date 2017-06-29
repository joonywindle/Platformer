#ifndef IOMANAGER_H
#define IOMANAGER_H
#include <vector>
#include <string>
class IOManager
{
public:
	static void readFileToBuffer(std::string filepath,std::vector<unsigned char>& buffer);

};

#endif // IOMANAGER_H
