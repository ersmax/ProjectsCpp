# Redeem Voucher

You have a voucher for a bakery, which you redeem to buy baked goods of your
choice. The value of the voucher is fixed and the total bill of the items selected
should not exceed the voucher value. If the voucher has any value left after the
purchase, then it cannot be utilized again. Write a program that displays 4 items
and their prices as a menu and then reads the value of the voucher.
Write a function, with parameters itemCode and voucherValue passed by reference,
that deducts the price of an item from the voucher’s value only if the item’s
value is less that or equal to the voucher value. Use a loop to invoke the above
function as many times as required until the value of the voucher is less than or
equal to the cheapest item on the menu.
Finally, display the calculated sum of the prices of the items selected, and the unutilized
balance on the voucher after purchase.

---

## Program Documentation

This program models redeeming a fixed-value voucher. 
It reads 4 items (name and price), reads the voucher value, sorts items by price (descending), 
redeems items while the voucher covers them, and prints redeemed items, total redeemed value, and remaining voucher balance.

## Build and run
- Compile with a C++17-compatible compiler, for example:

```
g++ -std=c++17 -O2 -Wall -Wextra -o redeem 3_Redeem_Voucher.cpp
./redeem
```

## High-level flow
1. Read voucher value (`addVoucherValue`).
2. Read 4 items into `items` (`addItem` called 4 times).
3. Sort items in descending price order (`sortItem`).
4. Display menu (`showItem`).
5. Redeem items while possible (`useVoucher`) — removes non-redeemed items from the vector.
6. Display redeemed items and totals (`showItem`, `showTotalBalance`).

## Functions (brief)
- `void addVoucherValue(double& voucherValue)`
  - Reads a non-negative `double` from `stdin` into `voucherValue`. Validates input and discards extra tokens.

- `void addItem(std::vector<std::pair<std::string, double>>& items)`
  - Reads an item `name` and `price` (non-negative). Appends `(name, price)` to `items`. Validates input.

- `void sortItem(std::vector<std::pair<std::string, double>>& items)`
  - Sorts `items` in-place in descending order by price. Uses selection sort; indices use `size_t` to match `items.size()`.

- `void showItem(const std::vector<std::pair<std::string, double>>& items)`
  - Prints each item's name and price to `stdout`.

- `void useVoucher(std::vector<std::pair<std::string, double>>& items, double& voucherValue, double& total)`
  - Iterates `items` with an iterator. If `voucherValue >= price` then deducts price from `voucherValue` and adds to `total`; otherwise erases the item from `items`. After the call, `items` contains only redeemed items and `total` is the sum redeemed.

- `void showTotalBalance(double voucherValue, double total)`
  - Prints `total` redeemed and `voucherValue` remaining.

## Design notes and fixes
- Use `size_t` (or the container's `size_type`) for loop indices to avoid signed/unsigned warnings and match `.size()`.
- In selection sort the comparison must use the current candidate maximum (`items[idxMaxValue].second`) — otherwise the wrong element can be selected.
- `useVoucher` erases non-redeemed items while iterating; it correctly uses the returned iterator from `erase`.
- `showTotalBalance` parameters can be plain `double` (top-level `const` on pass-by-value is redundant).

## Example interaction
```
Enter the value of voucher: 10
Enter the name and price of item: Croissant 3
Enter the name and price of item: Baguette 4
Enter the name and price of item: Muffin 2.5
Enter the name and price of item: Donut 1.5

Menu:
Baguette price: 4
Croissant price: 3
Muffin price: 2.5
Donut price: 1.5

Items redeemed:
Baguette price: 4
Croissant price: 3
Muffin price: 2.5

Total value items redeemed: 9.5
Voucher value left (not redeemed): 0.5
```

## Assumptions and constraints
- Exactly 4 items are read (`ITEMS = 4`).
- Prices and voucher values are non-negative `double`s.
- Remaining voucher value cannot be reused beyond the program's single redemption pass.