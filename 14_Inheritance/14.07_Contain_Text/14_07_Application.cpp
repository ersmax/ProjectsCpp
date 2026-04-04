#include <iostream>
#include <filesystem>
#include "14_07_Email.h"
#include "14_07_File.h"

const std::string CURRENT_PATH = std::filesystem::current_path().string();

bool containsKeyword(const myNamespaceDocs::Document& docObject, const std::string& keyword);
//   Precondition: docObject is a valid Document object, keyword is a valid string variable.
//   Postcondition: Return true if docObject contains keyword in its text, and false otherwise.
// std::string::npos is a constant static member with the greatest possible value for an element of type size_t (-1).
// The meaning in searches is: “this operation did not find anything”.
// Its function is to indicate that no matches were found in string::find and related functions. 
// If the value returned by string::find is string::npos, the search was unsuccessful.

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

	std::cout << "First email ";
	if (containsKeyword(anEmail, "c++"))
		std::cout << "contains ";
	else
		std::cout << "does not contain ";
	std::cout << "the keyword c++\n";


	std::cout << "Second email ";
	if (containsKeyword(anotherEmail, "c++"))
		std::cout << "contains ";
	else
		std::cout << "does not contain ";
	std::cout << "the keyword c++\n";

	std::cout << "First File ";
	if (containsKeyword(aFile, "c++"))
		std::cout << "contains ";
	else
		std::cout << "does not contain ";
	std::cout << "the keyword c++\n";

	std::cout << "Second file ";
	if (containsKeyword(anotherFile, "c++"))
		std::cout << "contains ";
	else
		std::cout << "does not contain ";
	std::cout << "the keyword c++\n";

	std::cout << '\n';
	return 0;
}

bool containsKeyword(const myNamespaceDocs::Document& docObject, const std::string& keyword)
{
	if (docObject.getText().find(keyword) != std::string::npos)
		return true;
	return false;
}
