#ifndef FILE_14_07_H
#define FILE_14_07_H

#include "14_07_Document.h"

namespace myNamespaceDocs
{
	class File : public Document
	{
	public:
		File();
		//   Postcondition: Initialize the path with 
		// the program's current working directory path.
		// Initialize the text to an empty string.
		File(const std::string& thePath, const std::string& theText);
		//   Postcondition: An File object has been created with path initialized 
		// to thePath and text initialized to theText.
		const std::string& getPathFile() const;
		void printInfo(std::ostream& outputStream) const override;
		friend std::istream& operator >>(std::istream& inputStream, File& aFile);
		//   Postcondition: inputStream has been modified to read a string into the path of aFile, 
		// and to read the text of aFile.
		friend std::ostream& operator <<(std::ostream& outputStream, const File& aFile);
		//   Postcondition: outputStream has been modified to write the path and text of aFile to the stream.
	private:
		std::string pathFile;
	};
	

} // myNamespaceDocs


#endif // FILE_14_07_H
