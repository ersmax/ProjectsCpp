You have four identical prizes to give away and a pool of 25 finalists. The finalists
are assigned numbers from 1 to 25. Write a program to randomly select the
numbers of 4 finalists to receive a prize. Make sure not to pick the same number
twice. For example, picking finalists 3, 15, 22, and 14 would be valid but picking
3, 3, 31, and 17 would be invalid, because finalist number 3 is listed twice and 31
is not a valid finalist number.

---

## Price Winners Lottery - Solution Approaches

This program randomly selects 4 unique winners from a pool of 25 finalists, 
each assigned a number from 1 to 25. 
The selection ensures no duplicate winners and only valid finalist numbers.

### Approach 1: Swap and Shrink Pool

- Participants are stored in an array.
- For each winner, a random index is chosen.
- The selected participant is swapped with the last in the pool, and the pool size is reduced.
- This prevents re-selection of previous winners efficiently.

### Approach 2: Boolean Flag Array

- Each participant is tracked using a boolean array.
- When a winner is selected, their corresponding flag is set to true.
- The process repeats until all prizes are assigned, guaranteeing uniqueness.

### Common Features

- Both approaches seed the random number generator once at program start.
- Participant numbers are initialized from 1 to 25.
- The winners are displayed with their corresponding prize numbers.

These methods ensure fair and unique selection of winners according to the problem requirements.

### Differences in Implementation
- The first approach modifies the participant array directly, with a shrinking pool.
- The second method uses a boolean array to track selected winners without altering the original participant list.