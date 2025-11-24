A government research lab has concluded that an artificial sweetener commonly
used in diet soda will cause death in laboratory mice. A friend of yours is desperate
to lose weight but cannot give up soda. Your friend wants to know how much diet
soda it is possible to drink without dying as a result. Write a program to supply
the answer. The input to the program is the amount of artificial sweetener needed
to kill a mouse, the weight of the mouse, and the weight of the dieter. To ensure
the safety of your friend, be sure the program requests the weight at which the
dieter will stop dieting, rather than the dieter’s current weight. Assume that diet
soda contains one-tenth of 1% artificial sweetener. Use a variable declaration with
the modifier const to give a name to this fraction. You may want to express the
percentage as the double value 0.001.

=================================================================

Program Description:
This program estimates the maximum amount of diet soda a person
can safely consume without reaching a lethal dose of artificial sweetener.
The calculation is based on toxicity data from laboratory mice and scaled
proportionally to the dieter’s target weight.

How it Works:
The user provides three inputs:
- The amount of sweetener lethal to a mouse (in grams).
- The weight of the mouse (in kilograms).
- The target weight of the dieter (in kilograms).

The program calculates the lethal sweetener concentration per gram
of body weight using the mouse data.
It then scales this concentration to the dieter’s target weight
to find the maximum total amount of sweetener they could ingest without risk.

Since diet soda contains 0.1% (0.001 as a fraction) artificial sweetener,
the program computes the maximum safe amount of soda accordingly.

Finally, the result is displayed in kilograms of soda.

Key Features:
- Uses a constant (const) for the sweetener concentration in soda.
- Converts weights consistently into grams for calculation.
- Ensures safety by requiring the target weight instead of current weight.