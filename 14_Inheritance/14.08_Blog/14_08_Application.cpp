/*
Create a class for a simple blog. The owner of the blog should be able to (a) post a
new message, (b) numerically list and display all messages, and (c) select a specific
message and delete it.
Viewers of the blog should only be able to numerically list and display all posted
messages.
Create a class Viewer and a class Owner that uses inheritance to help implement
the blog functionality. Store the data messages using any format you like (a vector
of type string may be easiest). A menu function should be implemented for each
class that outputs the legal choices for the type of user. To test your classes, the
main function of the program should allow the user to invoke the menus from the
Viewer and Owner objects.
*/

#include <iostream>
#include "14_08_Blog.h"
#include "14_08_Owner.h"
#include "14_08_Validation.h"

int main( )
{
	using myNamespaceBlog::Owner;
	using myNamespaceBlog::Viewer;
	using myNamespaceBlog::Blog;

	Blog aBlog;
	Owner willie;
	Owner oliver("Oliver", aBlog);
	Viewer aViewer(aBlog);
	std::cout << "Enter viewer details below\n";
	std::cin >> aViewer;

	using myNamespaceValidation::readText;
	std::string choice;
	do
	{
		std::cout << "Test for owner:\n";
		oliver.menu();
		std::cout << "Test for viewer:\n";
		aViewer.menu();
		std::cout << "Continue? (y/n):\n";
		readText(std::cin, choice);

	} while (choice == "y");
	
	std::cout << "Test empty constructor\n";
	willie.menu();


	return 0;
}
