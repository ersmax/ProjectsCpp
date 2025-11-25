Write a function called deleteRepeats that has a partially filled array of characters
as a formal parameter and that deletes all repeated letters from the array. Since a
partially filled array requires two arguments, the function will actually have two
formal parameters: an array parameter and a formal parameter of type int that
gives the number of array positions used. When a letter is deleted, the remaining
letters are moved forward to fill in the gap. This will create empty positions at
the end of the array so that less of the array is used. Since the formal parameter is
a partially filled array, a second formal parameter of type int will tell how many
array positions are filled. This second formal parameter will be a call-by-reference
parameter and will be changed to show how much of the array is used after the
repeated letters are deleted. For example, consider the following code:
char a[10];
a[0] = 'a';
a[1] = 'b';
a[2] = 'a';
a[3] = 'c';
int size = 4;
deleteRepeats(a, size);
After this code is executed, the value of a[0] is 'a', the value of a[1] is 'b', the
value of a[2] is 'c', and the value of size is 3. (The value of a[3] is no longer
of any concern, since the partially filled array no longer uses this indexed variable.)
You may assume that the partially filled array contains only lowercase letters. Embed
your function in a suitable test program.

---

# Overview of deleteRepeats with Three-Pointer Pattern

- `main` 
  Declares letters and numberUsed, calls fillArray to populate the partially filled array, 
  calls removeDuplicates to remove repeated letters, then prints the used portion.
- `fillArray(char letters[], const std::size_t size, int& numberUsed)`
   Reads tokens from std::cin into a std::string. 
   If the token equals -1 the function breaks immediately. 
   Validates the token is a single alphabetic character, stores it, and counts how many were read. 
   At the end sets numberUsed to the number of valid entries read. 
-  `removeDuplicates(char letters[], const std::size_t /*size*/, int& numberUsed)`
   Uses three indices: p1 (anchor for current kept value), p3 (scanner scanning the remainder), 
   and p2 (write position for the next non-duplicate relative to p1).
   For each p1 from 0 to numberUsed-1: set p2 = p3 = p1 + 1. Scan p3 forward; 
   when letters[p3] != letters[p1] copy letters[p3] into letters[p2++]. 
   After the scan set numberUsed = p2 to truncate duplicates of letters[p1].
   This preserves the first occurrence of each letter and compacts later unique elements forward. 
   It reduces repeated shifting per deletion (fewer writes) but remains O(n^2) worst-case for comparisons.

## Three-pointer pattern (`p1`, `p2`, `p3`) — detailed behavior
- Roles
    - `p1`: anchor index for the current kept value (first occurrence to keep).
    - `p2`: write position for the next element that is NOT a duplicate of `letters[p1]` (initially `p1 + 1`).
    - `p3`: scanner that walks the remainder of the used range looking for values to keep (initially `p1 + 1`).
- Inner loop (one pass for a fixed `p1`)
    1. Set `p2 = p3 = p1 + 1`.
    2. While `p3 < numberUsed`:
        - If `letters[p3] != letters[p1]` then move the non-duplicate into the write slot 
         (`letters[p2] = letters[p3]` or `std::swap(letters[p2], letters[p3])`) then `++p2`.
        - Always `++p3`.
    3. After the scan set `numberUsed = p2` to truncate any duplicates of `letters[p1]` that were at the end of the current used range.
- Effect across iterations
    - The first occurrence at each `p1` is preserved in place (stable order).
    - Later unique elements are compacted forward into the gap(s) created by removed duplicates.
    - `p1` then advances to the next index and the process repeats until `p1` reaches the (shrinking) `numberUsed`.

## Behavioral notes and complexity
- Preserves first occurrences and relative order of remaining elements.
- The implementation uses `std::swap` for compaction; a simpler approach is assignment `letters[p2] = letters[p3]`
- Time: O(n^2) worst case (nested scanning for each `p1`).
- Space: O(1) extra.

## Example
- Input: `a b a c` (numberUsed = 4) -> After `removeDuplicates`: `a b c` (numberUsed = 3).
