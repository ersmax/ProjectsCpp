Points on a two-dimensional plane are specified uniquely using two numbers, the
point’s distance from the horizontal x-axis, and its distance from the vertical y-axis.
The distance between any two points (x1, y1) and (x2, y2) can be calculated using
the formula
s = sqrt((x2 - x1)^2 + (y2 - y1)^2)
Write a program that reads in the x and y coordinates of two points on a plane, and
calculates the distance between them using the above formula.
Ensure that your program uses functions from the cmath library to perform the
calculations.

=============================================================================

Functions:
- `euclideanDistance(int x1, int y1, int x2, int y2)`:
  Calculates and returns the Euclidean distance between two points.

==============================================================================