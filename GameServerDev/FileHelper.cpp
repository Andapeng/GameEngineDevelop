#include "FileHelper.h"
#include <fstream>

void FileHelper::SaveContentToFile(std::string FilePath, std::string ContentString)
{
	std::fstream fout;
	fout.open(FilePath, std::ios::out);
	fout << ContentString;
}
