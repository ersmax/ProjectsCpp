Define a class named Document that contains a member variable of type string
named text that stores any textual content for the document. Create a function
named getText that returns the text field, a way to set this value, and an overloaded
assignment operator.
Next, define a class for Email that is derived from Document and that includes
member variables for the sender, recipient, and title of an e-mail message.
Implement appropriate accessor and mutator functions. The body of the e-mail
message should be stored in the inherited variable text. Also overload the assignment
operator for this class.
Similarly, define a class for File that is derived from Document and that includes
a member variable for the pathname. Implement appropriate accessor and mutator
functions for the pathname and overload the assignment operator.
Finally, create several sample objects of type Email and File in your main function.
Test your objects by passing them to the following subroutine, which will return
true if the object contains the specified keyword in the text property.
bool ContainsKeyword(const Document& docObject, string keyword)
{
if (docObject.getText().find(keyword) != string::npos)
return true;
return false;
}
For example, you might test to see whether an e-mail message contains the text
"c++" with the call ContainsKeyword(emailObj, "c++");.

---

# 14.07 - Contain Text

This exercise implements a small class hierarchy to store and search textual
content in different kinds of documents: generic documents, e-mail messages,
and files on disk.

## Design Overview

The implementation is split across several translation units in this folder.

### `Document` (`14_07_Document.h` / `14_07_Document.cpp`)

- Data member:
  - `std::string text;` stores the generic document text.
- Interface:
  - Default constructor initializes `text` to an empty string.
  - `Document(std::string theText)` initializes `text` from `theText`.
  - `const std::string& getText() const;` returns a const reference to `text`.
  - Copy assignment is defaulted: `Document& operator=(const Document&) = default;`.
  - Stream operators:
	- `operator>>` reads a full line of text into `text` using
	  `myNamespaceValidation::readText`.
	- `operator<<` writes the label "Text:" followed by the stored text.
- Namespace: all symbols are in `myNamespaceDocs`.

### `Email` (`14_07_Email.h` / `14_07_Email.cpp`)

- Inherits publicly from `Document`.
- Additional data members:
  - `sender`, `receiver`, `title` (all `std::string`).
- Constructors:
  - Default constructor initializes `Document` with empty text and sets
	`sender`, `receiver`, and `title` to placeholder values.
  - Parameterized constructor takes `theSender`, `theReceiver`, `theTitle`,
	and `theText`. It:
	- Initializes the base `Document` with `theText` (the e-mail body).
	- Validates that the three header fields are non-empty, throwing
	  `std::invalid_argument` otherwise.
- Other members:
  - Defaulted assignment operator: `Email& operator=(const Email&) = default;`.
  - Getters: `getSender()`, `getReceiver()`, `getTitle()` return const
	references to the respective strings.
- Stream operators:
  - `operator>>` first reads the body text through the `Document` input
	operator, then prompts and reads sender, receiver, and title using
	`myNamespaceValidation::readText`.
  - `operator<<` prints sender, receiver, and title, then delegates to the
	`Document` output operator to print the body text.

### `File` (`14_07_File.h` / `14_07_File.cpp`)

- Inherits publicly from `Document`.
- Additional data member:
  - `std::string pathFile;` stores the pathname of the file.
- Constructors:
  - Default constructor:
	- Calls the `Document` default constructor (empty text).
	- Initializes `pathFile` with the program's current working directory
	  obtained via `std::filesystem::current_path().string()`.
  - Parameterized constructor:
	- Calls the `Document` constructor with `theText` (file contents).
	- Validates `thePath` using a helper function `validPath`. If it passes,
	  assigns it to `pathFile`; otherwise throws `std::invalid_argument`.
- Other members:
  - `const std::string& getPathFile() const;` returns the stored path.
- Input/output:
  - `operator>>` prompts the user for a file path, reads it via
	`readText`, and loops until `validPath` accepts it. Then it reads the
	file text through the base `Document` input operator.
  - `operator<<` prints the stored path (labeled "File path:") and then
	outputs the document text via the `Document` output operator.

#### Path Validation Helper

- Implemented in an unnamed namespace in `14_07_File.cpp`:

```cpp
bool validPath(const std::string& thePath)
{
	if (thePath.empty())
		return false;
	const std::string invalidChars = "<>\"|?*";
	return thePath.find_first_of(invalidChars) == std::string::npos;
}
```

- This performs a simple check:
  - Rejects empty paths.
  - Rejects paths containing characters that are invalid in Windows file
	names. The search uses `std::string::find_first_of`, and compares the
	result to `std::string::npos` (meaning no invalid characters were found).

### `Validation` (`14_07_Validation.h` / `14_07_Validation.cpp`)

- Namespace: `myNamespaceValidation`.
- Function:
  - `void readText(std::istream& inputStream, std::string& myText);`
	- Uses `std::getline` in a loop to read a line of text into `myText`.
	- If input fails, prints an error message, clears the stream, and tries
	  again.
	- Used by the stream extraction operators of `Document`, `Email`, and
	  `File`.

### Application / Tests (`14_07_Application.cpp`)

- Includes `<filesystem>` and defines a constant
  `CURRENT_PATH = std::filesystem::current_path().string();` for convenience.
- In `main()`:
  - Creates two `Email` objects:
	- `anEmail` (default constructed, then read from `std::cin`).
	- `anotherEmail` constructed with fixed sender, receiver, title, and a
	  body containing the keyword "c++".
  - Creates two `File` objects:
	- `aFile` (default constructed, then read from `std::cin`).
	- `anotherFile` constructed with `CURRENT_PATH` as its path and a short
	  text string.
  - For each object, calls `containsKeyword` with the keyword "c++" and
	prints whether the keyword is present in its text.
- Helper function `containsKeyword`:

```cpp
bool containsKeyword(const myNamespaceDocs::Document& docObject,
					 const std::string& keyword)
{
	if (docObject.getText().find(keyword) != std::string::npos)
		return true;
	return false;
}
```

- This uses `Document::getText()` and `std::string::find` to check whether the
  keyword appears in the stored text. If `find` does not return
  `std::string::npos`, the keyword was found.

---

In summary, the program demonstrates basic inheritance, composition with
standard library types (`std::string`, `std::filesystem::path`), operator
overloading for stream I/O, and simple input validation and keyword search
over a common `Document` base interface.


