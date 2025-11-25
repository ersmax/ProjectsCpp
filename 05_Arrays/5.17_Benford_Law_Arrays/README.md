Programming Project 2.12 asked you to explore Benford’s Law. An easier way to
write the program is to use an array to store the digit counts. That is, count[0]
might store the number of times 0 is the first digit (if that is possible in your data
set), count[1] might store the number of times 1 is the first digit, and so forth.
Redo Programming Project 2.12 using arrays.

---

# Overview

This project counts the leading digit (0..9) of integers from a file and reports percentages.

## Function
- `readData(const std::string& path, int& totNumbers, int count[], int size)`
  - Open `path` using `openFile`.
  - Read the file line by line; skip empty lines.
  - Use a string stream to extract integers from each line.
  - For each integer read, call `checkNumber(...)` to update counts.
  - Close the file with `closeFile`.

- `checkNumber(int number, int& totNumbers, int count[], const int size)`
  - Make the value non\-negative safely:
    - Widen to a larger signed type (for example `long long`) before negating to avoid overflow when `number == INT_MIN`.
  - Increment `totNumbers` as soon as a value is observed (zero counts as a valid input).
  - Extract the leading digit:
    - Use integer division in a loop (`while (value >= 10) value /= 10;`) — no allocations and very fast.
    - Alternative: convert to string and take the first character (readable but allocates memory).

- `openFile(const std::string& path, std::fstream& inputStream)`
  - Attempt to open and return success/failure.
  - Caller should print an error and exit the read loop if opening fails.

- `closeFile(const std::string& path, std::fstream& inputStream)`
  - Close the stream.

- `checkBenfordLaw(const int totalNumbers, const int count[], const int size)`
  - If `totalNumbers == 0`, print a message and return to avoid division by zero.
  - For each digit index, compute percentage:
    - `percent = static_cast<double>(count[idx]) / totalNumbers * 100.0`
  - Format output (fixed, one decimal place) and print each bucket.

## Getting the lead digit using string conversion
It is possible to get the leading digit of a number by converting it to a string and
extracting the first character. This approach is straightforward and works well for
integers of any size.

```cpp
void checkNumber(int number, int& totNumbers, int count[], const int size) {
    number = std::abs(number);
    ++totNumbers;
    const std::string s = std::to_string(number);
    int leadingDigit = s[0] - '0';
    if (leadingDigit >= 0 && leadingDigit < size)
        ++count[leadingDigit];
}
```

Alternatively, you can extract the leading digit using mathematical operations, 
which avoids string conversion and works directly with the numeric value.
This method is preferred for performance and simplicity when dealing with integers,
because it does not involve memory allocation or string manipulation.

```cpp
void checkNumber(int number, int& totNumbers, int count[], const int size) {
    number = std::abs(number);
    ++totNumbers;
    while (number >= 10) number /= 10;
    if (number >= 0 && number < size)
        ++count[number];
}
```