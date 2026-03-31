#include <iostream>
#include "14.02_Menu.h"

using myNamespaceMenu::Menu;

void test(Menu & myMenu);
char choiceValidation();

int main()
{

	Menu aMenu;
	do
	{
		test(aMenu);
		std::cout << "Repeat (y/n)?\n";
	} while (std::tolower(choiceValidation()) == 'y');

	std::cout << '\n';
	return 0;
}

void test(Menu& myMenu)
{
	std::cout << "Add ('a') or show ('s') employees?\n";
	switch (choiceValidation())
	{
	case 'a':
		myMenu.addEmployee();
		break;
	case 's':
		myMenu.showEmployee();
		break;
	default:
		std::cout << "Not a valid choice\n";
		break;
	}
}

char choiceValidation()
{
	char choice;
	while (true)
	{
		if (!(std::cin >> choice))
		{
			std::cout << "Not a valid choice\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return choice;
	}
}
