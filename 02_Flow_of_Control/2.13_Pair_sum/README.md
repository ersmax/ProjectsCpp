Create a text file that contains 10 integers with one integer per line. You can enter
any 10 integers that you like in the file. Then write a program that inputs a number
from the keyboard and determines if any pair of the 10 integers in the text file adds
up to exactly the number typed in from the keyboard. If so, the program should
output the pair of integers. If no pair of integers adds up to the number, then the
program should output “No pair found.”

====================================================================================

This program solves the following problem:

Logic Overview:
1. Open the text file and read 10 integers into an array.
2. Prompt the user for a target sum.
3. Use nested loops to check every possible pair of integers in the array.
4. For each pair whose sum matches the target, output the pair and increment a solution counter.
5. If no pairs are found, output “No pair found.”

File Input Alternatives:
- The code uses a `for` loop to read exactly 10 integers.
- A commented-out `while` loop is provided as an alternative for more flexible input.
However, if more than 10 integers are present, the `for` loop ensures only the first 10 are read.
The while loop could cause errors if the file contains fewer than 10 integers.
That is because the array is statically defined to hold only 10 integers.

Edge Cases:
- If the file cannot be opened, the program exits with an error message.
- If no pairs match the target sum, a message is displayed.

Usage:
- Place 10 integers in the file `99_Text_files/2_13_Pair_sum.txt`, one per line.
- Run the program and enter a target number when prompted.
- The program will display all pairs that sum to the target, or indicate if none are found.

====================================================================================