
In the game of craps, a “Pass Line” bet proceeds as follows. The first roll of the two,
six-sided dice in a craps round is called the “come out roll.” The bet immediately
wins when the come out roll is 7 or 11, and loses when the come out roll is 2, 3,
or 12. If 4, 5, 6, 8, 9, or 10 is rolled on the come out roll, that number becomes
“the point.” The player keeps rolling the dice until either 7 or the point is rolled.
If the point is rolled first, then the player wins the bet. If the player rolls a 7 first,
then the player loses.
Write a program that plays craps using those rules so that it simulates a game
without human input. Instead of asking for a wager, the program should calculate
whether the player would win or lose. Create a function that simulates rolling the
two dice and returns the sum. Add a loop so that the program plays 10,000 games.
Add counters that count how many times the player wins, and how many times the
player loses. At the end of the 10,000 games, compute the probability of winning,
as Wins / (Wins + Losses), and output this value. Over the long run, who is going
to win more games of craps, you or the house?

---

Program Overview:
This program simulates 10,000 games of craps using the standard "Pass Line" rules.
It counts the number of wins and losses, calculates the probability of winning,
and displays the results.

Function Descriptions:
- `int sum_two_dices();`
  Simulates rolling two six-sided dice and returns their sum (random number between 2 and 12).

- `bool outcome();`
  Simulates a single game of craps:
  - Rolls the dice for the "come out roll".
  - Wins immediately if the roll is 7 or 11.
  - Loses immediately if the roll is 2, 3, or 12.
  - Otherwise, sets the rolled value as the "point" and continues rolling:
    - Wins if the point is rolled again before a 7.
    - Loses if a 7 is rolled before the point.

- `int main();`
  - Seeds the random number generator.
  - Plays 10,000 games, counting wins and losses.
  - Calculates and prints the probability of winning as a percentage.
  - Displays the number of wins and losses.
  - Indicates whether the player or the house is more likely to win.

Key Variables:
- `games`: Number of games to simulate (10,000).
- `wins`, `losses`: Counters for wins and losses.
- `result`: Probability of winning, as a percentage.

Output:
- The likelihood of winning (percentage).
- Number of wins and losses.
- A message indicating whether the house or the player is more likely to win.