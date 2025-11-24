The video game machines at your local arcade output coupons depending on how
well you play the game. You can redeem 10 coupons for a candy bar or 3 coupons
for a gumball. You prefer candy bars to gumballs. Write a program that inputs the
number of coupons you win and outputs how many candy bars and gumballs you
can get if you spend all of your coupons on candy bars first and any remaining
coupons on gumballs.

===================================================================
Documentation and Explanation:

This program calculates the maximum number of candy bars and gumballs a player can redeem
with their arcade coupons, prioritizing candy bars over gumballs.

Choices Explained:
- Input/Output: Uses `cin` and `cout` for user interaction,
  which is standard for simple console applications.
- Variable Declaration: Declares all variables at the start for clarity.
- Division and Modulo: Uses integer division (`/`) to determine
  how many candy bars can be redeemed (since each costs 10 coupons).
  The modulo operator (`%`) finds the remaining coupons after redeeming candy bars.
- Second Redemption: Uses the remaining coupons to calculate how many gumballs
  can be redeemed (each costs 3 coupons).

Preference Logic:
The process ensures all possible candy bars are redeemed first,
reflecting the stated preference for candy bars over gumballs.

No Loops or Conditionals:
The logic is straightforward and does not require loops or `if` statements,
as the redemption is based on simple arithmetic.

Process:
1. Prompt the user for the number of coupons.
2. Calculate the number of candy bars (`total_coupons / 10`).
3. Calculate remaining coupons (`total_coupons % 10`).
4. Calculate the number of gumballs (`remaining_coupons / 3`).
5. Output the results.

===================================================================