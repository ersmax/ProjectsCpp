Create a base class called Student that has their university's name (type string),
their registration number (type int), and their proctor (type UniversityStaff
given in the code that follows). Then create a class called ScienceStudent that
is derived from Student and has additional properties science discipline (type
string), undergraduate or postgraduate course (type string). Be sure your classes
have a reasonable complement of constructors and accessor methods, an overloaded
assignment operator, and a copy constructor. Write a driver program that
tests all your methods.
The definition of the class UniversityStaff follows. The implementation of the
class is part of this programming project.

class UniversityStaff
{
public:
	UniversityStaff( );
	UniversityStaff(string theName);
	UniversityStaff(const UniversityStaff& theObject);
	string getName( ) const;
	UniversityStaff& operator=(const UniversityStaff& rtSide);
	friend istream& operator >>(istream& inStream,
	UniversityStaff& staffObject);
	friend ostream& operator <<(ostream& outStream,
	const UniversityStaff& staffObject);
private:
	string name;
};

---


## Implementation Overview (14_04)

This directory contains a complete implementation of the exercise using three main classes and a small input–validation module. All code lives in the namespace `myNamespaceUniversity` except for the validation helpers.

### Files and Responsibilities

- `14_04_University_Staff.h/.cpp`
  - Defines class `UniversityStaff`, which models the proctor/academic staff member.
  - Data:
	- `std::string name` – staff member's name.
  - Interface:
	- Default and `std::string` constructors plus a compiler-generated copy constructor and assignment operator (`= default`).
	- `const std::string& getName() const` – returns the staff name.
	- `friend std::istream& operator>>(std::istream&, UniversityStaff&)` – prompts for and reads a non-empty staff name using the validation helpers.
	- `friend std::ostream& operator<<(std::ostream&, const UniversityStaff&)` – prints a label and the staff name.

- `14_04_Student.h/.cpp`
  - Defines base class `Student`.
  - Data:
	- `std::string universityName` – name of the university.
	- `int registrationNumber` – student registration number.
	- `UniversityStaff proctor` – supervising staff member.
  - Interface:
	- Default and full constructor, plus compiler-generated copy constructor and assignment operator.
	- Accessors:
	  - `const std::string& getUniversity() const` – returns `universityName`.
	  - `int getRegistration() const` – returns `registrationNumber`.
	  - `const std::string& getProctor() const` – returns the proctor's name via `UniversityStaff::getName()`.
	- `friend std::istream& operator>>(std::istream&, Student&)` – interactive extractor:
	  - Prompts and reads the university name using `readName` from the validation module.
	  - Prompts and reads the registration number using `readNumber`.
	  - Reads the `proctor` object via `readObject`, which in turn uses `operator>>` for `UniversityStaff`.
	- `friend std::ostream& operator<<(std::ostream&, const Student&)` – printer:
	  - Outputs university name, registration number, and proctor using `operator<<` for `UniversityStaff`.

- `14_04_Science_Student.h/.cpp`
  - Defines `ScienceStudent`, derived publicly from `Student`.
  - Extra data:
	- `std::string discipline` – science discipline (for example, Physics, Chemistry).
	- `std::string course` – either `"Undergraduate"` or `"Postgraduate"`.
  - Interface:
	- Default and full constructor; copy constructor and assignment operator are compiler-generated (`= default`).
	- `const std::string& getDiscipline() const` and `const std::string& getCourse() const` – accessors for the added fields.
	- `friend std::istream& operator>>(std::istream&, ScienceStudent&)` – extractor for the full object:
	  - First calls the base-class extractor via `inputStream >> static_cast<Student&>(aScienceStudent);` to read the `Student` part.
	  - Prompts and reads `discipline` using `readName`.
	  - Repeatedly prompts and reads `course` (also with `readName`) until it matches one of the allowed values listed in the local `COURSES` vector. Validation is done by the helper `validateCourse` in an unnamed namespace.
	- `friend std::ostream& operator<<(std::ostream&, const ScienceStudent&)` – printer:
	  - Reuses the base printer via `static_cast<const Student&>(aScienceStudent)`.
	  - Then prints `discipline` and `course` on separate lines.

- `14_04_Input_Validation.h/.cpp`
  - Provides reusable input helpers in namespace `myNamespaceValidation`.
  - Functions:
	- `void readName(std::istream&, std::string&)` – reads a full line using `std::getline`, rejects empty input (and per comment, rejects invalid formats), and keeps prompting until a valid non-empty string is entered.
	- `void readNumber(std::istream&, int&)` – reads an `int` using the extraction operator, clears the stream and discards the rest of the line on failure, and keeps prompting until a valid integer is entered.
	- `template <typename T> void readObject(std::istream&, T&)` – generic helper that repeatedly tries `inputStream >> object` and, on failure, prints an error, clears the stream, discards the rest of the line, and retries. This is used to read `UniversityStaff` via its overloaded `operator>>`.

- `14_04_Application.cpp`
  - Simple driver program that exercises the classes and their special member functions.
  - Logic:
	- Creates a default `ScienceStudent aStudent` and reads all of its data from `std::cin` using `operator>>`.
	- Uses the copy constructor to create `const ScienceStudent aStudent2(aStudent);` and prints it with `operator<<`.
	- Uses the assignment operator by default-constructing `ScienceStudent aStudent3;` and then doing `aStudent3 = aStudent2;`, and prints the result.
	- This verifies that input, output, copy construction, and assignment all behave as expected for the derived class, and transitively for the base class and `UniversityStaff`.

