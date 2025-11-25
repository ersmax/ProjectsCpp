Write a function that computes the average and standard deviation of four scores.
The standard deviation is defined to be the square root of the average of the four
values: (si − a )^2, where a is the average of the four scores s1, s2, s3, and s4. The function
will have six parameters and will call two other functions. Embed the function
in a program that allows you to test the function again and again until you tell the
program you are finished.

================================================================================================

Functions:

- `double averageScore(double score1, double score2, double score3, double score4);`
  Returns the average of four scores.

- `double standardDeviation(double score1, double score2, double score3, double score4);`
  Returns the standard deviation, defined as the square root of the average of the
  squared deviations from the mean.

- `void showStatistics(double averageScores, double sdScores);`
  Displays the average and standard deviation, formatted to two decimal places.

Main Loop:
Prompts the user for four scores, computes statistics, displays results,
and asks if the user wants to repeat.

Preconditions:
All input scores must be valid numbers.

Postconditions:
Displays the computed average and standard deviation for each set of scores entered.
==================================================================================================