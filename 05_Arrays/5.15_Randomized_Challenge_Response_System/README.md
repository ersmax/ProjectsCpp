Traditional password entry schemes are susceptible to “shoulder surfing” in which
an attacker watches an unsuspecting user enter their password or PIN number and
uses it later to gain access to the account. One way to combat this problem is with
a randomized challenge-response system. In these systems, the user enters different
information every time based on a secret in response to a randomly generated challenge.
Consider the following scheme in which the password consists of a five-digit
PIN number (00000 to 99999). Each digit is assigned a random number that is
1, 2, or 3. The user enters the random numbers that correspond to their PIN instead
of their actual PIN numbers.
For example, consider an actual PIN number of 12345. To authenticate, the user
would be presented with a screen such as

| PIN | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
|-----|---|---|---|---|---|---|---|---|---|---|
| NUM | 3 | 2 | 3 | 1 | 1 | 3 | 2 | 2 | 1 | 3 |

The user would enter 23113 instead of 12345. This does not divulge the password
even if an attacker intercepts the entry because 23113 could correspond to other
PIN numbers, such as 69440 or 70439. The next time the user logs in, a different
sequence of random numbers would be generated, such as

| PIN | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
|-----|---|---|---|---|---|---|---|---|---|---|
| NUM | 1 | 1 | 2 | 3 | 1 | 2 | 2 | 3 | 3 | 3 |

Your program should simulate the authentication process. Store an actual PIN
number in your program. The program should use an array to assign random
numbers to the digits from 0 to 9. Output the random digits to the screen, input
the response from the user, and output whether or not the user’s response correctly
matches the PIN number.

---


# Overview
- The program simulates a randomized challenge/response PIN authentication.
- An internal (stored) PIN is kept as an integer constant `GIVEN_PIN`.
- A mapping array `sequence[0..9]` assigns each digit (0..9) a random number in `1..NUMBERS`.
- The user types the response: the sequence of mapped numbers corresponding to each digit of their PIN.
- The program verifies the response by mapping each digit of `GIVEN_PIN` through `sequence` and comparing with the user input.

## Constants
- `NUMBERS` — number of possible mapped values (1..NUMBERS).
- `DIGITS` — number of digit positions (10).
- `PIN` — length of stored PIN (5).
- `GIVEN_PIN` — stored PIN as an integer (leading zeros are handled by digit extraction).

## Functions
- `createSequence(int sequence[], int size)`
  - Builds the initial mapping for `0..9`. In the current implementation it fills a repeating pattern (1..NUMBERS) then the mapping is randomized by `shuffleSequence`.
  - Alternative: use `std::uniform_int_distribution<int>(1, NUMBERS)` per entry to produce independent random assignments.
- `shuffleSequence(int sequence[], int size)`
  - Uses Fisher-Yates shuffle with `std::mt19937` to randomize the `sequence` array.
- `showSystem(const int sequence[], int size)`
  - Prints the two rows: PIN indices `0..9` and corresponding `NUM` values from `sequence`.
- `enterPin(int pin[], int nDigits)`
  - Reads the user response as a `std::string`.
  - Validates length equals `nDigits`.
  - Validates each character is in `'1' .. '0' + NUMBERS'`.
  - Converts each character to an integer by subtracting `'0'` and stores into the `pin[]` array.
  - Handles bad input and clears `std::cin` appropriately.
- `checkPin(const int pin[], int nDigitsPin, const int sequence[], int nDigits)`
  - Converts `GIVEN_PIN` into an array `givenPin[PIN]` by repeated `% DIGITS` and `/= DIGITS` (fills leading positions with `0` when `GIVEN_PIN` has leading zeros).
  - For each PIN position `i`, obtains the actual digit `d = givenPin[i]` and checks `sequence[d] == pin[i]`.
  - Returns `true` if all positions match, otherwise `false`.

## Transform a number into an array
There are two possible strategies to go about transforming a number into an array.

1. The first strategy is to extract each digit of the number and place it into an array. 
   This is done by repeatedly taking the modulus of 10 of the number to get the last 
   digit, and then dividing the number by 10 to remove the last digit. 
   This is done in the function `checkPin` in the code below.
```cpp
bool checkPin(const int pin[], const int nDigitsPin,
const int sequence[], const int nDigits) {

    int givenPin[PIN];
    int temp = GIVEN_PIN;
    for (int idx = PIN - 1; idx >= 0; --idx) {
        givenPin[idx] = temp % DIGITS;
        temp /= DIGITS;
    }
    // other code...
```
2. The second strategy is to convert the number into a string, and then  
   extract each character of the string and convert it back to an integer.
   This is done in the function `enterPin` in the code below.

```cpp
void enterPin(int pin[], const int nDigits) {
    std::string number;
    std::cout << "Enter the PIN sequence:\n";
    while (true) {
        
        // other code...
        
        // add to array
        for (int idx = 0; idx < nDigits; ++idx)
            pin[idx] = number[idx] - '0';
        break;
    }
}
```


## Alternative implementation
Another way to check the correctness is to build an internal
array with all the idx of the `sequence` associated with the corresponding 
randomized number.
However, this strategy requires more space, since we create 
an internal array for each digit of the PIN.

```cpp
bool checkPin(const int pin[], const int nDigitsPin,
              const int sequence[], const int nDigits) {

    int givenPin[PIN];
    int temp = GIVEN_PIN;
    for (int idx = PIN - 1; idx >= 0; --idx) {
        givenPin[idx] = temp % 10;
        temp /= 10;
    }
    
    // build an inner array to check the randomized numbers 
    for (int digit = 0; digit < nDigitsPin; ++digit) {
        int digits[PIN];
        int sizeDigits = 0;
        for (int idx = 0; idx < nDigits; ++idx) {
            if (sequence[idx] == pin[digit])
                digits[sizeDigits++] = idx;
        }
        // now check if randomized number is in sequence
        bool inSequence = false;
        for (int d = 0; d < sizeDigits; ++d)
            if (digits[d] == givenPin[digit]) {
                inSequence = true;
                break;
            }
        if (!inSequence) return false;
    }
    return true;
}
```
