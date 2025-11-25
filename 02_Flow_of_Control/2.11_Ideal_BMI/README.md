(This is an extension of an exercise from Chapter 1.) A simple rule to estimate
your ideal body weight is to allow 110 pounds for the first 5 feet of height and 5
pounds for each additional inch. Create the following text in a text file. It contains
the names and heights in feet and inches of Tom Atto (6'3"), Eaton Wright (5'5"),
and Cary Oki (5'11"):
Tom Atto
6
3
Eaton Wright
5
5
Cary Oki
5
11
Write a program that reads the data in the file and outputs the full name and ideal
body weight for each person. Use a loop to read the names from the file. Your
program should also handle an arbitrary number of entries in the file instead of
handling only three entries.

======================================================================================

This program calculates the ideal body weight for each person listed in a text file,
using a simple rule: 110 pounds for the first 5 feet of height,
plus 5 pounds for each additional inch.
The input file contains multiple entries, each with a person's full name,
height in feet, and height in inches.

How the Code Works:

- The program opens a text file containing the data.
- It reads each person's first name, last name, feet, and inches in a loop,
  allowing for any number of entries.
- For each entry, it calls a function to calculate the ideal body weight
  based on the provided height.
- If the height is less than 5 feet or greater than or equal to 8 feet,
  an error message is printed to the standard error stream, and the entry is skipped.
- For valid entries, the program prints the person's full name
  and their calculated ideal body weight to the console.
- The file is closed after processing all entries.

Key Points:

- Uses `fstream` to read data from a file.
- Uses input extraction (`>>`) to read individual data fields.
- Handles errors in input data gracefully.
- Supports an arbitrary number of entries in the input file.

It is important that the last person has firstName, lastName, feet, and inches in the file.
If any of these are missing, the program will end.
This is the reason why the while loop checks for firstName, lastName, feet, and inches
in the while condition.