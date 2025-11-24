Write a program that inputs an integer that represents a length of time in seconds.
The program should then output the number of hours, minutes, and seconds that
corresponds to that number of seconds. For example, if the user inputs 50391 total
seconds then the program should output 13 hours, 59 minutes, and 51 seconds.


================================================================

This program converts a user-inputted total number of seconds into hours, minutes, and seconds.

Code Choices Explained:
- Input/Output: Uses `cin` and `cout` for simple console interaction.
- Variable Declaration: Declares all variables as `int` since time values are whole numbers.
- Time Conversion Logic:
  - Calculates hours by dividing total seconds by 3600 seconds/h (60 minutes X 60 seconds/minute).
  - Calculates minutes by taking the remainder after hours (`total_seconds % 3600`)
    and dividing by 60 seconds/minute, which gives dimension minutes.
  - Calculates seconds by taking the remainder after minutes (`total_seconds % 60 seconds/minute`).

Process Overview:
1. Prompt the user for the total number of seconds.
2. Compute hours, minutes, and seconds using integer division and modulo.
3. Output the result in a descriptive format.

================================================================