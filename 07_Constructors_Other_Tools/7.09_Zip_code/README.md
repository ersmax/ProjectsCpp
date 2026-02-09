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

## Implementation Logic

### Class Design
The `Zip` class stores the zip code internally as an **integer** and provides conversion methods 
to/from bar code strings.

**Key Components:**
- **Storage**: `int zip` - stores zip code as 5-digit number (0-99999)
- **Constructors**: Accept either bar code string or integer
- **Getters**: Return zip code as integer or bar code string
- **Validation**: Ensures data integrity for both formats

### Decoding Algorithm (Bar Code → Integer)

**Function**: `conversion(const std::string& myString)`

1. **Strip Frame Bars**: Remove leading and trailing '1' characters, leaving 25 digits
2. **Process Each Group**: Iterate through 5 groups of 5 digits each
3. **Apply POSTNET Values**: For each group, multiply each bar (0 or 1) by its position value:
   - Position 0: value = 7
   - Position 1: value = 4
   - Position 2: value = 2
   - Position 3: value = 1
   - Position 4: value = 0
4. **Sum Products**: Add all products to get the digit value
5. **Handle Special Case**: If sum equals 11, the digit is 0 (since 7+4=11, the only way to represent 0)
6. **Build Integer**: Multiply previous result by 10 and add new digit

**Example**: `10100` → (1×7)+(0×4)+(1×2)+(0×1)+(0×0) = 9

### Encoding Algorithm (Integer → Bar Code)

**Function**: `conversion(int zipCode)`

1. **Extract Digits**: Use modulo and division to extract each digit right-to-left, store left-to-right in array
2. **For Each Digit**:
   - Convert 0 to target sum of 11, others keep their value
   - Find two positions in POSTNET array [7,4,2,1,0] that sum to target
   - Set those two positions to '1', rest remain '0'
   - This creates a 5-character bar code group
3. **Concatenate**: Combine all groups with leading and trailing '1' frame bars

**Example**: Digit 9 → target=9 → find 7+2=9 → positions 0,2 → bar code `10100`

### Validation Logic

**Bar Code String Validation** (`isValid(const std::string&)`):
- Length must be exactly 27 characters
- First and last characters must be '1' (frame bars)
- All characters must be '0' or '1'
- Each of the 5 middle groups must have exactly two '1's

**Integer Validation** (`isValid(const int)`):
- Must be between 0 and 99999 (valid 5-digit zip code range)

### Error Handling
- Invalid inputs throw `std::invalid_argument` exception
- Validation occurs in constructors, preventing creation of invalid objects
- Try-catch block in main demonstrates proper exception handling

---
