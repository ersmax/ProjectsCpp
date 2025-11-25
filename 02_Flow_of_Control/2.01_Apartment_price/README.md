A real-estate developer wants to estimate the cost of each apartment on each floor
of his development before he starts marketing them. He has decided to quote different
prices for apartments on different floors. The price for all apartments on
the first floor is a sum of their base price, charges on amenities, and taxes. The
apartments from the second floor on will see a 2% increase in their base price.
For example, if an apartment on the first floor has a base price of $650,000, an
apartment on the second floor would have a base price of $663,000. Charges
on amenities are charged at a specified rate on an apartment’s base price. Taxes
are calculated at a specified rate on the sum of an apartment’s base price and the
charges on amenities. Your program asks for the number of stories, the base price
of apartments on the first floor, and the rates (as a decimal) of the charges on amenities,
and taxes. The program should output the base price, charges on amenities,
taxes, and the total price of apartments on each floor. (Hint: Use a loop.)

==============================================================================

This program estimates the cost of apartments on each floor of a building,
considering a compound increase in base price, amenity charges, and taxes.

Features:
- Prompts user for:
  - Number of stories
  - Base price of first-floor apartments
- Calculates for each floor:
  - Base price (2% increase per floor)
  - Amenity charges (5% of base price)
  - Taxes (20% of base price + amenities)
  - Total price (sum of above)
- Outputs a table with all calculated values per floor.

Usage:
1. Run the program.
2. Enter the required inputs when prompted.
3. View the detailed price breakdown for each floor.

Key Formulas:
- Base price for floor `n`: `basePriceFirstFloor * pow(1.02, n - 1)`
- Amenities: `basePrice * 0.05`
- Taxes: `(basePrice + amenities) * 0.20`
- Total price: `basePrice + amenities + taxes`

The reason why pow is used is because of the compound increase in base price.
In other words, each floor's base price is 2% higher than the previous floor's base price.
For this reason, the library cmath is included to use the pow function.