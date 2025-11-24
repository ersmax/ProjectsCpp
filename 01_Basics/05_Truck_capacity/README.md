Write a program that determines whether a truck is loaded beyond its rated capacity.
The program will read in the truck’s maximum load capacity (in metric tons), the
number of boxes it’s carrying, and the average weight of a box. If the total weight of
the boxes is less than or equal to the truck’s capacity, the program announces that the
truck can legally carry all boxes and tells how many additional boxes can be added. If
the number of boxes exceeds the maximum capacity, the program announces that the
truck is overloaded and tells how many boxes must be removed.



================================================================================
The program determines if a truck is overloaded based on:
- user input for maximum load capacity;
- number of boxes;
- and average box weight.

It calculates the total weight of the boxes and compares it to the truck's capacity:

- If the total weight is within the truck's capacity,
  it computes and displays how many more boxes can be added.
- If the truck is overloaded,
  it calculates and displays how many boxes must be removed to meet the legal limit.

The program uses type casting to handle conversions between `int` and `float`
for accurate calculations and avoids narrowing conversion warnings
by explicitly casting values in conditional checks.

A choice has been made to avoid using ceiling functions for simplicity,
and instead uses integer division to determine the number of boxes
that can be added or need to be removed.

User input is handled via the console, and results are displayed with clear messages.