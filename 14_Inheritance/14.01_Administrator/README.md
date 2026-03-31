Write a program that uses the class SalariedEmployee given in Display 14.4.
Your program is to define a derived class called Administrator, which is to be
derived from the class SalariedEmployee. You are allowed to change private in
the base class to protected. You are to supply the following additional data and
function members:
- A member variable of type string that contains the administrator’s title, (such
as Director or Vice President).
- A member variable of type string that contains the company area of responsibility
(such as Production, Accounting, or Personnel).
- A member variable of type string that contains the name of this administrator’s
immediate supervisor.
- A protected member variable of type double that holds the administrator’s
annual salary. It is possible for you to use the existing salary member if you
changed private in the base class to protected.
\- A member function called setSupervisor, which changes the supervisor name.
\- A member function for reading in an administrator’s data from the keyboard.
\- A member function called print, which outputs the object’s data to the screen.
\- Finally, an overloading of the member function printCheck( ) with appropriate
notations on the check.

---

## Implementation Notes (`14_01_Administrator.h` / `14_01_Administrator.cpp`)

- The program extends `SalariedEmployee` with an `Administrator` class that adds:
  - `title` (e.g. `"Director"`, `"Vice President"`)
  - `areaResponsibility` (e.g. `"Production"`, `"Accounting"`, `"Personnel"`)
  - `nameSupervisor` (immediate supervisor name)
  - `annualSalary` (computed from weekly salary)

- In `14_01_Administrator.cpp` there are file-scope constants and helpers:
  - `constexpr int WEEKS = 52;` is used to convert weekly salary to annual salary.
  - `TITLES` and `RESPONSIBILITIES` are `std::vector<std::string>` lists of allowed titles and areas.
  - `inputValidation()` reads a full line from `std::cin` and rejects empty/invalid input.
  - `capitalize(std::string&)` normalizes a string so the first character is uppercase and all others are lowercase.
  - `readChoice(prompt, options)` prints a prompt and the allowed options, then loops until the user types a value that matches one of the options after capitalization.

- `Administrator` interface (`14_01_Administrator.h`):
  - Default ctor initializes all fields to sentinel values:
    - `name = "No name"`, `ssn = "No number"` via the base `Employee` default.
    - `title = "No title"`, `areaResponsibility = "No area"`, `nameSupervisor = "No name"`, `annualSalary = 0`.
  - Parameterized ctor takes `name`, `ssn`, weekly salary, title, area, supervisor. It:
    - Calls the `SalariedEmployee` ctor for base data.
    - Normalizes and validates `theTitle` and `theArea` against `TITLES` and `RESPONSIBILITIES`.
    - Throws `std::invalid_argument` if either value is not in the allowed lists.
    - Computes `annualSalary` as `WEEKS * getSalary()`.
  - `setSupervisor(const std::string&)` simply updates `nameSupervisor`.
  - `readData()` reads all administrator data from the keyboard:
    - Prompts for name, ssn, weekly salary (stored using `setName`, `setSsn`, `setSalary`).
    - Uses `readChoice` to select a valid `title` and `areaResponsibility`.
    - Reads `nameSupervisor` with `inputValidation()`.
    - Recomputes `annualSalary = WEEKS * getSalary()`.
  - `print() const` outputs name, title, area, annual salary and supervisor in a formatted way using `std::setw`.
  - `printCheck()` overrides the base behavior to print a check using the annual salary:
    - Calls `setNetPay(annualSalary)`.
    - Prints a simple check layout with name, net pay, ssn, and a line labeled `"Administrator Annual Pay"`.

