#include <iostream>
#include "14.02_Menu.h"

using myNamespaceMenu::Menu;

static void test(Menu & myMenu);

int main()
{
	using myNamespaceMenu::choiceValidation;
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
	using myNamespaceMenu::choiceValidation;
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
