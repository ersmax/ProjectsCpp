(You should do Programming Projects 4.6 and 4.9 before doing this programming
project.) Write a program that combines the functions of Programming
Projects 4.6 and 4.9. The program asks the user if he or she wants to convert
lengths or weights. If the user chooses lengths, then the program asks the user if
he or she wants to convert from feet and inches to meters and centimeters or from
meters and centimeters to feet and inches. If the user chooses weights, a similar
question about pounds, ounces, kilograms, and grams is asked. The program then
performs the desired conversion. Have the user respond by typing the integer 1 for
one type of conversion and 2 for the other. The program reads the user’s answer
and then executes an if-else statement. Each branch of the if-else statement
will be a function call. The two functions called in the if-else statement will
have function definitions that are very similar to the programs for Programming
Projects 4.6 and 4.9. Thus, these functions will be fairly complicated function
definitions that call other functions; however, they will be very easy to write by
adapting the programs you wrote for Programming Projects 4.6 and 4.9. Notice
that your program will have if-else statements embedded inside of if-else
statements, but only in an indirect way. The outer if-else statement will include
two function calls, as its two branches. These two function calls will each
in turn include an if-else statement, but you need not think about that. They
are just function calls and the details are in a black box that you create when you
define these functions. If you try to create a four-way branch, you are probably
on the wrong track. You should only need to think about two-way branches (even
though the entire program does ultimately branch into four cases). Include a loop
that lets the user repeat this computation for new input values until the user says
he or she wants to end the program.

---

# Length & Weight Conversion

This program combines the length conversion (feet/inches <-> meters/centimeters) and
weight conversion (pounds/ounces <-> kilograms/grams). It provides a top-level menu
to choose conversion type and a submenu to choose direction. Input validation,
conversion logic and formatted output are implemented in separate functions.

- Build with your usual C++ toolchain (CLion, g++, MSVC)
```
g++ -std=c++17 -O2 10_Length_Weight_Conversion.cpp -o converter
./converter
```

## Program behavior
### Top menu:
  - 1 — Convert length (feet & inches <-> meters & centimeters)
  - 2 — Convert weight (pounds & ounces <-> kilograms & grams)
  - 0 — Exit program
### Submenus (for each top choice):
  - 1 — Convert from the first unit pair to the second (e.g. feet & inches -> meters & centimeters)
  - 2 — Convert from the second pair to the first
  - 0 — Return to main menu

## Note on submenu\-exit semantics
Two reasonable behaviors exist; the codebase supports the recommended behavior (submenu 0 returns to the main menu):
1. Current: submenu returns 0 in the *submenu field* (e.g. `choice.meterFeet = 0`), and `main` treats that as "return to main menu" (skip conversion, loop again). This is clearer to users and keeps the top-level `lengthWeight` unchanged. 
2. Alternative: submenu can set the *top-level* menu field to 0 to cause the program to exit immediately. To implement that behavior you must change the submenu function signature to take the top-level choice by non-const reference (for example `void makeChoice(int& choiceMenu, int& choiceSubmenu);`) and assign `choiceMenu = 0` when the user selects 0. This is more surprising to users; avoid unless desired.

For alternative 2., see improvements below.

## Function overview
- `void makeChoice(Choice& choice)`  
  Orchestrates menus: calls top-menu, then the appropriate submenu if needed.

- `void makeChoice(int& choiceMenu)`  
  Top-level menu: displays options, validates input, sets `choiceMenu` to 0/1/2.

- `void makeChoice(const int& choiceMenu, int& choiceSubmenu)`  
  Submenu for the chosen category: displays length or weight submenu and sets `choiceSubmenu` to 0/1/2. (If you prefer the "submenu forces program exit" behavior, change signature to `int& choiceMenu` and assign `choiceMenu = 0` when user selects 0.)

- `void getData(FeetInches& f)` / `void getData(MetersCentimeters& m)` / `void getData(PoundsOunces& p)` / `void getData(KilogramsGrams& k)`  
  Read user input for the selected units, perform validation and re-prompt on invalid input.

- `void convertData(const FeetInches&, MetersCentimeters&)` and vice versa; `void convertData(const PoundsOunces&, KilogramsGrams&)` and vice versa  
  Convert units using `constexpr` constants. Rounding is applied where appropriate.

- `void showData(const FeetInches&, const MetersCentimeters&)` and `void showData(const PoundsOunces&, const KilogramsGrams&)`  
  Print the conversion results with simple pluralization and formatting.

## Implementation notes & small fixes
- Submenu handling: prefer setting the submenu field to 0 and letting `main` `continue` the loop rather than overwriting the top-level menu field.
- Assertions: the code uses `assert` to check non\-negative results after conversion.
- Pluralization and rounding: the output rounds grams/ounces for label selection (already handled in `showData`).

## Possible improvements 
- Use `enum class` for main/submenu choices
- Normalizing internal representation (e.g. store all lengths in centimeters or all weights in grams internally) to simplify conversion logic.


## Alternative version: 0 in the sub-menu to exit the program
If the user wants to exit at the sub-menu (choosing betweeen feet & meters conversion or pound & kilo conversion),
one needs to change the signature and definition of the function `void makeChoice(const int& choiceMenu, int& choiceSubmenu)`
to the following:
```cpp
void makeChoice(int& choiceMenu, int& choiceSubmenu);
```
```cpp
void makeChoice(int& choiceMenu, int& choiceSubmenu) {
    while (true) {
        int answer;

        if (choiceMenu == 1)
            cout << "Length menu:\n"
                 << "1. Convert feet & inches to meters and centimeters\n"
                 << "2. Convert meters & centimeters to feet & inches\n";
        if (choiceMenu == 2)
            cout << "Weight menu:\n"
                 << "1. Convert pounds & ounces to kilos and grams\n"
                 << "2. Convert kilo & grams to pounds & ounces\n";

        cout     << "0. Exit sub-menu\n"
                 << "Enter action:\n";

        if (!(cin >> answer)) {
            cout << "Invalid choice.\n\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        // ignore remaining input after 1 or 2
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\n";

        if (answer == 0) {
            choiceMenu = answer;
            break;
        }
        if (answer == 1 || answer == 2) {
            choiceSubmenu = answer;
            break;
        }

        cout << "Invalid result.\n\n";
    }
}
``` 
An additional local variable `int answer` is declared, because the input from the user (`cin >> answer`) 
guides the program whether to exit from execution (`choiceMenu = answer` and later `if (choice.lengthWeight == 0) break;`)
or continue with the execution (`choiceSubmenu = answer`).
Should the user wants to exit from the submenu, the option of returning to the menu from submenu in the main should 
also be removed. That is, the following condition in the main should be removed or commented out:
```
if (choice.meterFeet == 0 ||                    // sub-menu termination
    choice.kiloPound == 0) continue;
```

## Alternative version: no Orchestrator for `makeChoice`
This variant uses no single "orchestrator" wrapper for menu handling. 
Instead `main` calls the top-level menu and the submenu directly, 
using a separate `Choice` object for submenu state. Flow and semantics:

The "no orchestrator" approach keeps submenu state separate, 
avoid changing the top-level `choice` from inside the submenu, 
and uses the label `0` as "Exit" as in the previous alternative.

- Top-level menu
  - `void makeChoice(Choice& choice)` — fills `choice.lengthWeight` (0=exit, 1=length, 2=weight).
- Submenu
  - `void makeChoice(Choice& choice, Choice& subChoice)` — displays the appropriate length/weight submenu 
     and writes the user answer into the *submenu* fields of `subChoice`:
    - `subChoice.meterFeet` for length sub-options (0=exit, 1,2)
    - `subChoice.kiloPound` for weight sub-options (0=exit, 1,2)
- Main loop
  - Calls `makeChoice(choice)` then, if `choice.lengthWeight` selects a category, calls `makeChoice(choice, subChoice)`.
  - After the submenu returns, `main` examines the relevant `subChoice` field:
    - If it is `0` treat it as "Exit".
    - If it is 1 or 2 perform the requested conversion.
  - Reset `subChoice` fields before the next submenu invocation if desired.

### Pros
- Separation of top menu state (`choice`) and submenu state (`subChoice`).
- `main` directly orchestrates control flow (no extra wrapper function), making the flow explicit.

### Cons / pitfalls
- Less function separation and more code obfuscation in main

#### Code for the second version (no orchestrator) 

```cpp
#include <iostream>
#include <limits>
using std::cout;
using std::cin;
using std::numeric_limits;
using std::streamsize;

struct Choice {
    int lengthWeight = -1;  // 0 exit, 1 length,   2 weight
    int meterFeet = -1;     // 0 exit, 1 feet/m,   2 m/feet
    int kiloPound = -1;     // 0 exit, 1 pound/kg, 2 kg/pound
};

void makeChoice(Choice& choice);                    // menu

void makeChoice(Choice& choice, Choice& subChoice); // submenu

int main ( ) {
    Choice choice, subChoice;

    while (true) {
        makeChoice(choice);
        if (choice.lengthWeight == 0) break;        // menu termination

        if (choice.lengthWeight == 1 || choice.lengthWeight == 2) {
            makeChoice(choice, subChoice);
            if (choice.lengthWeight == 0)           // sub-menu termination
                break;
        }

        if (choice.lengthWeight == 1) {
            // TODO
        }
        if (choice.lengthWeight == 2) {
            // TODO
        }

    }
    cout << '\n';
    return 0;
}

void makeChoice(Choice& choice) {
    while (true) {
        cout << "Menu:\n"
             << "1. Convert length (feet & inches <-> km & meters)\n"
             << "2. Convert weight (pounds & ounces <-> kg & grams)\n"
             << "0. Exit\n"
             << "Choice:";
        if (!(cin >> choice.lengthWeight)) {
            cout  << "Invalid choice.\n\n";
            cin.clear();
            cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        // ignore remaining input
        cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
        if (choice.lengthWeight == 0 ||
            choice.lengthWeight == 1 ||
            choice.lengthWeight == 2)
            break;

        cout << "Invalid choice.\n\n";
    }
}

void makeChoice(Choice& choice, Choice& subChoice) {
    while (true) {
        int answer;
        if (choice.lengthWeight == 1)
            cout << "Length menu:\n"
                 << "1. Convert feet & inches to meters and centimeters\n"
                 << "2. Convert meters & centimeters to feet & inches\n";
        else if (choice.lengthWeight == 2)
            cout << "Weight menu:\n"
                 << "1. Convert pounds & ounces to kilos and grams\n"
                 << "2. Convert kilo & grams to pounds & ounces\n";

        cout     << "0. Exit\n"
                 << "Enter action:\n";

        if (!(cin >> answer)) {
            cout << "Invalid choice.\n\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        // ignore remaining input after 1 or 2
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (answer < 0 || answer > 2) {
            cout << "Invalid choice.\n\n";
            continue;
        }
        if (answer == 1)
            subChoice.meterFeet = answer;
        if (answer == 2)
            subChoice.kiloPound = answer;
        if (answer == 0)
            choice.lengthWeight = answer;
        break;
    }
}
```


