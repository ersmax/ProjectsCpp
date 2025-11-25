The gravitational attractive force between two bodies with masses m1 and m2
separated by a distance d is given by the following formula:
F = Gm1m2 / d^2
where G is the universal gravitational constant:
G = 6.673 * 10^(-8) cm^3 / (g • sec^2)
Write a function definition that takes arguments for the masses of two bodies
and the distance between them and returns the gravitational force between them.

Since you will use the previous formula, the gravitational force will be in dynes.
One dyne equals a (g • cm/sec^2)

You should use a globally defined constant for the universal gravitational constant.
Embed your function definition in a complete program that computes the gravitational
force between two objects given suitable inputs. Your program should allow
the user to repeat this calculation as often as the user wishes.

===============================================================================

The code is designed to calculate the gravitational force between two bodies
using the classical physics formula:

F = (G x m_1 x m_2) / (d^2)

Documentation:

- Choice of Formula:
  The formula is standard in physics for gravitational attraction,
  where G is the universal gravitational constant, m_1 and m_2 are the masses (in grams),
  and d is the distance (in centimeters). The result is in dynes, matching the required units.

- Constant Definition:
  `G` is defined globally as `6.673e-8`,
  matching the value and units specified in the problem statement.

- Function Design:
  The function `gravitationalForce` takes the two masses and the distance as arguments,
  ensuring modularity and reusability.
  It returns the computed force, encapsulating the calculation logic.

- Input Validation:
  The program checks that all inputs are positive, preventing invalid physical scenarios.

- User Interaction:
  The main loop allows repeated calculations, improving usability.

- Precision and Formatting:
  Output is formatted to show ten decimal places, ensuring accuracy and clarity.

================================================================================