A city cab service provider charges customers based on distance and time. The
service charges $2 per kilometer for the first two kilometers. After the first two kilometers,
the service charges $0.50 per kilometer for the next six kilometers. After six
kilometers, the customer is charged $1 per kilometer. At the end of the ride, a fee
of $0.2 per minute is charged based on the total travel duration. Write a program
that reads the distance traveled in kilometers and the time taken in minutes for a
cab ride and computes the fare based on the service’s charges.

====================================================================

The program calculates cab fare based on distance and time,
using clear conditional logic and concise expressions.

- Fare Calculation Logic:
  The fare is split into three brackets:
  - $2 per km for the first 2 km.
  - $0.50 per km for the next 6 km (from 2 to 8 km).
  - $1 per km for any distance above 8 km.
  - An additional $0.20 per minute for the ride duration.

- Use of `min` Function:
  The `min` function ensures that the correct distance bracket is applied,
  preventing overcharging for the first 2 km and the next 6 km.

- Ternary Operator:
  The ternary operator `(distance_km > 0 ? min(distance_km, 2.0f) : 0)`
  is used for concise conditional assignment,
  ensuring the base fare is only applied if the distance is positive.

- Conditional Checks:
  Nested `if` statements are used to apply the correct fare for each distance bracket,
  making the logic readable and maintainable.

- Type Safety:
  All calculations use `float` to handle fractional distances and times accurately.

- User Input Handling:
  The program prompts for distance and time, ensuring interactive usage.

Summary:
The use of the ternary operator and `min` function makes the code concise
and avoids unnecessary branching.
This approach improves readability and maintainability while ensuring accurate fare calculation.