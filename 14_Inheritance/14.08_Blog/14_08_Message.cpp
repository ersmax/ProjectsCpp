#include "14_08_Message.h"
#include "14_08_Validation.h"

namespace myNamespaceBlog
{
	Message::Message() : title("No title"), text("No text")
	{ /* Body intentionally left empty */ }

	Message::Message(const std::string& theTitle)
	{
		if (theTitle.empty())	throw std::invalid_argument("Title cannot be empty\n");
		title = theTitle;
	}

	Message::Message(const std::string& theTitle, const std::string& theMessage) : text(theMessage)
	{
		if (theTitle.empty())	throw std::invalid_argument("Title cannot be empty\n");
		title = theTitle;
	}

	const std::string& Message::getText() const { return text; }

	const std::string& Message::getTitle() const { return title; }

	std::istream& operator >>(std::istream& inputStream, Message& aMessage)
	{
		using myNamespaceValidation::readText;
		do
		{
			std::cout << "Enter a non empty title:\n";
			readText(inputStream, aMessage.title);
		} while (aMessage.title.empty());
		std::cout << "Enter the text:\n";
		readText(inputStream, aMessage.text);
		return inputStream;
	}

	std::ostream& operator <<(std::ostream& outputStream, const Message& aMessage)
	{
		outputStream << "Title: " << aMessage.title << '\n';
		outputStream << "Text:\n" << aMessage.text << '\n';
		return outputStream;
	}
} // myNamespaceBlog
