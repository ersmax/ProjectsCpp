Write a program that outputs all 99 stanzas of the “Ninety-Nine Bottles of Beer
on the Wall” song. Your program should print the number of bottles in English,
not as a number:
Ninety-nine bottles of beer on the wall,
Ninety-nine bottles of beer,
Take one down, pass it around,
Ninety-eight bottles of beer on the wall.
…
One bottle of beer on the wall,
One bottle of beer,
Take one down, pass it around,
Zero bottles of beer on the wall.
Your program should not use ninety-nine different output statements!

===============================================

numberToWords(int number):
- Converts an integer between 0 and 99 to its English word representation.
- Uses two arrays: one for numbers below 20, and one for tens (20, 30, ... 90).
- For numbers below 20, returns the corresponding word.
- For numbers 20 and above, combines the tens word with the units word (if not zero),
  separated by a hyphen.

main():
- Loops from 99 down to 1.
- For each number, prints a stanza of the "Ninety-Nine Bottles of Beer" song.
- Uses `numberToWords` to print the bottle count in words.
- Handles singular/plural form for "bottle"/"bottles".
- After each stanza, decrements the bottle count and prints the next count in words.

================================================