Using dynamic arrays, implement a polynomial class with polynomial addition,
subtraction, and multiplication.
Discussion: A variable in a polynomial does nothing but act as a placeholder for
the coefficients. Hence, the only interesting thing about polynomials is the array
of coefficients and the corresponding exponent. Think about the polynomial
x*x*x + x + 1
Where is the term in x*x? One simple way to implement the polynomial class is to
use an array of type double to store the coefficients. The index of the array is the
exponent of the corresponding term. If a term is missing, then it simply has a zero
coefficient.
There are techniques for representing polynomials of high degree with many missing terms. 
These use so-called sparse matrix techniques. Unless you already know
these techniques, or learn very quickly, do not use these techniques.
Provide a default constructor, a copy constructor, and a parameterized constructor
that enables an arbitrary polynomial to be constructed.
Supply an overloaded operator = and a destructor.
Provide these operations:
polynomial + polynomial, constant + polynomial, polynomial + constant,
polynomial - polynomial, constant - polynomial, polynomial - constant.
polynomial * polynomial, constant * polynomial, polynomial * constant,
Supply functions to assign and extract coefficients, indexed by exponent.
Supply a function to evaluate the polynomial at a value of type double.
You should decide whether to implement these functions as members, friends, or
standalone functions.

---

## Code Logic Overview: 10.02_Polynomial_class.cpp

This file implements a `Polynomial` class using dynamic arrays to store polynomial coefficients. 
The main logic and features are:

- **Data Representation:**  
  - The coefficients are stored in a dynamic array (`double*`), where the index represents the exponent.
  - The degree of the polynomial is tracked as an integer.

- **Constructors and Destructor:**  
  - Default constructor initializes a zero polynomial.
  - Parameterized constructor allows creation from an array of coefficients and a degree.
  - Copy constructor performs a deep copy.
  - Destructor deallocates the dynamic array.

- **Assignment Operator:**  
  - Overloaded `operator=` for deep copy assignment.

- **Arithmetic Operators:**  
  - Overloaded `+`, `-`, `*` for polynomial-polynomial and polynomial-constant operations (as members and friends).
  - Handles addition, subtraction, and multiplication, returning new `Polynomial` objects.

- **Coefficient Access:**  
  - Overloaded `operator[]` for both reading (R-Value) and writing (L-Value) coefficients by exponent.

- **Evaluation (Horner's Method):**  
  - The `evaluate(double)` method computes the value of the polynomial at a given point using **Horner’s method**.
  - **Horner’s method** is an efficient algorithm for evaluating polynomials. 
    Instead of computing each term separately (which would require many multiplications and powers), 
    it rewrites the polynomial in nested form:
    - For example, a polynomial `a_n*x^n + ... + a_1*x + a_0` is rewritten as  
      `(...((a_n*x + a_{n-1})*x + a_{n-2})*x + ... + a_1)*x + a_0`
    - This reduces the number of multiplications and additions, making the evaluation much faster, especially for high-degree polynomials.
    - In the code, this is implemented by looping from the highest degree down to zero, updating the result as `result = result * x + coefficient`.
    - Time complexity is reduced from O(n^2) to O(n), where n is the degree of the polynomial.

- **Input/Output:**  
  - Overloaded `>>` and `<<` operators for reading and printing polynomials.
  - Input expects degree and coefficients; output prints in standard polynomial form, omitting zero terms.

- **Error Handling:**  
  - Throws exceptions for out-of-range coefficient access.
  - Ensures the highest-degree coefficient is nonzero on input.
