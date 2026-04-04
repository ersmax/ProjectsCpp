#include <stdexcept>
#include <filesystem>
#include "14_07_File.h"
#include "14_07_Validation.h"

namespace
{
	bool validPath(const std::string& thePath)
	//   Postcondition: Return true if thePath is a valid path, and false otherwise.
	//   thePath.find_first_of(invalidChars) returns 
	// the index of the first occurrence of any 
	// of those characters in thePath, or nPos if none are found.
	{
		if (thePath.empty())	return false;
		const std::string invalidChars = "<>\"|?*";
		return thePath.find_first_of(invalidChars) == std::string::npos;
	}

} // unnnamed namespace

namespace myNamespaceDocs
{
	File::File() :	Document(), 
					pathFile(std::filesystem::current_path().string())
	{ /* Body intentionally left empty */ }

	File::File(const std::string& thePath, const std::string& theText) : Document(theText)
	{
		if (validPath(thePath))	pathFile = thePath;
		else throw std::invalid_argument("Not a valid path\n");
	}

	const std::string& File::getPathFile() const { return pathFile; }

	void File::printInfo(std::ostream& outputStream) const
	{
		outputStream << "File path at: " << pathFile;
	}

	std::istream& operator >>(std::istream& inputStream, File& aFile)
	{
		using myNamespaceValidation::readText;
		while (true)
		{
			std::cout << "Enter file path:\n";
			readText(inputStream, aFile.pathFile);
			if (!validPath(aFile.pathFile))
				std::cout << "Not a valid path file\n";
			else
				break;
		}
		std::cout << "Enter file text below\n";
		inputStream >> dynamic_cast<Document&>(aFile);
		return inputStream;
	}

	std::ostream& operator <<(std::ostream& outputStream, const File& aFile)
	{
		outputStream << "File path:\n" << aFile.pathFile << '\n';
		outputStream << dynamic_cast<const Document&>(aFile);
		return outputStream;
	}

} // myNamespaceDocs
