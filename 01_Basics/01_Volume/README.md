One gallon is 3785.41 milliliters. Write a program that will read the volume of
a package of milk in milliliters, and output the volume in gallons, as well as the
number of packets needed to yield at least one gallon of milk.

=========================================================================

Important notes:
- Use a constant variable to store the conversion factor (ML_PER_GALLON).
- When calculating the number of packets, divide ML_PER_GALLON by the package volume.
- If the division result is not an integer, round up to the next whole number.
- If the division result is an integer (i.e., ML_PER_GALLON is exactly divisible by the package volume), do not add an extra packet.
- To implement this, store the division result in a temporary variable, cast it to int, and compare. If the division result is greater than its integer part, increment the packet count by 1.

Example:
If ML_PER_GALLON = 3785.41 and package volume = 1000 ml:
  division = 3785.41 / 1000 = 3.78541
  packets_needed = 4

If package volume = 3785.41 ml:
  division = 3785.41 / 3785.41 = 1.0
  packets_needed = 1


An alternative solution would be:
- Use a constant variable to store the conversion factor (ML_PER_GALLON).
- When calculating the number of packets, use integer division and the modulo operator:
    packets_needed = static_cast<int>(ML_PER_GALLON / volume_ml) +
                    (static_cast<int>(ML_PER_GALLON) % static_cast<int>(volume_ml) != 0);
- This expression rounds up only if there is a remainder, and does not use an if statement or std::ceil.
- If ML_PER_GALLON is exactly divisible by the package volume, no extra packet is added.

Example:
If ML_PER_GALLON = 3785.41 and package volume = 1000 ml:
  packets_needed = 3 + (3785 % 1000 != 0) = 3 + 1 = 4

If package volume = 3785.41 ml:
  packets_needed = 1 + (3785 % 3785 != 0) = 1 + 0 = 1
