This problem is based on a “Nifty Assignment” by Steve Wolfman (http://nifty.
stanford.edu/2006/wolfman-pretid). Consider lists of numbers from real-life data
sources, for example, a list containing the number of students enrolled in different
course sections, the number of comments posted for different Facebook status
updates, the number of books in different library holdings, the number of votes per
precinct, etc. It might seem like the leading digit of each number in the list should
be 1–9 with an equally likely probability. However, Benford’s Law states that the
leading digit is 1 about 30% of the time and drops with larger digits. The leading
digit is 9 only about 5% of the time.
Write a program that tests Benford’s Law. Collect a list of at least one hundred
numbers from some real-life data source and enter them into a text file. Your program
should loop through the list of numbers and count how many times 1 is the
first digit, 2 is the first digit, etc. For each digit, output the percentage it appears
as the first digit.
If you read a number into the string variable named strNum then you can access
the first digit as a char by using strNum[0]. This is described in more detail in
Chapter 9.

=========================================================================================

This program reads numbers from a text file and analyzes the distribution
of their leading digits to test Benford’s Law.

For each number, it extracts the first character (`strNum[0]`),
checks if it is a digit, and converts it to its integer value by subtracting `'0'`.
This works because digit characters in ASCII are sequential:
`'0'` is 48, `'1'` is 49, ..., so `'5' - '0'` gives 5.
In other words, subtracting the character `'0'` from a digit character
converts it to its corresponding integer value.

The array `digitCount[9]` is used to store counts for digits 1 through 9.
Each index corresponds to a digit:
index 0 for digit 1, index 1 for digit 2, ..., index 8 for digit 9.
This allows efficient counting and easy calculation of percentages for each leading digit.

==========================================================================================