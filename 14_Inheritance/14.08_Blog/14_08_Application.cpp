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
