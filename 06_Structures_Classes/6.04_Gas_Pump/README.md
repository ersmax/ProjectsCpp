Write the definition for a class named GasPump to be used to model a pump at an
automobile service station. Before you go further with this programming exercise,
write down the behavior you expect from a gas pump from the point of view of the
purchaser.
The following are listed things a gas pump might be expected to do. If your list
differs, and you think your list is as good or better than these, then consult your
instructor. You and your instructor should jointly decide what behavior you are to
implement. Then implement and test the agreed upon design for a gas pump class.
a. A display of the amount dispensed
b. A display of the amount charged for the amount dispensed
c. A display of the cost per gallon, liter, or other unit of volume that is used where
you reside
d. Before use, the gas pump must reset the amount dispensed and amount charged
to zero.
e. Once started, a gas pump continues to dispense fuel, keep track of the amount
dispensed, and compute the charge for the amount dispensed until stopped.
f. A stop dispensing control of some kind is needed.
Implement the behavior of the gas pump as declarations of member functions of
the gas pump class, then write implementations of these member functions. You
will have to decide if there is data the gas pump has to keep track of that the user
of the pump should not have access to. If so, make these private member variables.
Additional functions that I have thought:
1. Choose the fuel pump
2. Refill for a given amount
3. Select petrol/diesel
4. Select cash/card

----


### Old implementation
The old implementation of `setAmount` tries to read the input from the 
user by reading a line of text.
However, this approach creates a new line as soon as the user press
'Enter' from keyboard. 
To avoid the issue, a specific library `conio.h` is used.
Reference: 
[Stackoverflow - Creating a progress update by replacing output in the R console from C/C++](https://stackoverflow.com/questions/47623478/creating-a-progress-update-by-replacing-output-in-the-r-console-from-c-c)

```cpp
void GasPump::setAmount(const double userPrice)
{
	amount = 0.0;
	std::string line;
	std::cout << "Press enter to refill (or 'exit'):\n";
	while (amount <= userPrice)
	{
		std::getline(std::cin, line);
		if (line.empty())
		{
			amount += STEP_REFILL;
			std::cout << "\rFuel: " << amount << "        " << std::flush;

		}
		if (line == "exit")
			break;
	}
}
```