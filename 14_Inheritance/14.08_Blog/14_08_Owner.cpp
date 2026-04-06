#include <iostream>
#include "14_08_Owner.h"
#include "14_08_Validation.h"

namespace myNamespaceBlog
{
	Owner::Owner() : Viewer()
	{ /* Body intentionally left empty */ }

	Owner::Owner(Blog& theBlog) : Viewer(theBlog)
	{ /* Body intentionally left empty */ }

	Owner::Owner(const std::string& theName, Blog& theBlog) : Viewer(theName, theBlog)
	{ /* Body intentionally left empty */ }

	void Owner::menu()
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
			std::cout << "Menu\n"
					  << "1. List all messages posted (title only)\n"
					  << "2. List a message (title and text)\n"
					  << "3. Add a new message\n"
					  << "4. Delete a message\n"
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
			case 3:
				postNewMessage();
				break;
			case 4:
				deleteOldMessage();
				break;
			case 0:
			default:
				break;
			}
		} while (choice != 0);
	}

	void Owner::postNewMessage()
	{
		if (blog == nullptr)
		{
			std::cout << "No blog associated with this user\n";
			return;
		}
		Message newMessage;
		std::cout << "You chose to enter a new message\n";
		std::cin >> newMessage;
		blog->addNewMessage(newMessage);
	}

    void Owner::deleteOldMessage()
    {
		if (blog == nullptr)
		{
			std::cout << "No blog associated with this user\n";
			return;
		}
		std::cout << "You chose to delete a message. Choose a title number:\n";
		printAllTitles();
		int choice;
		using myNamespaceValidation::readNumber;
		readNumber(std::cin, choice);
		choice--;
		// Zero normalized the index
		if (choice < 0 || choice >= blog->getNumMessages())
		{
			std::cout << "Choice not valid\n";
			return;
		}
		blog->deleteMessage(choice);
	}

} // myNamespaceBlog
