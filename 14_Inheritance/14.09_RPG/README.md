# RPG Game

Suppose that you are creating a fantasy role - playing game.In this game, we have
four different types of creatures : humans, cyberdemons, balrogs, and elves.To
represent one of these creatures, we might define a Creature class as follows :
	class Creature
{
private:
	int type; // 0 human, 1 cyberdemon, 2 balrog, 3 elf
	int strength; // How much damage we can inflict
	int hitpoints; // How much damage we can sustain
	string getSpecies(); // Returns type of species
public:
	Creature();
	// Initialize to human, 10 strength, 10 hit points
	Creature(int newType, int newStrength, int newHit);
	// Initialize creature to new type, strength, hit points
	// Also add appropriate accessor and mutator functions
	// for type, strength, and hit points
	int getDamage();
	// Returns amount of damage this creature
	// inflicts in one round of combat
};
Here is an implementation of the getSpecies() function:
string Creature::getSpecies()
{
	switch (type)
	{
	case 0: return "Human";
	case 1: return "Cyberdemon";
	case 2: return "Balrog";
	case 3: return "Elf";
	}
	return "Unknown";
}
The getDamage() function outputs and returns the damage this creature can
inflict in one round of combat.The rules for calculating the damage are as follows :
■ Every creature inflicts damage that is a random number r, where 0 < r <=
	strength.
■ Demons have a 5 % chance of inflicting a demonic attack, which is an additional
	50 damage points.Balrogs and Cyberdemons are demons. 
■ Elves have a 10 % chance to inflict a magical attack that doubles the normal
	amount of damage.
■ Balrogs are very fast, so they get to attack twice.

An implementation of getDamage() is given here :
int Creature::getDamage()
{
	int damage;
	// All creatures inflict damage, which is a
	// random number up to their strength
	damage = (rand() % strength) + 1;
	cout << getSpecies() << " attacks for " <<
		damage << " points!" << endl;
	// Demons can inflict damage of 50 with a 5% chance
	if ((type = 2) || (type == 1))
		if ((rand() % 100) < 5)
		{
			damage = damage + 50;
			cout << "Demonic attack inflicts 50 "
				<< " additional damage points!" << endl;
		}
	// Elves inflict double magical damage with a 10% chance
	if (type == 3)
	{
		if ((rand() % 10) == 0)
		{
			cout << "Magical attack inflicts " << damage <<
				" additional damage points!" << endl;
			damage = damage * 2;
		}
	}
	// Balrogs are so fast they get to attack twice
	if (type == 2)
	{
		int damage2 = (rand() % strength) + 1;
		cout << "Balrog speed attack inflicts " << damage2 <<
			" additional damage points!" << endl;
		damage = damage + damage2;
	}
	return damage;
}

One problem with this implementation is that it is unwieldy to add new creatures.
Rewrite the class to use inheritance, which will eliminate the need for the variable
type.The Creature class should be the base class.The classes Demon, Elf, and
Human should be derived from Creature.The classes Cyberdemon and Balrog
should be derived from Demon.You will need to rewrite the getSpecies() and
getDamage() functions so they are appropriate for each class.
For example, the getDamage() function in each class should only compute the
damage appropriate for that object.The total damage is then calculated by combining
the results of getDamage() at each level of the inheritance hierarchy.As an
example, invoking getDamage() for a Balrog object should invoke getDamage()
for the Demon object, which should invoke getDamage() for the Creature object.
This will compute the basic damage that all creatures inflict, followed by the random
5 % damage that demons inflict, followed by the double damage that balrogs inflict.
Also include mutator and accessor functions for the private variables.Write a main
function that contains a driver to test your classes.It should create an object for
each type of creature and repeatedly outputs the results of getDamage().

---

## Design of This Solution

This folder contains an inheritance-based redesign of the original, 
type-coded `Creature` class. The goal is to model the RPG creatures with proper polymorphism and to separate the setup phase of the game from the play phase.

### Class Hierarchy and Responsibilities

- `Creature` (`14_09_Creature.h/.cpp`)
  - Abstract base class (pure virtual `getSpecies`) holding shared state: `strength` and `hitpoints`.
  - Provides `virtual int getDamage() const` which:
	- Uses a `thread_local std::mt19937` RNG and `std::uniform_int_distribution<int>(1, strength)` to compute base damage in `[1, strength]`.
	- Prints `<species> attack for X points` using virtual `getSpecies`.
  - Provides accessors `getStrength`, `getHitpoints` and stream operators `>>` / `<<` to read and print stats.

- `Human` (`14_09_Human.h/.cpp`)
  - `class Human : public Creature`.
  - `getDamage` just defers to `Creature::getDamage` (no additional rules).
  - `getSpecies` returns a stored `std::string` with value `"Human"`.

- `Demon` (`14_09_Demon.h/.cpp`)
  - `class Demon : public Creature` (base for demonic types).
  - `getDamage` calls `Creature::getDamage` for base damage, then applies a 5% chance to add a fixed `DEMONIC_ATTACK` (50) and prints a demonic-attack message when triggered.

- `Cyberdemon` (`14_09_Cyberdemon.h/.cpp`)
  - `class Cyberdemon : public Demon`.
  - Only overrides `getSpecies` to return `"Cyberdemon"`; all damage rules come from `Demon` + `Creature`.

- `Balrog` (`14_09_Balrog.h/.cpp`)
  - `class Balrog : public Demon`.
  - `getDamage`:
	- Calls `Demon::getDamage()` (base random damage plus optional demonic bonus).
	- Performs a second, independent attack: a new random roll in `[1, getStrength()]` using its own `thread_local std::mt19937` and `std::uniform_int_distribution`.
	- Prints `"Balrog speed attack inflicts X additional damage points!"` and adds this to the total.
  - `getSpecies` returns `"Balrog"`.

- `Elf` (`14_09_Elf.h/.cpp`)
  - `class Elf : public Creature`.
  - `getDamage`:
	- Calls `Creature::getDamage()` for base damage.
	- With 10% probability (`uniform_int_distribution<int>(0, 9) == 0`), prints a magical-attack message and doubles the damage.
  - `getSpecies` returns `"Elf"`.

### Game and Builder Design

- `GameBuilder` (`14_09_Game_Builder.h/.cpp`)
  - Manages the setup phase and owns a dynamic array of `Creature*` (`CreaturePtr* creatures`, with `CreaturePtr = Creature*`).
  - Supports:
	- `addCreature()` – interactive menu to create a `Human`, `Cyberdemon`, `Balrog`, or `Elf` on the heap using `new`, read its stats via `operator>>`, and append its pointer to the dynamic array.
	- `deleteCreature()` – shows current creatures, lets the user choose an index, deletes the selected `Creature*`, and compacts the pointer array.
	- `operator[](int)` – read-only access to a creature during setup.
	- `build()` – constructs a `Game` by passing the internal `CreaturePtr*` and count to `Game`'s private constructor. 
	   After this, the builder sets its `creatures` pointer to `nullptr` and resets `numberCreatures` so that only the `Game` owns and later deletes the creatures.

- `Game` (`14_09_Game.h/.cpp`)
  - Represents the play phase of the game. Once constructed, it is immutable with respect to the creature list.
  - Internally stores `const CreaturePtr* creatures`, `int numberCreatures`, and a `turn` counter.
  - Destructor deletes each `Creature*` in the array and then deletes the pointer array itself.
  - `operator[](int)` returns a `const Creature&` for indexed read-only access.
  - `playNextTurn()`:
	- Increments the turn and, for each creature, calls `getDamage()` polymorphically.
	- Uses `dynamic_cast` to classify the dynamic type (`Human`, `Cyberdemon`, `Balrog`, `Elf`) and accumulate total damage per species.
	- Prints total damage for each species at the end of the turn.

### Input Utilities

- `Validation` (`14_09_Validation.h/.cpp`)
  - Provides robust input helpers:
	- `readNumber(std::istream&, int&)` – reads an integer with basic validation, clearing bad input and retrying.
	- `readLetter(std::istream&, char&)` – reads a single character with similar validation.
  - Used throughout `main` and the builder to keep input handling simple and consistent.

### Application Flow

- `14_09_Application.cpp` contains `main` and drives the game:
  - Creates a `GameBuilder`.
  - Repeatedly prompts the user to:
	- Add new creatures.
	- Delete existing creatures by index.
	- Start the game.
  - Once the user chooses to play, calls `aGame.build()` to obtain a `Game` instance.
  - Enters a loop where it calls `game.playNextTurn()` and asks the user whether to continue (`y/n`) using `readLetter`.

This structure demonstrates classical polymorphism in C++: `getDamage()` 
is built up layer by layer along the inheritance hierarchy (Creature → Demon → Balrog, etc.), 
and the runtime behavior depends on each creature's dynamic type while the game and builder work purely with `Creature*`.

