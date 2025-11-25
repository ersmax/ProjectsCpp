Your time machine is capable of going forward in time up to 24 hours. The machine
is configured to jump ahead in minutes. To enter the proper number of minutes
into your machine, you would like a program that can take a start time and an
end time and calculate the difference in minutes between them. The end time will
always be within 24 hours of the start time. Use military notation for both the start
and end times (e.g., 0000 for midnight and 2359 for one minute before midnight).
Write a function that takes as input a start time and an end time represented as an
int, using military notation. The function should return the difference in minutes
as an integer. Write a driver program that calls your subroutine with times entered
by the user.
Hint: Be careful of time intervals that start before midnight and end the following day.

---

# Time Difference (24-hour, HHMM)

## Overview
This utility computes the number of minutes to advance a time-machine from a start time to an end time. 
Both times use 24-hour "military" notation as four-digit values (HHMM). 
The end time is guaranteed to be within 24 hours after the start time.

## Behavior and assumptions
- Inputs are treated as strings representing HHMM (e.g., `0000` for midnight, `2359` for 23:59).  
- The program assumes the end time occurs within the next 24 hours (including same-day or next-day).  
- Invalid inputs (wrong length, non-digit characters, or invalid hour/minute ranges) are rejected before computing the difference.

## Key routines
- `minutesFromHHMM(const std::string& t)`  
  Converts an HHMM string to total minutes since midnight. Example: `0130` -> `90`. Validates format and numeric ranges prior to conversion.

- `differenceMinute(const std::string& starting, const std::string& ending)`  
  Returns a non-negative integer number of minutes to advance from `starting` to `ending`. Implementation approach:
  1. Convert both times to minutes since midnight with `minutesFromHHMM`.  
  2. Compute `diff = endingMinutes - startingMinutes`.  
  3. If `diff < 0`, add `24 * 60` to wrap into the next day.  
  This yields the minimal forward interval up to 24 hours.

- `validDate` (or equivalent validator)  
  A helper that verifies an HHMM string is exactly 4 characters, all digits, and represents a valid time (hours 0..23, minutes 0..59).

## Constants
- `constexpr int MINUTES_PER_DAY = 24 * 60;` — used when wrapping negative differences.

## Examples
- Start `0900`, End `1030` -> diff = 90.  
- Start `2300`, End `0030` -> diff = 90 (wraps across midnight).  
- Start `0000`, End `0000` -> diff = 0 (no advancement).  
- Start `2359`, End `2358` -> diff = 24*60 - 1 = 1439.

## Implementation notes
- 2 ways of computing the difference: from total minute (`int differenceMin`) and from hour and minutes separately (`int differenceMinute`)
- When calling `std::isdigit` on `char`, cast to `unsigned char` to avoid Undefined Behavior on negative `char` values.
