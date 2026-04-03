Define a class named Payment that contains a member variable of type float that
stores the amount of the payment and appropriate accessor and mutator functions.
Also create a member function named paymentDetails that outputs an English
sentence describing the amount of the payment.
Next, define a class named CashPayment that is derived from Payment. This class
should redefine the paymentDetails function to indicate that the payment is in
cash. Include appropriate constructor(s).
Define a class named CreditCardPayment that is derived from Payment. This
class should contain member variables for the name on the card, expiration date,
and credit card number. Include appropriate constructor(s). Finally, redefine the
paymentDetails function to include all credit card information in the printout.
Create a main function that creates at least two CashPayment and two
CreditCardPayment
objects with different values and calls to paymentDetails
for each.
---

## Implementation overview

This project implements the specification above using a small class hierarchy:

- `Payment` (namespace `myNamespacePayment`) stores the payment amount as a `float` and provides accessors, a mutator with validation (rejects negative amounts), and stream operators `>>`/`<<` for console input/output. Its `paymentDetails(std::ostream&)` function signals that details for a generic, undifferentiated payment are not supported and is intended to be redefined in derived classes.
- `CashPayment` derives from `Payment` and represents payments made in cash. It reuses all validation from `Payment`, adds constructors to initialize the amount, and defines `paymentDetails(std::ostream&)` to print that the payment is in cash. The `operator<<` first prints the base `Payment` information and then the cash-specific details.
- `ExpirationDate` (namespace `myNamespaceDate`) encapsulates a month/year pair for credit card expiration. It validates that the date is within a reasonable range, provides setters/getters, and overloads `>>`/`<<` to read and print expiration dates.
- `CreditCardPayment` derives from `Payment` and adds the card holder name, card number, and an `ExpirationDate`. It validates that the card number contains only digits and that the card name is not empty. Its `paymentDetails(std::ostream&) const` prints all credit card–specific details, including the formatted expiration date. Stream operators `>>`/`<<` are provided to interactively read and display full credit card payments.

The `main` function (in `14_06_Application.cpp`) demonstrates the classes by:

- Creating a `CashPayment` with a fixed amount and printing it.
- Reading another `CashPayment` from standard input and printing it.
- Creating a `CreditCardPayment` with a fixed amount, card data, and expiration date, then printing it.
- Copying a `CreditCardPayment` and printing the copy.
- Reading another `CreditCardPayment` interactively (amount, card name, card number, expiration date) and printing the result.

All user interaction is done through `std::cin`/`std::cout`, and validation helpers from `14_06_Validation.h` are used to safely read numeric and string input where needed.

