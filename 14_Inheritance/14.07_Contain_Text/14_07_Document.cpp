#include "14_07_Document.h"
#include "14_07_Validation.h"

namespace myNamespaceDocs
{
	Document::Document() : text("")
	{ /* Body intentionally left empty */ }

	Document::Document(std::string theText) : text(std::move(theText))
	{ /* Body intentionally left empty */ }

	const std::string& Document::getText() const { return text; }

	void Document::printInfo(std::ostream& outputStream) const
	{
		outputStream << "Document";
	}

	std::istream& operator >>(std::istream& inputStream, Document& aDocument)
	{
		using myNamespaceValidation::readText;
		readText(inputStream, aDocument.text);
		return inputStream;
	}

	std::ostream& operator <<(std::ostream& outputStream, const Document& aDocument)
	{
		outputStream << "Text:\n" << aDocument.text;
		return outputStream;
	}

} // myNamespaceDocs
