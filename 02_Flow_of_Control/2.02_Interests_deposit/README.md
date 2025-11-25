In order to manage their funds efficiently, a person deposits an amount of money
in a bank account. They withdraw a fixed portion on the fifth day of every month
for their household expenses. The bank credits the interest accumulated on their
balance on the last day of every month. Write a program that inputs the initial
deposit made, the interest rate provided by bank, and the fixed amount withdrawn
every month. Calculate the number of months the amount (including the credited
interest) can be utilized. (Hint: Use a loop)
Note: Check for boundary conditions – If the interest earned every month is greater
than the fixed withdrawal amount, the program should print that message and
return.

===============================================================================

This program calculates how many months a bank deposit can last,
given a fixed monthly withdrawal and interest credited at the end of each month.

Key Features:
- Inputs:
  - Initial deposit amount
  - Monthly interest rate
  - Fixed monthly withdrawal
- Checks a boundary condition:
  - If the monthly interest earned is greater than or equal to the withdrawal,
    the deposit will never run out (infinite loop prevention).
  - In this case, the program prints a message and returns immediately.
- Otherwise, simulates monthly withdrawals and interest accrual
  until the balance is insufficient.

Importance of the Return Statement:
- The early `return` prevents an infinite loop
  when the interest earned each month is enough to cover or exceed the withdrawal.
- Without this check, the loop would never terminate, as the balance
  would never decrease below the withdrawal amount.
