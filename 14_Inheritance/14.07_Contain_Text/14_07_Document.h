#ifndef DOCUMENT_14_07_H
#define DOCUMENT_14_07_H

#include <string>

namespace myNamespaceDocs
{
	class Document
	{
	public:
		Document();
		//   Postcondition: A Document object has been created with text initialized 
		// to an empty string. 
		Document(std::string theText);
		//   Postcondition: A Document object has been created with text initialized
		const std::string& getText() const;
		Document& operator =(const Document& aDocument) = default;
		friend std::istream& operator >>(std::istream& inputStream, Document& aDocument);
		//   Precondition: inputStream is open, aDocument is a valid Document object.
		//   Postcondition: inputStream has been modified to read a string into the text
		friend std::ostream& operator <<(std::ostream& outputStream, const Document& aDocument);
		//   Precondition: outputStream is open, aDocument is a valid Document object.
		//   Postcondition: outputStream has been modified to write the text of aDocument to the stream.
	private:
		std::string text;
	};
}

#endif // DOCUMENT_14_07_H
