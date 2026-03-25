#include <iostream>
#include <cctype>

namespace
{
	std::string password;

	int digitToInt(const char c) { return (static_cast<int>(c) - static_cast<int>('0')); }

	bool isSpecial(const unsigned char c) { return !std::isalnum(c); }

	bool isValid()
	{
		if (password.length() < 8)	return false;

		bool number = false;
		bool special = false;
		for (const unsigned char character : password)
		{
			//if (digitToInt(character) >= 0 && digitToInt(character) <= 9)
			//	number = true;
			//if (character < 48 || (character > 57 && character < 65) ||
			//	(character > 90 && character < 97) || character > 122)
			//	special = true;

			if (std::isdigit(character))	number = true;
			if (std::ispunct(character))	special = true;

			if (number && special)	return true;
		}

		return false;
	}
} // unnamed namespace

namespace Authenticate
{
	void inputPassword()
	{
		do
		{
			std::cout << "Enter your password (at least 8 characters, at least one number, and one special character)\n";
			std::cin >> password;
		} while (!isValid());
	}

	std::string getPassword()
	{
		return password;
	}

} // namespace Authenticate