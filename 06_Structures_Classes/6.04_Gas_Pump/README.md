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

# Gas Pump 

## High-level flow

- The program models a simple gas pump via the `GasPump` class. Key members:
  - `double getAmount() const` — returns the dispensed fuel volume (liters).
  - `double getCharges() const` — returns the amount charged (currency).
  - `void setCharges(double userPrice)` — interactive routine that simulates dispensing until the user's chosen spending limit is reached or the user cancels.
  - `void setAmount()` (private) — computes `amount` from `charges / PRICE_LITER` after dispensing finishes.
  - `double showUnitCharge()` — returns the `PRICE_LITER` constant.
  - `void setFuel(double& userPrice)` — reads combination of banknote values from the user (5, 10, 20, 50, 100) and sums them into `userPrice`.

- Typical run:
  1. `setFuel` prompts the user to enter sums (multiples of 5). The user can enter multiple values and finishes with `-1`.
  2. `driver1.setCharges(userPrice)` starts an interactive refill loop. Each press of the Enter key increments `charges` by `STEP_REFILL` (0.1) until `charges` reaches `userPrice` (or user cancels with ESC).
  3. During dispensing the program updates the console in-place using a carriage return (`'\r'`) and `std::flush` so the `Fuel:` label overwrites the same line.
  4. After the loop completes, `setAmount()` sets the fuel `amount` as `charges / PRICE_LITER` and the program prints final values.

### Key implementation details and rationale

- In-place console updates use `std::cout << '\r'` and `<< std::flush` so output appears immediately without producing newlines. The code also uses `std::setw(20)` to clear leftover characters from previous, longer labels.

- `STEP_REFILL` represents the monetary increment applied each Enter press. 

- Floating-point comparisons use a small epsilon (`1e-9`) to avoid precision issues when comparing `charges` and `userPrice`.

- Formatting (`std::fixed`, `std::setprecision`) is applied at output so currency and liters present consistent decimal places.

### conio.h, `_kbhit` and `_getch`

- `conio.h` is a non-standard header provided by Microsoft Visual C++ and some other compilers on Windows. It is not part of the C++ standard library and is not portable to POSIX systems.

- `_kbhit()`
  - Prototype: `int _kbhit(void);`
  - Returns a non-zero value if a keyboard key has been pressed and is available in the input buffer; otherwise returns zero.
  - It is non-blocking — it does not wait for user input.
  - In the context of the gas pump code, it is used to check if the user has pressed a key (like ESC) to cancel the refill operation.
```cpp
void GasPump::setCharges(const double userPrice)
{
	// some code
	if (_kbhit())
	
}
```

- `_getch()`
  - Prototype: `int _getch(void);`
  - Reads a single character from the console without echoing it and without waiting for an Enter key. It blocks if no key is available (so typically you call it after `_kbhit()` returns non-zero).
  - Returns the character code (e.g. `13` for Enter, `27` for ESC).

- Typical usage pattern in the code:
  - Poll `_kbhit()` inside a loop; when it indicates a key press, call `_getch()` to obtain the character. This enables responsive, single-key interaction without line buffering.

- Caveats and alternatives:
  - Because `conio.h` is Windows-specific, code using `_kbhit/_getch` will not compile on POSIX systems. For cross-platform projects, we can use other libraries, namely `ncurses` (Linux/Unix) or use platform abstraction wrappers.
  - If portability is not required, and the project targets Visual Studio on Windows, `conio.h` is acceptable.
  - We ought to use `std::flush` when printing with a carriage return (`'\r'`) and no newline to ensure the console updates immediately.

### UX and correctness suggestions

- Cap incremental updates so `charges` never overshoots `userPrice`
```cpp
charges = std::min(charges + STEP_REFILL, userPrice);
```
- For portability, one could replace `conio.h` usage with a platform abstraction layer.

----



### Old implementation
The old implementation of `setAmount` tries to read the input from the 
user by reading a line of text.
However, this approach creates a new line as soon as the user press
'Enter' from keyboard. 
To avoid the issue, the library `conio.h` is used to read a single character 
from keyboard without creating a new line.
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