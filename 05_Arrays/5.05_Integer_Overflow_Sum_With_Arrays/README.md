An array can be used to store large integers one digit at a time. For example, the
integer 1234 could be stored in the array a by setting a[0] to 1, a[1] to 2, a[2]
to 3, and a[3] to 4. However, for this exercise you might find it more useful to
store the digits backward, that is, place 4 in a[0], 3 in a[1], 2 in a[2], and 1 in
a[3]. In this exercise you will write a program that reads in two positive integers
that are 20 or fewer digits in length and then outputs the sum of the two numbers.
Your program will read the digits as values of type char so that the number
1234 is read as the four characters '1', '2', '3', and '4'. After they are read into
the program, the characters are changed to values of type int. The digits will be
read into a partially filled array, and you might find it useful to reverse the order
of the elements in the array after the array is filled with data from the keyboard.
(Whether or not you reverse the order of the elements in the array is up to you. It
can be done either way, and each way has its advantages and disadvantages.) Your
program will perform the addition by implementing the usual paper-and-pencil
addition algorithm. The result of the addition is stored in an array of size 20 and
the result is then written to the screen. If the result of the addition is an integer with
more than the maximum number of digits (that is, more than 20 digits), then your
program should issue a message saying that it has encountered “integer overflow.”
You should be able to change the maximum length of the integers by changing
only one globally defined constant. Include a loop that allows the user to continue
to do more additions until the user says the program should end.

---

# Summary
This program reads two positive integers (each up to a configurable maximum number of digits), 
stores each number's digits in an array (least-significant digit first), 
computes their sum using the paper-and-pencil digit-addition algorithm, and prints the sum. 
If the sum requires more digits than the allowed maximum, the program reports `integer overflow`.

## Example interaction:
```
Enter the number up to 20 digits, or `exit` to terminate
1234
Enter the number up to 20 digits, or `exit` to terminate
5678
6912
```

## Input rules
- Maximum number of digits is set by the global constant `SIZE` (default: 20).
- Blank or invalid input prompts a retry.
- Enter `exit` to end input and exit the program.

## Behavior and implementation notes
- Digits are stored least-significant-first in the arrays to simplify addition (index 0 = units).
- The addition routine (`sumNumbers`) walks both arrays, adds digits with carry, and writes the result also least-significant-first.
- Before printing, the used portion of the `result` array is reversed so the number is printed most-significant-first. 
  The code uses `std::reverse(result, result + sizeResult)` to reverse the used range in-place.
- If the final carry would make the result longer than `SIZE`, the program prints `integer overflow.` and clears the `result` array.
- `sizeResult` contains the number of digits in the computed result

## Configuring maximum digits
Change the `constexpr int SIZE = 20;` to adjust the maximum supported digits. Only this constant needs to be changed.

## Notes
- The program demonstrates manual big-integer addition using arrays of digits.
- For production, we could use `std::string`/`std::vector` or big-integer libraries that handle arbitrary precision and edge cases.