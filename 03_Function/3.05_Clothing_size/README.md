Write a program that asks for the user’s height, weight, and age, and then computes
clothing sizes according to the following formulas.
• Hat size = weight in pounds divided by height in inches and all that multiplied
by 2.9.
• Jacket size (chest in inches) = height times weight divided by 288 and then
adjusted by adding one-eighth of an inch for each 10 years over age 30. (Note
that the adjustment only takes place after a full 10 years. So, there is no adjustment
for ages 30 through 39, but one-eighth of an inch is added for age 40.)
• Waist in inches = weight divided by 5.7 and then adjusted by adding one-tenth
of an inch for each 2 years over age 28. (Note that the adjustment only takes
place after a full 2 years. So, there is no adjustment for age 29, but one-tenth
of an inch is added for age 30.)
Use functions for each calculation. Your program should allow the user to repeat
this calculation as often as he or she wishes.

===========================================================================

Code Choices and Optimizations in Clothing Size Program

1. Avoiding Code Repetition with `getValidatedInput`
   The new function `getValidatedInput` replaces repeated input-validation-retry logic
   for height, weight, and age.
   - It takes a prompt and valid range, loops until valid input or user exit, and returns the value.
   - This makes the code shorter, easier to maintain, and less error-prone.

2. Role of Old Boolean Functions:
   The previous functions (`errorHandlingHeight`, `errorHandlingWeight`, `errorHandlingAge`)
   only checked if values were in range.
   - They were called separately for each input, leading to repeated code blocks
     for prompting, validating, and retrying.

3. Passing Prompt by Reference:
   The prompt string in `getValidatedInput` is passed as `const string&`
   to avoid copying and to ensure the function does not modify it.
   - This is efficient and makes the function flexible for different prompts.

4. Reusability and Readability:
   - The new approach allows the same function to be used for any validated input,
     improving reusability.
   - The main logic is clearer, focusing on what is being input rather than how it is validated.

5. Hat Size Calculation (`hatSize`):
   - Calculates hat size using the formula: `(weight / height) * HAT_CONSTANT`.
   - Converts height from feet and inches to total inches for accuracy.

6. Jacket Size Calculation (`jacketSize`):
   - Uses the formula: `(height * weight) / JACKET_CONSTANT`.
   - Adds an age-based adjustment: for every decade over 30, increases size by `JACKET_OFFSET`.

7. Waist Size Calculation (`waistSize`):
   - Uses the formula: `weight / WAIST_CONSTANT`.
   - Adds an age-based adjustment: for every 2 years over 28, increases size by `WAIST_OFFSET`.

Summary:
The refactored code is modular, maintainable, and easy to extend.
Input validation is centralized, and calculations are clearly separated into functions,
improving readability and reusability.

=============================================================================