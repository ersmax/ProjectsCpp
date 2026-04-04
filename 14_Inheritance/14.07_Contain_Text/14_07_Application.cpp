#include <iostream>
#include <filesystem>
#include "14_07_Email.h"
#include "14_07_File.h"

using myNamespaceDocs::Document;

const std::string CURRENT_PATH = std::filesystem::current_path().string();

bool containsKeyword(const myNamespaceDocs::Document& docObject, const std::string& keyword);
//   Precondition: docObject is a valid Document object, keyword is a valid string variable.
//   Postcondition: Return true if docObject contains keyword in its text, and false otherwise.
// std::string::npos is a constant static member with the greatest possible value for an element of type size_t (-1).
// The meaning in searches is: “this operation did not find anything”.
// Its function is to indicate that no matches were found in string::find and related functions. 
// If the value returned by string::find is string::npos, the search was unsuccessful.

void printTest(const std::string& label, const Document& aDocument, const std::string& keyword);

int main( )
{
	using myNamespaceDocs::Email;
	using myNamespaceDocs::File;

	Email anEmail;
	Email anotherEmail("Ciccio", "Pasticcio", "The message", "I love c++");
	std::cin >> anEmail;

	File aFile;
	File anotherFile(CURRENT_PATH, "This is okay\n");
	std::cin >> aFile;

	printTest("First email ", anEmail, "c++");
	printTest("Second email ", anotherEmail, "c++");
	printTest("First file ", aFile, "c++");
	printTest("Second file  ", anotherFile, "c++");

	std::cout << '\n';
	return 0;
}

bool containsKeyword(const myNamespaceDocs::Document& docObject, const std::string& keyword)
{
	if (docObject.getText().find(keyword) != std::string::npos)
		return true;
	return false;
}

void printTest(const std::string& label, const Document& aDocument, const std::string& keyword)
{
	std::cout << label << ' ';
	if (containsKeyword(aDocument, keyword))
		std::cout << "contains ";
	else
		std::cout << "does not contain ";
	std::cout << "the keyword " << keyword << '\n';
}
