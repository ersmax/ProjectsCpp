Use inheritance and classes to represent a deck of playing cards.Create a Card class
that stores the suit(Clubs, Diamonds, Hearts, Spades) and name(e.g., Ace, 2, 10,
Jack) along with appropriate accessors, constructors, and mutators.
Next, create a Deck class that stores a vector of Card objects.The default constructor
should create objects that represent the standard 52 cards and store them in the
vector.The Deck class should have functions to :
■ Print every card in the deck.
■ Shuffle the cards in the deck.You can implement this by randomly swapping
every card in the deck.
■ Add a new card to the deck.This function should take a Card object as a
parameter
and add it to the vector.
■ Remove a card from the deck.This removes the first card stored in the vector
and returns it.
■ Sort the cards in the deck ordered by name.
Next, create a Hand class that represents the cards in a hand. Hand should be derived
from Deck. This is because a hand is like a specialized version of a deck; we can
print, shuffle, add, remove, and sort cards in a hand just like cards in a deck. The
default constructor should set the hand to an empty set of cards.
Finally, write a main function that creates a deck of cards, shuffles the deck, and
creates two hands of five cards each. The cards should be removed from the deck
and added to the hand. Test the sort and print functions for the hands and the
deck. Finally, return the cards in the hand to the deck and test to ensure that the
cards have been properly returned.
You may add additional functions or class variables as desired to implement your
solution.

---

The project is implemented in the following files:

- `14_11_Card.h` / `14_11_Card.cpp`
- `14_11_Deck.h` / `14_11_Deck.cpp`
- `14_11_Hand.h` / `14_11_Hand.cpp`
- `14_11_Validation.h` / `14_11_Validation.cpp`
- `14_11_Application.cpp`

## Card

The `Card` class models a single playing card using two `std::string` members:

- `suit` – one of `"Clubs"`, `"Diamonds"`, `"Hearts"`, `"Spades"`.
- `name` – one of `"Ace"`, `"2"`, `"3"`, `"4"`, `"5"`, `"6"`, `"7"`, `"8"`, `"9"`, `"10"`, `"Jack"`, `"Queen"`, `"King"`.

Two inline constant arrays in `14_11_Card.h` define the allowed values and their
ordering:

- `SUITS[N_SUITS]`
- `NAMES[N_NAMES]`

`14_11_Card.cpp` contains:

- Validation helpers `validSuit` and `validName` that check user input against
  those arrays.
- A helper `indexOf` that returns the index of a string in one of the arrays.
- `Card::operator<` uses `indexOf` to order cards first by `name` (rank
  according to `NAMES`), and for equal names by `suit` according to `SUITS`.
- `Card::operator==` compares both `name` and `suit`.
- Extractor `operator>>` asks the user for a suit and a name, validates them,
  and stores them in the `Card`.
- Inserter `operator<<` prints a card as `"<suit> <name>"` followed by a
  newline.

## Deck

The `Deck` class owns a dynamic array of `Card` objects through a raw pointer
`CardPtr deck` and an integer `numberCards` that tracks how many cards are
logically in the deck.

### Construction and lifetime

- The default constructor allocates a dynamic array of size `DECK_SIZE` (52)
  and fills it with all combinations of `SUITS` and `NAMES`, producing a
  standard deck of 52 cards.
- The destructor releases the dynamic array with `delete[]`.
- The copy constructor allocates a new array and copies all cards from the
  other deck.
- The copy-assignment operator reallocates if needed and then copies all cards
  from the source deck.

### Core operations

- `print(std::ostream&) const` prints all cards in order as
  `"Card i: <card>"`, using `Card::operator<<` for each element.
- `sort()` implements selection sort over the dynamic array, using
  `Card::operator<` to define the ordering. It returns `*this` so it can be
  chained with `operator<<` (e.g. `std::cout << deck.sort();`).
- `shuffle()` implements a Fisher–Yates shuffle:
  - Uses a `thread_local std::mt19937` engine seeded from `std::random_device`.
  - For `idx` from `numberCards - 1` down to `1`, picks a random index in
    `[0, idx]` and swaps `deck[idx]` with `deck[idxRandom]`.
- `add(const Card&)` grows the deck by one card:
  - Allocates a new array of size `numberCards + 1`.
  - Copies existing cards.
  - Appends the new `Card` at the end.
  - Deletes the old array and updates `deck` and `numberCards`.
- `remove()` removes and returns the first card:
  - Stores `deck[0]` into a local `removed` variable.
  - Allocates a new array of size `numberCards - 1`.
  - Copies all remaining cards, shifting them down by one.
  - Deletes the old array, updates `deck` and `numberCards`, and returns
    `removed` by value.
- `emptyDeck()` sets `numberCards` to `0` (logical empty deck) without freeing
  the underlying storage.
- `getNumberCards()` returns the current logical size.

The free `operator<<` for `Deck` delegates to `print`, and `operator>>` reads
cards interactively from the user, using `Card::operator>>`, checking for
duplicates with `operator==`, and calling `add` for each new card.

## Hand

`Hand` is a public subclass of `Deck` defined in `14_11_Hand.h` and
implemented in `14_11_Hand.cpp`.

- `Hand::Hand()` calls the `Deck` default constructor to allocate storage, then
  calls `emptyDeck()` to set `numberCards` to `0`.
- A `Hand` therefore starts with the capacity of a full deck but is logically
  empty. It reuses all `Deck` operations (`add`, `remove`, `sort`, `shuffle`,
  `print`, `operator<<`, etc.) to behave like a specialized deck containing
  the cards currently held by a player.

## Validation helpers

`14_11_Validation.h/.cpp` define two overloads of `readName` in the
`myNamespaceValidation` namespace:

- `readName(std::istream&, std::string&)` reads a full line into a string,
  retrying on input failure.
- `readName(std::istream&, char&)` reads a single character, clears error
  state, and discards the rest of the line on failure.

These helpers are used by `Card::operator>>` and `Deck::operator>>` to obtain
robust input from the user.

## Application logic

`14_11_Application.cpp` wires everything together:

1. Creates a `Deck aDeck;` which starts as a full, ordered 52-card deck.
2. Creates a `std::vector<Hand> hands` with two `Hand` objects.
3. Shuffles the deck with `aDeck.shuffle();`.
4. Calls `createHand(aDeck, hands);` to deal cards from the deck into each
   hand:
   - First checks that the deck has at least `hands.size() * CARDS_HAND`
     cards; if not, prints an error and returns.
   - Then, in `CARDS_HAND` rounds, removes one card per hand from the front of
     the deck and adds it to that hand. After this, each hand has five cards
     and the deck has 42 cards remaining.
5. Prints both hands, then prints the result of sorting each hand in-place via
   `hand.sort()` chained into `operator<<`.
6. Prints the remaining cards in the deck in unsorted and sorted order.
7. Calls `returnHand(aDeck, hands);` to move all cards back from each hand to
   the deck:
   - For each `Hand` in the vector, repeatedly calls `remove()` while
     `getNumberCards() > 0`, and uses `Deck::add` to append those cards back to
     `aDeck`.
8. Sorts the full deck again and prints it, together with the final card
   counts in the deck and in each hand to verify that all 52 cards have been
   returned and both hands are empty.

Overall, the design uses inheritance to reuse all `Deck` functionality in
`Hand`, standard comparison operators on `Card` to support sorting, and a
manually-managed dynamic array inside `Deck` to practice pointer and
allocation logic instead of using `std::vector`.
