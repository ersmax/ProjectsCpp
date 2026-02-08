Prior to 2009 the bar code on an envelope used by the U.S. Postal Service represented a five (or more) digit zip code using a format called POSTNET. The bar
code consists of long and short bars as shown here:

<p align="center">
  <img src="./Figures/Bar_code.png" alt="Bar code" width="48%" />
</p>

For this program, we will represent the bar code as a string of digits. The digit 1
represents a long bar, and the digit 0 represents a short bar. Therefore, the bar code
shown would be represented in our program as follows:
110100101000101011000010011

The first and last digits of the bar code are always 1. Removing these leave 25 digits.
If these 25 digits are split into groups of five digits each then we have the following:
10100 10100 01010 11000 01001

Next, consider each group of five digits. There always will be exactly two 1’s in
each group of digits. Each digit stands for a number. From left to right, the digits
encode the values 7, 4, 2, 1, and 0. Multiply the corresponding value with the digit
and compute the sum to get the final encoded digit for the zip code. The following
table shows the encoding for 10100.

| Bar Code Digits | 1 | 0 | 1 | 0 | 0 |
|-----------------|---|---|---|---|---|
| Value           | 7 | 4 | 2 | 1 | 0 |
| Product of Digit * Value | 7 | 0 | 2 | 0 | 0 |

Zip Code Digit = 7 + 0 + 2 + 0 + 0 = 9

Repeat this for each group of five digits and concatenate to get the complete zip
code. There is one special value. If the sum of a group of five digits is 11, then this
represents the digit 0 (this is necessary because with two digits per group it is not
possible to represent zero). The zip code for the sample bar code decodes to 99504.
While the POSTNET scheme may seem unnecessarily complex, its design allows
machines to detect whether errors have been made in scanning the zip code.

Write a zip code class that encodes and decodes five-digit bar codes used by the
U.S. Postal Service on envelopes. The class should have two constructors. The first
constructor should input the zip code as an integer, and the second constructor
should input the zip code as a bar code string consisting of 0’s and 1’s as described
above. Although you have two ways to input the zip code, internally, the class
should only store the zip code using one format. (You may choose to store it as a
bar code string or as a zip code number.) The class also should have at least two
public member functions: one to return the zip code as an integer and the other
to return the zip code in bar code format as a string. All helper functions should be
declared private. Embed your class definition in a suitable test program.

---