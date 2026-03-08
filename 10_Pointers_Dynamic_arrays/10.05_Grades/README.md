This programming project is based on Programming Projects 7.8 and 5.7. Write
a program that outputs a histogram of grades for an assignment given to a class of
students. The program should input each student’s grade as an integer and store
the grade in a vector. Grades should be entered until the user enters -1 for a grade.
The program should then scan through the vector and compute the histogram. In
computing the histogram, the minimum value of a grade is 0, but your program
should determine the maximum value entered by the user. Use a dynamic array to
store the histogram. Output the histogram to the console.

--- 

## Logic and Structure of `10.05_Grades.cpp`

This program reads an arbitrary number of student grades, sorts them, and prints a histogram 
showing how many times each unique grade was entered. 
The implementation uses dynamic arrays and manual memory management.

### Main Steps

1. **Input Grades Dynamically**
   - The user is prompted to enter grades one by one.
   - Grades are stored in a dynamic array (`grades`), which doubles in size as needed.
   - Input ends when the user enters `-1`.

2. **Sort the Grades**
   - The grades array is sorted in ascending order using a custom merge sort implementation.

3. **Count Unique Grades and Their Frequencies**
   - The sorted array is scanned to count how many different grades were entered.
   - A new dynamic array is created to store only the unique grades.
   - Another dynamic array stores the frequency (count) of each unique grade.
   - The original grades array is replaced with the compacted array of unique grades.

4. **Print the Histogram**
   - For each unique grade, the program prints the number of times it was entered.

5. **Memory Cleanup**
   - All dynamically allocated arrays are deleted before the program exits.

---

### Function Roles

- **`addGrades`**: Handles user input and dynamic resizing of the grades array.
- **`mergeSort` / `sort`**: Sorts the grades array in ascending order using merge sort.
- **`countDifferent`**: Counts the number of unique grades in the sorted array.
- **`countFrequencies`**: Compacts the sorted array to unique grades and creates a parallel array of their frequencies.
- **`printHistogram`**: Prints each unique grade and its frequency in a formatted way.
- **`inputValidation`**: Ensures only valid integer input is accepted from the user.

---

### Example Output

For input: `3, 0, 1, 3, 3, 5, 5, 4, 5, 4`  
The output will be:
```
  1 grade(s) of 0
  1 grade(s) of 1
  3 grade(s) of 3
  2 grade(s) of 4
  3 grade(s) of 5
```
Only grades that were actually entered are shown.

