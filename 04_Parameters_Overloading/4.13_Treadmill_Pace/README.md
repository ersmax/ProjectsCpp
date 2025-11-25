You would like to know how fast you can run in miles per hour. Your treadmill
will tell you your speed in terms of a pace (minutes and seconds per mile, such as
“5:30 mile”) or in terms of kilometers per hour (kph).
Write an overloaded function called convertToMPH. The first definition should
take as input two integers that represent the pace in minutes and seconds per mile
and return the speed in mph as a double. The second definition should take as
input one double that represents the speed in kph and return the speed in mph as
a double. One mile is approximately 1.61 kilometers. Write a driver program to
test your function.

---

# Treadmill Pace -> MPH Converter

Small utility that converts a running pace (minutes and seconds per mile) 
or a speed in kilometers per hour (kph) into miles per hour (mph). 
The program demonstrates overloaded functions named `convertToMPH`.

## Behavior
- Prompts for a pace as two integers: minutes and seconds per mile (separated by a space).
- Validates input: minutes and seconds must be non-negative and the pace cannot be `0 0`.
- Normalizes seconds: values \>= 60 are carried into minutes (for example, `5 75` -> `6 15`).
- Computes speed in mph from the pace and also converts mph \↔\ kph using the constant `KM_MILE = 1.61`.
- Guards against divide-by-zero / invalid input when computing speed.

## Functions
- `double convertToMPH(int minutes, int seconds)`  
  Returns speed in mph computed from the pace (minutes and seconds per mile).
- `double convertToMPH(double speedKPH)`  
  Converts a kph value to mph.

- `void enterData(int& minutes, int& seconds)`  
  Reads, validates, and normalizes user input.

## Build (Windows / CLion)
- Using g++ (MinGW) from a terminal:
```cpp
g++ -std=c++17 -O2 -o treadmill 13_Treadmill_Pace.cpp
.\treadmill.exe
```
  
## Usage examples
- Input: `5 30`  
  Output: shows mph equivalent and kph conversion.
- Input: `5 75`  
  Program normalizes to `6 15` and computes the corresponding mph.

## Notes
- One mile ≈ `1.61` kilometers (constant `KM_MILE`).
- The program formats numeric output to two decimal places.
