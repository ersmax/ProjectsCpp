The type Point is a fairly simple data type, but under another name (the template
class pair) this data type is defined and used in the C++ Standard Template Library,
although you need not know anything about the Standard Template Library
to do this exercise. Write a definition of a class named Point that might be used to
store and manipulate the location of a point in the plane. You will need to declare
and implement the following member functions:
a. A member function set that sets the private data after an object of this class is
created.
b. A member function to move the point by an amount along the vertical and
horizontal directions specified by the first and second arguments.
c. A member function to rotate the point by 90 degrees clockwise around the
origin.
d. Two const inspector functions to retrieve the current coordinates of the point.
Document these functions with appropriate comments. Embed your class in a test
program that requests data for several points from the user, creates the points, then
exercises the member functions.

---