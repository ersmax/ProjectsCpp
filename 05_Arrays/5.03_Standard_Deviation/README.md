The standard deviation of a list of numbers is a measure of how much the numbers
deviate from the average. If the standard deviation is small, the numbers are
clustered close to the average. If the standard deviation is large, the numbers are
scattered far from the average. The standard deviation, S, of a list of N numbers xi
is defined as follows:
S = sqrt ( sum from i=1 to N of (xi - X)^2 / N ),
where X is the average of the N numbers x1, x2, … . 
Define a function that takes a
partially filled array of numbers as its argument and returns the standard deviation
of the numbers in the partially filled array. Since a partially filled array requires two
arguments, the function will actually have two formal parameters: an array parameter

---
# Overview
- The program demonstrates computing the population standard deviation:
  S = sqrt( sum_{i=1..N} (x_i - X)^2 / N )
  where X is the average of the N numbers.
- It uses a fixed-size array and a "partially filled array" pattern: the array capacity is passed along with the number of elements actually used.

## Program behavior
- On start the program prompts:
  - "Enter up to 10 numbers (or `exit` to end)."
- Input rules:
  - Enter numbers separated by whitespace.
  - Type `exit` to stop input early.
  - Non-numeric tokens (other than `exit`) are reported as invalid and the prompt continues.
- After input ends, the program prints the entered values and their standard deviation.

Key functions
- `void fillArray(double numbers[], std::size_t size, int& numberUsed)`
  - Reads up to `size` numbers into `numbers`.
  - Stops early if the user types `exit`.
  - Sets `numberUsed` to the count of values stored.
  - Performs basic validation: uses `std::stod` to verify tokens are valid doubles.
- `double computeStandardDev(const double numbers[], std::size_t size, int numberUsed)`
  - Computes and returns the population standard deviation for the first `numberUsed` elements.
  - If `numberUsed <= 0`, returns `0.0`.
  - Uses two passes: one to compute the mean, another to accumulate squared deviations.

Notes and design decisions
- The program uses a fixed capacity (`SIZE = 10`) and models a partially filled array by passing both the array and the used count.
- `std::span` is used in `main` only for concise printing of the used subrange.
- `assert` checks that `numberUsed` does not exceed the array capacity.
- The implementation computes the population standard deviation (division by N), not the sample standard deviation (which would divide by N-1).
- Error handling for invalid input uses `std::cin` clearing and a `try/catch` around `std::stod`.

Example session
- Input:
  - `1.0 2.0 3.0 4.0 exit`
- Output:
  - `1 2 3 4`
  - `Their standard deviation is 1.11803` (approx.)