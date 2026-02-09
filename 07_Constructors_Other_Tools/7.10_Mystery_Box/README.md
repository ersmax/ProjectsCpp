 First, complete Programming Project 6.12. Modify the main function with a loop
so that the user determines how many BoxOfProduce objects are created. Each box
should contain three bundles of fruits or vegetables selected randomly from this
list: tomatillo, broccoli, tomato, kiwi, and kale. Add a menu so the user can decide
when to stop creating boxes. The menu should allow the user to make substitutions
for the randomly selected items in a box.
You would like to throw in a free recipe flyer for salsa verde if the box contains
tomatillos. However, there are only 5 recipe flyers. Add a static member variable
to the BoxOfProduce class that counts the number of recipe flyers remaining and
initialize it to 5. Also add a member variable that indicates whether or not the box
contains a recipe flyer and modify the output function to also print “salsa verde
recipe” if the box contains a recipe flyer. Finally, add logic inside the class so that if
the box contains at least one order of tomatillos then it automatically gets a recipe
flyer until all of the recipe flyers are gone. Note that a box should only get one
recipe flyer even if there are multiple orders of tomatillos.
Test your class by creating boxes with tomatillos from your menu until all of the
flyers are gone.

---

