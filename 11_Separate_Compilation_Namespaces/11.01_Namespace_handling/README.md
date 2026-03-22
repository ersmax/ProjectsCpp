This exercise is intended to illustrate namespaces and separate compilation in your
development environment. You should use the development environment you regularly
use in this course for this exercise. In a file f.h, place a declaration of void f( )
in namespace A. In a file g.h, place a declaration of void g( ) in namespace A. In
files f.cpp and g.cpp, place the definitions of void f( ) and void g( ), respectively.
Place the definitions of void f( ) and void g( ) in namespace A. The functions can
do anything you want, but to keep track of execution include something like
cout << "Function_Name called" << endl;
where Function_Name is the name of the particular function. In another file, main.
cpp, put your main function, #include the minimum collection of files to provide
access to the names from namespace A. In your main function call the functions
f then g. Compile, link, and execute using your development environment. To provide
access to names in namespaces, you may use local using declarations such as
using std::cout;
or use local using directives such as
using namespace std;
inside a block, or qualify names using the names of namespaces, such as std::cout.
You may not use global namespace directives such as the following which are not
in a block and apply to the entire file:
using namespace std;
Of course you must handle namespace A and function names f and g, in addition
to possibly std and cout.
After doing this, write a one page description of how to create and use namespaces
and separate compilation in your environment.

---

For this exercise I use a CMake-based C++ project opened in Microsoft Visual
Studio Community 2026. CMake generates Ninja build files, and Visual Studio
drives CMake and Ninja for me when I configure and build the project. Each
".cpp" file is compiled as a separate translation unit and then linked into a
single executable, which illustrates separate compilation in practice.

To organize the code, I created three kinds of files inside
"11_Separate_Compilation_Namespaces/11.01_Namespace_handling":

- Header files for declarations (i.e. interface files): "11.01_f.h" and "11.01_g.h".
- Source files for definitions (i.e. implementation files): "11.01_f.cpp" and "11.01_g.cpp".
- A main program file (i.e. application file): "11.01_main.cpp".

In the header files I declare the functions inside a user-defined namespace
"A" and protect each header with an include guard, so it can be included
safely from multiple source files:

```cpp

    #ifndef F_H_11_01
    #define F_H_11_01

    namespace A {
        void f();
    }

    #endif
```

The header for "g()" is analogous. These headers expose only the function
declarations and the namespace, but they do not include <iostream>.
Keeping most standard library includes out of headers (unless required)
avoids unnecessary coupling between translation units and can speed up
compilation.

In the implementation files "11.01_f.cpp" and "11.01_g.cpp" I include the
corresponding header and <iostream>, then provide the function bodies
inside the same namespace "A". For example, "11.01_f.cpp" contains:

```cpp
    #include <iostream>
    #include "11.01_f.h"

    namespace A {
        void f() {
            std::cout << "Calling function f()\n";
        }
    }
```

This shows how the namespace groups related functions ("f" and "g") and
how the implementation is kept separate from the interface. Each ".cpp"
file is compiled independently by the build system into an object file.
During the link step, these object files are combined into the final
executable. If I change only "11.01_f.cpp", CMake and Ninja only need to
recompile that one translation unit, which demonstrates the benefit of
separate compilation for build times and modular design.

The main program "11.01_main.cpp" includes just the headers it needs:

```cpp
    #include "11.01_f.h"
    #include "11.01_g.h"
```

Inside main() I avoid a global "using namespace std;" directive. Instead
I either qualify names (for example std::cout and A::f) or use local
using declarations in small blocks, as in:

```cpp
    int main() {
        {
            using A::f;
            f();
        }
        {
            using A::g;
            g();
        }
        return 0;
    }
```

This demonstrates how to access names from a user-defined namespace without
polluting the global namespace. The local using declarations are limited
to the block where they appear, and after the block ends those names are no
longer introduced into the surrounding scope.

From the build system perspective, Visual Studio detects the CMake project in
"D:/CPP/Projects" and configures it using the Ninja generator and the C++23
standard. When I build the target that includes "11.01_main.cpp",
"11.01_f.cpp", and "11.01_g.cpp", CMake creates Ninja rules that:

- Compile each source file as a separate translation unit.
- Link the resulting object files into the final executable.

In summary, namespaces in C++ provide a way to group and qualify related
names (such as A::f and A::g) to avoid collisions, while separate
compilation organizes code into headers and source files that are compiled
independently. In my Visual Studio + CMake + Ninja environment, this pattern
is natural: headers declare names in a namespace, ".cpp" files define them,
and the build system compiles each source file separately before linking
everything into a single program.

