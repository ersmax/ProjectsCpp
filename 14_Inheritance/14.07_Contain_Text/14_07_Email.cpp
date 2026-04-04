#include <stdexcept>
#include "14_07_Email.h"
#include "14_07_Validation.h"

namespace myNamespaceDocs
{
	Email::Email() : Document(), sender("No sender"), receiver("No receiver"), title("No title")
	{ /* Body intentionally left empty */ }

	Email::Email(const std::string& theSender, const std::string& theReceiver, 
				 const std::string& theTitle, const std::string& theText)
				: Document(theText) 
	{
		if (theSender.empty() || theReceiver.empty() || theTitle.empty())
			throw std::invalid_argument("Email field cannot be empty\n");
		sender = theSender;
		receiver = theReceiver;
		title = theTitle;
	}

	const std::string& Email::getSender() const { return sender; }

	const std::string& Email::getReceiver() const { return receiver; }

	const std::string& Email::getTitle() const { return title; }

	std::istream& operator >>(std::istream& inputStream, Email& anEmail)
	{
		inputStream >> dynamic_cast<Document&>(anEmail);
		
		using myNamespaceValidation::readText;
		std::cout << "Enter email sender:\n";
		readText(inputStream, anEmail.sender);
		std::cout << "Enter email receiver:\n";
		readText(inputStream, anEmail.receiver);
		std::cout << "Enter email title:\n";
		readText(inputStream, anEmail.title);
		return inputStream;
	}

	std::ostream& operator <<(std::ostream& outputStream, const Email& anEmail)
	{
		outputStream << "Sender: " << anEmail.sender << '\n';
		outputStream << "Receiver: " << anEmail.receiver << '\n';
		outputStream << "Title: " << anEmail.title << '\n';
		// Body:
		std::cout << "Enter Email text below\n";
		outputStream << dynamic_cast<const Document&>(anEmail);
		return outputStream;
	}

} // myNamespaceDocs 
