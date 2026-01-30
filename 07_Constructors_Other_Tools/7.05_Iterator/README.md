In an ancient land, the beautiful princess Eve had many suitors.She decided on
the following procedure to determine which suitor she would marry.First, all of
the suitors would be lined up one after the other and assigned numbers.The first
suitor would be number 1, the second number 2, and so on up to the last suitor,
number n. Starting at the first suitor she would then count three suitors down
the line (because of the three letters in her name) and the third suitor would be
eliminated from winning her hand and removed from the line. Eve would then
continue, counting three more suitors, and eliminating every third suitor. When
she reached the end of the line she would continue counting from the beginning.
For example, if there were six suitors then the elimination process would proceed
as follows:
123456 initial list of suitors, start counting from 1
12456 suitor 3 eliminated, continue counting from 4
1245 suitor 6 eliminated, continue counting from 1
125 suitor 4 eliminated, continue counting from 5
15 suitor 2 eliminated, continue counting from 5
1 suitor 5 eliminated, 1 is the lucky winner
Write a program that uses a vector to determine which position you should stand
in to marry the princess if there are n suitors. You will find the following function
from the Vector class useful:
v.erase(iter);
// Removes element at position iter
For example, to use this function to erase the fourth element from the beginning
of a vector variable named theVector, use
theVector.erase(theVector.begin( ) + 3);
The number 3 is used because the first element in the vector is at index position 0.

---

## Algorithm Logic

### Overview
This is a variant of the **Josephus Problem** - a classic elimination problem where participants 
stand in a circle and every k-th person is eliminated until only one remains.

### Key Components

#### 1. **Initialization**
- Create a vector with suitors numbered 1 to n
- Start with an iterator pointing to the first suitor

#### 2. **Elimination Process**
The `selectContender()` function implements the core algorithm:

```
While more than 1 suitor remains:
  1. Count POSITION-1 times forward (current position counts as 1)
     - Increment iterator
     - If iterator reaches .end(), wrap to .begin()
  2. Erase the suitor at current position
     - Capture the returned iterator (points to next element)
     - If returned iterator is .end(), wrap to .begin()
```

#### 3. **Important Iterator Concepts**

**`.end()` behavior:**
- Returns an iterator pointing to **one past the last element**
- Cannot dereference `.end()` - it's a sentinel value
- Must wrap to `.begin()` when reaching `.end()`

**`.erase()` behavior:**
- **Invalidates** the iterator passed to it
- **Returns** a new iterator pointing to the next element
- If last element is erased, returns `.end()`
- This is the reason why we check whether the returned iterator is `.end()` and wrap if necessary
- **Must** capture the return value: `current = suitors.erase(current)`

**Iterator invalidation:**
```cpp
suitors.erase(current);        // current is now INVALID, and no valid iterator to use
if (current == suitors.end())  // Undefined behavior!

current = suitors.erase(current);  // Get valid iterator (next element)
if (current == suitors.end())      // Safe to use
```

#### 4. **Counting Logic**
- Loop from `idx = 1` to `idx < POSITION` (not `idx = 0`)
- Why? This is because the **current position counts as "1"**
- To eliminate every 3rd person, advance 2 times from current position

### Example Trace (6 suitors)
```
{1,2,3,4,5,6}, current=1
  Count 2: 1→2→3, erase 3
{1,2,4,5,6}, current=4
  Count 2: 4→5→6, erase 6, wrap to 1
{1,2,4,5}, current=1
  Count 2: 1→2, erase 2
{1,4,5}, current=4
  Count 2: 4→5, erase 5
{1,4}, current=1 (after wrap)
  Count 2: 1→4, erase 4
{1} → Winner is 1
```

---

#### References
- [.erase() function](https://cplusplus.com/reference/vector/vector/erase/)