One way to estimate the height of a child is to use the following formula, which
uses the height of the parents:
Hmale_child = ((Hmother 13/12) + Hfather)/2
Hfemale_child = ((Hfather 12/13) + Hmother)/2
All heights are in inches. Write a function that takes as input parameters the gender
of the child, height of the mother in inches, and height of the father in inches,
and outputs the estimated height of the child in inches. Embed your function in a
program that allows you to test the function over and over again until telling the
program to exit. The user should be able to input the heights in feet and inches,
and the program should output the estimated height of the child in feet and inches.
Use the integer data type to store the heights.

---

## Program Overview

This program estimates the adult height of a child based on the heights of the parents and the child's gender. The user is prompted to enter the heights of the mother and father (in feet and inches) and the gender of the child. The program then calculates and displays the estimated height of the child in feet and inches. The process can be repeated as many times as the user wishes.

---

## Main Components

### 1. `estimatedHeight` Function

**Prototype:**  
`double estimatedHeight(char gender, int motherHeight, int fatherHeight);`

**Description:**  
Calculates the estimated height (in inches) of a child using the following formulas:
- For a male child:  
  \[(\text{motherHeight} \times \frac{13}{12} + \text{fatherHeight}) / 2\]
- For a female child:  
  \[(\text{fatherHeight} \times \frac{12}{13} + \text{motherHeight}) / 2\]

**Parameters:**
- `gender`: Character, either 'M' (male) or 'F' (female).
- `motherHeight`: Mother's height in inches.
- `fatherHeight`: Father's height in inches.

**Returns:**  
Estimated height of the child in inches (as a double).

---

### 2. `main` Function

**Description:**  
Handles user interaction and input validation:
- Prompts the user for the father's and mother's heights (feet and inches), ensuring values are within valid ranges (feet: 5-7, inches: 0-11).
- Prompts for the child's gender, ensuring it is 'M' or 'F'.
- Calls `estimatedHeight` to compute the child's estimated height.
- Converts the result from inches to feet and inches for display.
- Asks the user if they want to repeat the process.

**Input Validation:**
- Uses `while (true)` loops to repeatedly prompt the user until valid input is provided for each value.

---

## Usage

1. Run the program.
2. Enter the father's height (feet and inches).
3. Enter the mother's height (feet and inches).
4. Enter the child's gender ('M' or 'F').
5. View the estimated height of the child.
6. Choose to repeat or exit.

---

## Notes

- All heights are stored and processed as integers (inches).
- The program uses clear error messages for invalid input.
- The loop continues as long as the user enters 'y' or 'Y' when prompted.

---