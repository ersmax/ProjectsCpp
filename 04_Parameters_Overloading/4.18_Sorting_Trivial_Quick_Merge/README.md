Write a function named sort that takes three integer parameters by reference.
The function should rearrange the parameter values so that the first parameter
gets set to the smallest value, the second parameter gets set to the second smallest
value, and the third parameter gets set to the largest value. For example, given the
variable assignments a = 30; b = 10; c = 20, the function call sort(a,b,c)
should result in a = 10, b = 20, and c = 30. Note that the array construct covered
in Chapter 5 will give you a way to solve this problem for an arbitrary number of
items instead of only for three items.

A fun addition:
- Try with quick sort/merge sort by copy and by reference

---

# Purpose  
Implements a trivial three-value sort plus two quicksort variants (by-copy and in-place). 
A global `std::mt19937 rng` is used to choose random pivots.

## Functions
 - `trivialSort(int& a, int& b, int& c)`
    - What it does: sorts three integers in ascending order using pairwise comparisons and `std::swap`.
    - I/O: prints the sorted triple to stdout.
    - Complexity: O(1).

- `std::vector<int> quickSort(const std::vector<int>& numbers)` (quicksort by copy)
    - What it does: a functional quicksort that returns a new sorted vector.
    - Pivot: chosen randomly from the input range.
    - Partitioning: builds three vectors — `smaller`, `equal`, `larger` — by comparing elements to the pivot.
    - Recursion: sorts `smaller` and `larger` recursively, then concatenates `smaller + equal + larger` and returns the result.
    - Notes: stable with respect to equal elements in `equal` and simple to reason about; uses extra memory proportional to the input.

- `void quickSortReference(std::vector<int>& numbers)`
    - What it does: wrapper that calls the in-place quicksort helper and prints the resulting vector.
    - Precondition: `numbers` must be a valid vector.
    - Behavior: prints elements separated by spaces.

- `void quickSortInPlace(std::vector<int>& numbers, int low, int high)` (in-place quicksort using Hoare partition)
    - What it does: sorts the subarray `numbers[low..high]` in place using quicksort with Hoare partitioning.
    - Pivot: chosen randomly with `std::uniform_int_distribution` on the inclusive index range `[low, high]`.
    - Partitioning (Hoare): advances two indices from the ends toward each other, swapping elements that are on the wrong side of the pivot, and stops when the indices cross. After partitioning the algorithm recurses on the two resulting subranges.
    - Important invariants: `low` and `high` are inclusive indices.

- Complexity summary
    - `trivialSort`: O(1) time, O(1) space.
    - `quickSort` (by-copy): average O(n log n) time, worst-case O(n^2), O(n) extra space.
    - `quickSortInPlace`: average O(n log n) time, worst-case O(n^2), in-place (O(log n) recursion stack on average).
