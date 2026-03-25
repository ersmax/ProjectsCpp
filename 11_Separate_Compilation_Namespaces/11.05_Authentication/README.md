File: 11_Separate_Compilation_Namespaces\11.05_Authentication\README.md
This Programming Project explores how the unnamed namespace works. Listed are
snippets from a program to perform input validation for a username and password.
The code to input and validate the username is in a separate file than the code to
input and validate the password.
File header user.cpp:
```cpp
namespace Authenticate
{
	void inputUserName( )
	{
		do
		{
			cout << "Enter your username (8 letters only)" << endl;
			cin >> username;
		} while (!isValid( ));
	}

	string getUserName( )
	{
		return username;
	}
}
```

Define the username variable and the isValid( ) function in the unnamed
namespace so the code will compile. The isValid( ) function should return true
if username contains exactly eight letters. Generate an appropriate header file for
this code.
Repeat the same steps for the file password.cpp, placing the password variable
and the isValid( ) function in the unnamed namespace. In this case, the
isValid( ) function should return true if the input password has at least eight
characters including at least one non-letter:
File header password.cpp:
```cpp
namespace Authenticate
{
	void inputPassword( )
	{
		do
		{
			cout << "Enter your password (at least 8 characters " <<
			"and at least one non-letter)" << endl;
			cin >> password;
		} while (!isValid( ));
	}
	
	string getPassword( )
	{
		return password;
	}
}
```
At this point, you should have two functions named isValid( ), each in different
unnamed namespaces. Place the following main function in an appropriate place.
The program should compile and run.
```cpp
int main( )
{
	inputUserName( );
	inputPassword( );
	cout << "Your username is " << getUserName( ) <<
			" and your password is: " << getPassword( ) << endl;
	return 0;
}
```
Test the program with several invalid usernames and passwords.

---

## Implementation Logic

The program is split into three translation units that communicate through the
`Authenticate` namespace while keeping implementation details hidden in
unnamed namespaces.

### Main application (`11.05_Authentication_app.cpp`)
- Includes the public headers `11.05_User.h` and `11.05_Password.h`.
- Calls `Authenticate::inputUserName()` to read and validate the username.
- Calls `Authenticate::inputPassword()` to read and validate the password.
- After both values are valid, prints the username and password using
  `Authenticate::getUserName()` and `Authenticate::getPassword()`.

### Username module (`11.05_User.cpp` / `11.05_User.h`)
- `11.05_User.h` exposes two functions in namespace `Authenticate`:
  - `void inputUserName();`
  - `std::string getUserName();`
- `11.05_User.cpp` defines an unnamed namespace containing:
  - A `std::string username;` variable that stores the current username.
  - A helper `bool isValid();` that returns `true` only if:
    - The username length is exactly 8 characters, and
    - Every character is alphabetic (`std::isalpha`).
- `Authenticate::inputUserName()` repeatedly:
  - Prompts for "8 letters only".
  - Reads into `username`.
  - Loops until `isValid()` returns `true`.
- `Authenticate::getUserName()` returns the stored `username` string.

### Password module (`11.05_Password.cpp` / `11.05_Password.h`)
- `11.05_Password.h` exposes two functions in namespace `Authenticate`:
  - `void inputPassword();`
  - `std::string getPassword();`
- `11.05_Password.cpp` defines an unnamed namespace containing:
  - A `std::string password;` variable that stores the current password.
  - Helper functions used only inside this translation unit:
    - `int digitToInt(char c);` (not used in the final logic).
    - `bool isSpecial(unsigned char c);` (not used in the final logic).
  - A helper `bool isValid();` that returns `true` only if:
    - The password length is at least 8 characters, and
    - It contains at least one digit (`std::isdigit`) and
    - At least one punctuation/special character (`std::ispunct`).
- `Authenticate::inputPassword()` repeatedly:
  - Prompts for a password with the above constraints.
  - Reads into `password`.
  - Loops until `isValid()` returns `true`.
- `Authenticate::getPassword()` returns the stored `password` string.

The unnamed namespaces in the username and password modules ensure that
their internal `username`, `password`, and `isValid()` identifiers have
internal linkage and do not conflict across translation units, while the
`Authenticate` namespace provides a clean public interface used by `main`.

