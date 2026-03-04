Write a program that accepts a line of text input from the user and checks if the
number of words counted from both end of the text is equal. Your program should
work by using two pointers. The ‘head’ pointer should be set to the address of the
first character in the string, and the ‘tail’ pointer should be set to the address of the
last character in the string (i.e., the character before the terminating null). The
program should keep incrementing the “head” pointer and keep decrementing
the “tail” pointer until the pointers reach the other end. On finding whitespace
characters while going across the string, increment the word counts and compare
them at the end.

---

## Program Logic Documentation
This program reads a line of text from the user and checks if the number of words counted 
from both the front and the back of the string are equal. The logic is implemented using two functions, 
each using pointer arithmetic to traverse the string:

### `countFront`
- Uses a pointer (`frontPtr`) starting at the first character of the string.
- Skips any leading spaces.
- For each word (a sequence of non-space characters), increments a counter.
- Advances the pointer past the word and repeats until the end of the string (`'\0'`).
- Returns the total word count from the front.

### `countBack`
- Uses a pointer (`backPtr`) starting at the last character of the string.
- Skips any trailing spaces.
- For each word (a sequence of non-space characters), increments a counter.
- Moves the pointer backward past the word and repeats until the start of the string.
- Returns the total word count from the back.

### Main Program
- Reads a line of input using `std::getline`.
- Calls both `countFront` and `countBack` on the input.
- Compares the results and prints whether the word counts are the same or different.
- Includes several test cases to verify correctness for various input scenarios 
  (leading/trailing/multiple spaces, empty string).

### Notes
- Both functions use pointer arithmetic and character checks, not advanced string features.
- The logic is robust against leading/trailing/multiple spaces and empty input.

