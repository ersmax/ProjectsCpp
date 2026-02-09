// define NDEBUG        // uncomment this line to disable assertions
#include <iostream>
#include <string>
#include <vector>
#include <cassert>

constexpr int GROUP_SIZE = 5;
constexpr int POSTNET[5] = {7, 4, 2, 1, 0};

class Zip
{
public:
	Zip() : zip(00000) {};
	Zip(const std::string& zipCode) { setZip(zipCode); }
	Zip(const int zipCode) { setZip(zipCode); }
	int getZip() const { return zip; }
	
	std::string convertZip() const { return conversion(zip); }
	//   Postcondition: return the zip code in bar code format as a string
private:
	int zip;
	
	void setZip(const std::string& zipCode);
	//   Precondition: the postcondition of isValid(zipCode) is true
	//   Postcondition: set the zip code from the bar code to zipCode
	
	void setZip(int zipCode);
	//   Precondition: zipCode is a valid zip code number between 00000 and 99999
	//   Postcondition: set the zip code from the zip code number to zipCode
	
	static bool isValid(const std::string& myString);
	//   Postcondition: return true if zipCode is a valid bar code string consisting of 0’s and 1’s
	// having length 27, and the first and last digits are 1.
	// Each group of five digits has exactly two 1’s.
	
	static bool isValid(const int zipCode) 
						{ return (zipCode >= 0 && zipCode <= 99999); };
	
	static int conversion(const std::string& myString);
	//  Precondition: the postcondition of isValid(myString) is true
	//  Postcondition: return the zip code number converted from the bar code string myString

	static std::string conversion(int zipCode);
	//   Precondition: the postcondition of isValid(zipCode) is true
	//   Postcondition: return the zip code in bar code format as a string converted 
	// from the zip code number zipCode

};

int main( )
{
	try
	{
		const Zip anAddress("110100101000101011000010011");
		const Zip anotherAddress(99504);
		std::cout << "First zip Address: " 
				  << anAddress.getZip() << '\n';
		std::cout << "Second zip Address: " 
				  << anotherAddress.getZip() << '\n';
		std::cout << "Second zip is equivalent to: " 
				  << anotherAddress.convertZip() << '\n';

	} catch (const std::invalid_argument& e) {
		std::cout << "Error: " << e.what() << '\n';
	}
	
	std::cout << '\n';
	return 0;
}

void Zip::setZip(const std::string& zipCode)
{
	if (!isValid(zipCode))
		throw std::invalid_argument("Invalid zip Code");
	zip = conversion(zipCode);
}

void Zip::setZip(const int zipCode)
{
	if (!isValid(zipCode))
		throw std::invalid_argument("Invalid zip Code");

	zip = zipCode;
}

bool Zip::isValid(const std::string& myString)
{
	if (myString.length() != 27)
		return false;
	if (myString.front() != '1' || myString.back() != '1')
		return false;
	
	for (const char& character : myString)
		if (character != '0' && character != '1')
			return false;

	for (size_t idx = 1; idx < 26; idx += GROUP_SIZE)
	{
		int count = 0;
		for (int jdx = idx; jdx < idx + GROUP_SIZE; jdx++)
			if (myString[jdx] == '1')
				count++;
		if (count != 2)
			return false;
	}
	return true;
}

int Zip::conversion(const std::string& myString)
{
	// remove leading and trailing `1`
	const std::string code = myString.substr(1, myString.length() - 2);
	
	int zip = 0;
	for (size_t idx = 0; idx < code.length(); idx += GROUP_SIZE)
	{
		int zipDigit = 0;
		for (size_t jdx = 0; jdx < GROUP_SIZE; jdx++)
			// convert each digit to 0/1, then multiply by POSTNET code
			zipDigit += (code[idx + jdx] - '0') * POSTNET[jdx];

		if (zipDigit == 11)	zipDigit = 0;

		zip = zip * 10 + zipDigit;
	}
	return zip;
}

std::string Zip::conversion(int zipCode)
{
	// Separate each group digit 
	int digits[GROUP_SIZE];
	for (int idx = 4; idx >= 0; idx--)
	{
		digits[idx] = zipCode % 10;
		zipCode /= 10;
	}
	// Group digit conversion
	std::string zip = "1";
	for (size_t idx = 0; idx < GROUP_SIZE; idx++)
	{
		std::string groupCode = "00000";
		const int target = (digits[idx] == 0) ? 11 : digits[idx];
		
		bool found = false;
		for (size_t p1 = 0; p1 < GROUP_SIZE - 1 && !found; p1++)
			for (size_t p2 = p1 + 1; p2 < GROUP_SIZE; p2++)
				if (POSTNET[p1] + POSTNET[p2] == target)
				{
					found = true;
					groupCode[p1] = '1';
					groupCode[p2] = '1';
					break;
				}
		zip += groupCode;
	}
	zip += "1";
	return zip;
}
