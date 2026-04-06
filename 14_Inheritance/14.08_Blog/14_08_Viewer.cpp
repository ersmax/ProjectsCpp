#include <stdexcept>
#include <iostream>
#include "14_08_Viewer.h"
#include "14_08_Message.h"
#include "14_08_Validation.h"

namespace myNamespaceBlog
{
	Viewer::Viewer() : blog(nullptr), name("No name")
	{ /* Body intentionally left empty */ }

	Viewer::Viewer(Blog& theBlog) : blog(&theBlog), name("No name")
	{ /* Body intentionally left empty */ }

	Viewer::Viewer(const std::string& theName, Blog& theBlog): blog(&theBlog)
	{
		if (theName.empty())	throw std::invalid_argument("Name cannot be empty");
		name = theName;
	}

	const Message& Viewer::getMessage(const int numberMessage) const 	
	{
		return blog->operator[](numberMessage);
	}

	const BlogPtr& Viewer::getBlog() const { return blog; }

	void Viewer::menu() const
	{
		if (blog == nullptr)
		{
			std::cout << "No blog associated with this user\n";
			return;
		}
		using myNamespaceValidation::readNumber;
		int choice = 0;
		do
		{
			std::cout	<< "Menu\n"
						<< "1. List all messages posted (title only)\n"
						<< "2. List a message (title and text)\n"
						<< "0. Exit\n";

			readNumber(std::cin, choice);
			switch (choice)
			{
			case 1:
				printAllTitles();
				break;
			case 2:
				printTheMessage();
				break;
			case 0:
			default:
				break;
			}
		} while (choice != 0);
	}

	void Viewer::printAllTitles() const
	{
		if (blog == nullptr)
		{
			std::cout << "No blog associated with this user\n";
			return;
		}
		const int numMessages = blog->getNumMessages();
		for (int idx = 0; idx < numMessages; idx++)
		{
			const Message& theMessage = getMessage(idx);
			std::cout << idx + 1 << ") "<< theMessage.getTitle() << '\n';
		}
	}

	void Viewer::printTheMessage() const
	{
		if (blog == nullptr)
		{
			std::cout << "No blog associated with this user\n";
			return;
		}
		std::cout << "Enter the message number you want to read.\n";
		printAllTitles();
		std::cout << "Enter a number:\n";
		int choice;
		using myNamespaceValidation::readNumber;
		readNumber(std::cin, choice);
		choice--;	
		// Zero-normalize
		if (choice < 0 || choice >=  blog->getNumMessages())
		{
			std::cout << "Not a valid message number\n";
			return;
		}
		const Message& theMessage = getMessage(choice);
		std::cout << "Title: " << theMessage.getTitle() << '\n';
		std::cout << "Text:\n" << theMessage.getText() << '\n';
	}

	std::ostream& operator <<(std::ostream& outputStream, const Viewer& aViewer)
	{
		outputStream << "Name: " << aViewer.name;
		return outputStream;
	}

	std::istream& operator >>(std::istream& inputStream, Viewer& aViewer)
	{
		using myNamespaceValidation::readText;
		std::cout << "Enter a name:\n";
		readText(inputStream, aViewer.name);
		return inputStream;
	}


} // myNamespaceBlog
