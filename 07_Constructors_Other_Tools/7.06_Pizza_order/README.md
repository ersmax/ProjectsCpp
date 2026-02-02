  This Programming Project requires you to first complete Programming Project 6.7
from Chapter 6, which is an implementation of a Pizza class. Add an Order class
that contains a private vector of type Pizza. This class represents a customer’s
entire order, where the order may consist of multiple pizzas. Include appropriate
functions so that a user of the Order class can add pizzas to the order (type is deep
dish, hand tossed, or pan; size is small, medium, or large; number of pepperoni or
cheese toppings). You can use constants to represent the type and size. Also write
a function that outputs everything in the order along with the total price. Write a
suitable test program that adds multiple pizzas to an order(s).

---

## Order Class Logic

### Class Structure
The `Order` class manages a customer's complete pizza order, which can contain multiple pizzas.

**Key Components:**

1. **Static Member - orderId**
   - Shared across ALL Order instances (class-level counter)
   - Automatically increments each time a new Order is created
   - Ensures each order gets a unique ID: "Order 1", "Order 2", etc.
   - Initialized once: `int Order::orderId = 1;`

2. **Instance Members** (unique to each Order object)
   - `nameOrder`: Stores the order's name/ID (e.g., "Order 1", "John's Order")
   - `anOrder`: Vector containing all Pizza objects in this specific order
   - `totalPrice`: Accumulates the total cost of all pizzas in THIS order only

### Key Methods

**Constructor**
```cpp
Order() { setName("Order " + std::to_string(orderId++)); }
```
- Generates unique order name using static counter
- Post-increment (orderId++) ensures next order gets next number

**addPizza()**
```cpp
void addPizza() { 
    const Pizza aPizza;                      // Creates new Pizza (prompts user for details)
    anOrder.push_back(aPizza);               // Adds pizza to this order's vector
    totalPrice += aPizza.computePrice();     // Updates THIS order's running total
}
```
- Creates a Pizza object (which triggers interactive prompts for type, size, toppings)
- Stores pizza in the order's vector
- Immediately calculates and adds the pizza's price to the order total

**showOrder()**
```cpp
void showOrder() const {
    for (const auto& pizza : anOrder) 
        pizza.outputDescription();
}
```
- Iterates through all pizzas in THIS specific order
- Calls outputDescription() on each pizza to display its details
- Uses `const auto&` to avoid copying pizza objects (efficient)

**getTotalPrice()**
- Returns the accumulated total price for THIS order only
- Each Order instance maintains its own separate totalPrice

---

## Program Flow (main function)

1. **Create Two Separate Orders**
   ```cpp
   Order anOrder, anotherOrder;  // Creates "Order 1" and "Order 2"
   ```

2. **Add Pizzas to First Order**
   ```cpp
   anOrder.addPizza();   // Prompts for pizza #1 details, adds to Order 1
   anOrder.addPizza();   // Prompts for pizza #2 details, adds to Order 1
   ```

3. **Add Pizzas to Second Order**
   ```cpp
   anotherOrder.addPizza();  // Pizza #1 for Order 2
   anotherOrder.addPizza();  // Pizza #2 for Order 2
   anotherOrder.addPizza();  // Pizza #3 for Order 2
   ```

4. **Display Order Summaries**
   ```cpp
   std::cout << anOrder.getId() << " price: " << anOrder.getTotalPrice() << '\n';
   anOrder.showOrder();  // Shows all pizzas in Order 1

   std::cout << anotherOrder.getId() << " price: " << anotherOrder.getTotalPrice() << '\n';
   anotherOrder.showOrder();  // Shows all pizzas in Order 2
   ```

---

## Key Design Patterns

1. **Static vs Instance Variables**
   - `static int orderId`: ONE counter shared by all Orders (auto-incrementing ID generator)
   - `double totalPrice`: SEPARATE total for each Order instance

2. **Composition**
   - Order class contains a vector of Pizza objects
   - Demonstrates "has-a" relationship (Order has-a collection of Pizzas)

3. **Encapsulation**
   - Private members ensure data integrity
   - Public interface provides controlled access
   - setName() is private to prevent external modification

4. **Interactive Object Creation**
   - Pizza constructor prompts user for all details
   - Order's addPizza() delegates pizza creation to Pizza class
   - Clear separation of concerns

---

## Example Output Flow

```
[User creates 5 pizzas through interactive prompts]

Order 1 price: 48
Small Pizza Deep Dish with 1 pepperoni and 1 cheese
Total price: $24
Medium Pizza Hand Tossed with 0 pepperoni and 2 cheese
Total price: $24

Order 2 price: 71
Large Pizza Pan with 2 pepperoni and 2 cheese
Total price: $25
Small Pizza Deep Dish with 0 pepperoni and 0 cheese
Total price: $10
...
```

Each order correctly tracks its own pizzas and cumulative total independently.
