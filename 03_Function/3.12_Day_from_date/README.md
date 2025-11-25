Write a program that inputs a date (e.g., July 4, 2008) and outputs the day of
the week that corresponds to that date. The following algorithm is from
[Wikipedia: Calculating the day of the week](http://en.wikipedia.org/wiki/Calculating_the_day_of_the_week). 

The implementation will require several functions:
bool isLeapYear(int year);
This function should return true if year is a leap year and false if it is not. Here
is pseudocode to determine a leap year:
leap_year = ((year divisible by 400) or (year divisible by 4 and year not divisible
by 100))
int getCenturyValue(int year);
This function should take the first two digits of the year (i.e., the century), divide
by 4, and save the remainder. Subtract the remainder from 3 and return this
value multiplied by 2. For example, the year 2008 becomes (20/4) = 5 remainder 0. 
Then 3 - 0 = 3. Return 3 * 2 = 6.
int getYearValue(int year);
This function computes a value based on the years since the beginning of the
century. First, extract the last two digits of the year. For example, 08 is extracted
for 2008. Next, factor in leap years. Divide the value from the previous step by 4
and discard the remainder. Add the two results together and return this value. For
example, from 2008 we extract 08. Then (8/4) = 2 remainder 0. Return 2 + 8 = 10.
int getMonthValue(int month, int year);
This function should return a value based on the following table and will require
invoking the isLeapYear function:
Here is the information in a Markdown table:

| Month     | Return Value (Normal Year) | Return Value (Leap Year) |
|-----------|---------------------------|--------------------------|
| January   | 0                         | 6                        |
| February  | 3                         | 2                        |
| March     | 3                         | 3                        |
| April     | 6                         | 6                        |
| May       | 1                         | 1                        |
| June      | 4                         | 4                        |
| July      | 6                         | 6                        |
| August    | 2                         | 2                        |
| September | 5                         | 5                        |
| October   | 0                         | 0                        |
| November  | 3                         | 3                        |
| December  | 5                         | 5                        |

Finally, to compute the day of the week, compute the sum of the date’s day plus
the values returned by getMonthValue, getYearValue, and getCenturyValue.
Divide the sum by 7 and compute the remainder. A remainder of 0 corresponds to
Sunday, 1 corresponds to Monday, etc.—up to 6—which corresponds to Saturday.
For example, the date July 4, 2008 should be computed as (day of month) +
(getMonthValue) + (getYearValue) + (getCenturyValue) = 4 + 6 + 10 + 6 = 26.
26/7 = 3 remainder 5. The fifth day of the week corresponds to Friday.
Your program should allow the user to enter any date and output the corresponding
day of the week in English.

---

Two versions, depending on the use of map or switch for month value lookup.
---

## Map-Based vs Switch-Based Implementation

### Map-Based Version (`12_Day_from_date_map.cpp`)

- **Month Value Lookup:** Uses a `std::map<string, int>` to associate month names (in uppercase) with 
  their corresponding values. Handles leap years by appending `"_LEAP"` to `"JANUARY"` and `"FEBRUARY"`.
- **Input:** Accepts month names as strings directly from user input.
- **Readability & Maintainability:** Easy to read and extend. Adding or modifying month values is straightforward.
- **Performance:** Slightly slower due to string manipulation and map lookup, but negligible for this use case.
- **Error Handling:** Returns `-1` if the month is not found in the map.

### Switch-Based Version (`12_Day_from_date_switch.cpp`)

- **Month Value Lookup:** Uses a `switch` statement on an integer month value (1-12) to return the corresponding value. 
  Leap years are handled with conditional logic inside the switch.
- **Input:** Requires converting the month name string to an integer (1-12) using a helper function.
- **Readability & Maintainability:** More verbose and less flexible. Adding or changing months requires editing 
  the switch statement.
- **Performance:** Slightly faster due to direct integer comparison.
- **Error Handling:** Returns `-1` for invalid months after conversion.

### Summary Table

| Feature         | Map-Based Version                | Switch-Based Version             |
|-----------------|----------------------------------|----------------------------------|
| Input Type      | String (month name)              | Integer (converted from string)  |
| Month Lookup    | Map (`std::map<string, int>`)    | Switch statement                 |
| Readability     | High                             | Medium                           |
| Maintainability | High                             | Low                              |
| Performance     | Medium                           | High                             |
| Scalability     | High                             | Low                              |
| Error Handling  | Map lookup, returns `-1`         | Switch default, returns `-1`     |


---
### Other Functions Explained

#### `bool isLeapYear(int year)`
Checks if a given year is a leap year using the standard rules:
- Returns `true` if the year is divisible by 400, or divisible by 4 but not by 100.
- Returns `false` otherwise.

#### `int getCenturyValue(int year)`
Calculates a value based on the century part of the year:
- Extracts the first two digits (century).
- Divides by 4 and gets the remainder.
- Subtracts the remainder from 3, multiplies by 2, and returns the result.

#### `int getYearValue(int year)`
Calculates a value based on the last two digits of the year:
- Extracts the last two digits.
- Divides by 4 and discards the remainder.
- Adds the result to the last two digits and returns the sum.

#### `int getMonthValue(...)`
Explained above, with both map-based and switch-based solutions.

#### Day of the Week Calculation
- Sums the day of the month, month value, year value, and century value.
- Divides the sum by 7 and uses the remainder to determine the day of the week (0 = Sunday, 1 = Monday, ..., 6 = Saturday).

---