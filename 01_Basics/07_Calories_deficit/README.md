A person runs on a treadmill for fifteen minutes a day as part of their exercise
routine. They start the workout at a speed of 4 MPH for the first three minutes,
and then increase it by 2 MPH after every four minutes. Write a program to
calculate the total calories burned during this workout. The number of calories
burned may be estimated using the formula:
Calories/Minute = 0.0175 X (Number of metabolic equivalents (MET)) X (Weight in kilograms)
Running at 6 MPH expends 10 METS. Your program should input the person’s
weight in kilograms and output the calories burned by them.



=================================================================

The program uses a combination of `if` and `while` statements to model
the workout intervals and calculate calories burned:

- `if constexpr`: Used to process the first interval (3 minutes at 4 MPH).
   This ensures the initial part of the workout is handled before the main loop.
- `while` loop: Iterates through the remaining workout time,
   increasing speed and calculating calories for each interval.
   The loop continues until the total workout time is reached.
- `min` function: Ensures that the last interval does not exceed the total workout time.

Process Explanation:
1. The user inputs their weight.
2. The first interval (3 minutes at 4 MPH) is processed using the `if` block.
3. The `while` loop handles subsequent intervals, each 4 minutes long,
   increasing speed by 2 MPH after each.
4. Calories for each interval are calculated using the provided formula and accumulated.
5. The total calories burned are displayed.


A choice of using constants for the MET values and time intervals is made to enhance
code readability and maintainability. This approach allows for easy adjustments to the
workout parameters if needed in the future.
=================================================================