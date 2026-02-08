Write a program that outputs a histogram of grades for an assignment given to
a class of students. The program should input each student’s grade as an integer
and store the grade in a vector. Grades should be entered until the user enters −1
for a grade. The program should then scan through the vector and compute the
histogram. In computing the histogram, the minimum value of a grade is 0, but
your program should determine the maximum value entered by the user. Output
the histogram to the console. See Programming Project 5.7 for information on how
to compute a histogram.
Output the histogram count at the end. For example, if the input grades are 3, 0,
1, 3, 3, 5, 5, 4, 5, 4, then the program should output
1 grade(s) of 0
1 grade(s) of 1
0 grade(s) of 2
3 grade(s) of 3
2 grade(s) of 4
3 grade(s) of 5

---

## Implementation Logic

The implementation uses a **sort-then-count** approach with three different counting strategies:

### Main Algorithm Flow:
1. **Input Phase** (`input` function):
   - Reads grades from user until -1 is entered
   - Validates input (non-negative integers only)
   - Stores all grades in a vector

2. **Sorting Phase** (`mergeSort` + `sort` functions):
   - Uses **merge sort** algorithm (O(n log n) complexity)
   - Recursively divides the array into halves
   - Merges sorted halves by comparing elements from left and right subarrays
   - After sorting, identical grades are adjacent (e.g., [0, 1, 3, 3, 3, 4, 4, 5, 5, 5])

3. **Counting Phase** (three implementations provided):

#### **`count` (Recommended)** - O(n) time, O(n) space:
   - Takes a **const** reference (doesn't modify original vector)
   - Scans sorted vector once from left to right
   - When consecutive elements are equal: increments the frequency counter
   - When elements differ: starts a new unique grade with frequency 1
   - Maintains two parallel vectors: `uniqueNumbers` and `frequencies`
   - Example: `[1, 2, 2, 3]` → `uniqueNumbers=[1, 2, 3]`, `frequencies=[1, 2, 1]`

#### **`count2` (Iterator-based with erase)** - O(n²) worst-case:
   - Uses iterators exclusively (no indices)
   - When duplicate found: erases the next element and increments frequency
   - `erase(current + 1)` removes element after current, keeping current valid
   - **Tradeoff**: Modifies the input vector but avoids extra storage
   - **Caveat**: Each erase operation is O(n), making total complexity quadratic

#### **`count3` (Mixed iterator/index)** - O(n²) worst-case:
   - **Not recommended**: Mixes iterators and indices, lacking in readability
   - Uses `erase(current)` which erases the element at current position
   - Must reassign iterator after erase to keep it valid
   - kept for practial purposes to show the differences with iterators and copying vectors

4. **Output Phase** (`print` function):
   - Iterates through `uniqueNumbers` and `frequencies` in parallel
   - Prints in format: `"3 grade(s) of 5"`

### Key Design Decisions:
- **Why do I sort first?** To reduce time complexity.
  If the users adds more elements later, new duplicates may be added. 
  Sorting ensures that duplicates are adjacent, allowing for O(n) counting later 
  instead of O(n²) if we were to check for duplicates in an unsorted vector.

- **Why merge sort?** Stable, predictable O(n log n) performance

- **Why three implementations?** Practical comparison of approaches:
  - `count`: Best time complexity, worst space complexity, by copying unique numbers in new vector.
  - `count2`: Shows iterator-only approach with modification. Best for space complexity.
  - `count3`: Demonstrates anti-pattern (mixing iterators/indices) and for practcing iterators with erase.

### Complexity Analysis:
- **Overall**: O(n log n) due to sorting (counting is O(n)), if count is used. Else O(n²) for count2 and count3.
- **Space**: O(n) for auxiliary vectors and merge sort workspace

### Note on Missing Grades:
Current implementation only outputs grades that were entered. 
The program does not show 0 counts for missing grades from 0 to max.
This is done on purpose to avoid cluttering output with grades that were not entered.

