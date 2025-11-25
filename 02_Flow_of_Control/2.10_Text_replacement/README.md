Create a text file that contains the text “I hate C++ and hate programming!” Write
a program that reads in the text from the file and outputs each word to the console
but replaces any occurrence of “hate” with “love.” Your program should work with
any line of text that contains the word “hate,” not just the example given in this
problem.
=====================================================================================

This program reads text from a file and outputs each word to the console,
replacing any occurrence of the word `hate` with `love`.
It processes the file line by line, then splits each line into words for replacement and output.

How to Read a Line from a File:

- Use `getline(inputStream, line)` to read a line from
  the file stream (`inputStream`) into the string variable `line`.
- This reads characters until a newline (`\n`) is found,
  storing the result in `line`.

How to Read a Word from a Line:

- Create an `istringstream` object from the line: `istringstream iss(line);`
- Use the extraction operator (`>>`) in a loop:
  `while (iss >> word)` to read each word from the line into the string variable `word`.

Summary:
- `getline(fstream, string)` reads a line from a file.
- `istringstream` with `>>` reads words from a line.
- The code replaces `hate` with `love` and prints each word.

================================================================================