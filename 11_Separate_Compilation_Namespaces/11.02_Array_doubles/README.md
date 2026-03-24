Obtain the source code for the PFArrayD class and the demonstration program
from Displays 11.10, 10.11, and 10.12. Modify this program to use namespaces
and separate compilation. Put the class definition and other function declarations
in one file. Place the implementations in a separate file. Distribute the namespace
definition across the two files. Place the demonstration program in a third file. To
provide access to names in namespaces, you may use local using declarations such as
using std::cout;
or use local using directives such as
using namespace std;
inside a block, or qualify names using the names of namespaces, such as std::cout.
You may not use global namespace directives such as the following which are not
in a block and apply to the entire file:
using namespace std;

---

## Implementation notes: logic and namespace separation

The code for this exercise is split into three files, following the
requirements for namespaces and separate compilation:

- "11.02_PFArrayD.h" contains the class interface and function declarations.
- "11.02_PFArrayD.cpp" contains the class and helper function definitions.
- "11.02_PFArrayD_app.cpp" contains the demonstration program with main().

The header file defines a user namespace named myNamespace and declares the
class PFArrayD as a partially filled array of double values. The public
interface includes:

- Constructors, copy constructor, assignment operator, and destructor.
- addElement() to insert a new value if there is still capacity.
- full(), getCapacity(), getNumberUSed(), and emptyArray() for querying and
  resetting the container state.
- operator[] for indexed access with range checks in the implementation.
- Friend operator>> and operator<< for reading from and writing to streams.

## Implementation
The implementation file "11.02_PFArrayD.cpp" also uses the same namespace
myNamespace so the definitions match the declarations. PFArrayD manages a
dynamic array of doubles (allocated with new and freed in the destructor),
tracks the current capacity and number of used elements, and performs safety
checks in addElement() and operator[] to avoid overruns and invalid indices.
The stream extraction operator>> reads nonnegative numbers until a negative
value or a full array, while operator<< outputs all stored numbers.

## Application
The application file "11.02_PFArrayD_app.cpp" includes only the header
"11.02_PFArrayD.h" plus standard headers like <iostream>. The main() function
prints a banner, then repeatedly calls testPFArrayD() while the user answers
"y" or "Y" to a prompt. Inside testPFArrayD(), the user chooses the array
capacity, a local using declaration (using myNamespace::PFArrayD;) brings the
class name into the local scope, and a PFArrayD instance is created. The
program then reads values into the PFArrayD object via operator>>, and
finally prints them via operator<<.

This structure demonstrates both separate compilation and controlled use of
namespaces: myNamespace groups the PFArrayD type and its related operators
across the header and implementation files, while the demonstration program
uses only a local using declaration inside a function block and qualifies
standard library entities with std::.

