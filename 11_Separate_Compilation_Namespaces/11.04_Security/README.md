You would like to verify the credentials of a user for your system. Listed next is a
class named Security, which authenticates a user and password. (Note that this
example is really not very secure. Typically passwords would be encrypted or stored
in a database.)

```cpp
class Security
{
public:
	static int validate(string username, string password);
	// This subroutine hard-codes valid users and is not
	// considered a secure practice.
	// It returns 0 if the credentials are invalid,
	// 1 if valid user, and
	// 2 if valid administrator
};

int Security::validate(string username, string password)
{
	if ((username=="abbott") && (password=="monday")) return 1;
	if ((username=="costello") && (password=="tuesday")) return 2;
	return 0;
}
```
Break this class into two files, a file with the header Security.h and a file with the
implementation Security.cpp.
Next, create two more classes that use the Security class by including the header
file. The first class should be named Administrator and contain a function
named Login that returns true if a given username and password have administrator
clearance. The second class should be named User and contain a function
named Login that returns true if a given username and password have either user
or administrator clearance.
Both the User and Administrator classes should be split into separate files for the
header and implementation.
Finally, write a main function that invokes the Login function for both the User
and Administrator classes to test if they work properly. The main function
should be in a separate file. Be sure to use the #ifndef directive to ensure that no
header file is included more than once.

---
## Implementation overview 

This folder contains one implementation of a Login class, split
into the following translation units:

- `11.04_Security.h` / `11.04_Security.cpp`
- `11.04_Administrator.h` / `11.04_Administrator.cpp`
- `11.04_User.h` / `11.04_User.cpp`
- `11.04_main_app.cpp`

### Security

- `Security` represents a single account with a `username`, `password` and an
  integer `privilege` flag (1 = user, 2 = admin).
- The constructor and the input operator `operator>>` are responsible for
  filling these three fields, performing basic input validation on the
  username, password and privilege value.
- `int Security::validate(const std::string& user, const std::string& pwd) const`
  compares the supplied credentials to the stored ones for that account. It
  returns `0` if the credentials do not match, or the stored `privilege` value
  (`1` for a normal user, `2` for an administrator) if they do.
- The global constant `PRIVILEGES` (defined in `11.04_Security.cpp` and
  declared in the header) holds the allowed privilege levels and is used by the
  other classes to interpret the result of `validate`.

### Administrator

- `Administrator::Login(const std::vector<Security>& users)` is a `static`
  function that takes a collection of `Security` objects (the known accounts).
- It prompts on `std::cin` for a username and password, then iterates over the
  `users` vector. For each stored account it calls `user.validate(name, pwd)`.
- If any call to `validate` returns `PRIVILEGES[1]` (administrator privilege),
  `Login` immediately returns `true`. If no match is found with admin
  privileges, it returns `false`.

### User

- `User::Login(const std::vector<Security>& users)` has the same structure as
  `Administrator::Login`: it prompts for credentials and loops over the stored
  accounts calling `validate`.
- It returns `true` if any account matches the provided credentials with
  privilege level `PRIVILEGES[0]` (user) or `PRIVILEGES[1]` (administrator),
  and `false` otherwise.

### main application

- `11.04_main_app.cpp` is the test harness. In `main` it constructs a
  `std::vector<Security>` and reads two `Security` objects from `std::cin`
  using `operator>>`, pushing them into the vector. This simulates two stored
  accounts.
- The helper function `test(const std::vector<Security>& roosterUsers)` drives
  the interaction loop:
  - It repeatedly asks the user whether to check for a user (`u`) or admin
	(`a`).
  - For `a`, it calls `Administrator::Login(roosterUsers)` and prints
	"This is an admin" if the call returns `true`.
  - For `u`, it calls `User::Login(roosterUsers)` and prints
	"This is a user" if the call returns `true`.
  - Any other choice prints an error message.
  - After each check, it asks whether to continue; the loop repeats while the
	answer is `y` or `Y`.
- This main program therefore exercises both `User::Login` and
  `Administrator::Login` against the same in-memory list of accounts, as
  required by the exercise.


