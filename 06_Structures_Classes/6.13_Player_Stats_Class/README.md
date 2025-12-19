Do Programming Project 5.19, but this time use a class named Player to store
a player’s name and score. Then use an array of the Player class to store the ten
players

Write a program that manages a list of up to ten players and their high scores in the
computer’s memory (not on disk as in Programming Project 18). Use two arrays
to manage the list. One array should store the player’s name, and the other array
should store the player’s high score. Use the index of the arrays to correlate the
names with the scores. In the next chapter you will learn a different way to organize
related data by putting them into a struct or class. Do not use a struct or class for
this program. Your program should support the following features:
a. Add a new player and score (up to ten players).
b. Print all player names and their scores to the screen.
c. Allow the user to enter a player name and output that player’s score or a message
if the player name has not been entered.
d. Allow the user to enter a player name and remove the player from the list.
Create a menu system that allows the user to select which option to invoke.

---

# Player Stats Class

This project refactors the array-based solution from Project 5.19 to use 
object-oriented programming with a `Player` class.

## Key Differences

### 1. **Data Organization**

**5.19 (Array-Based):**
```cpp
std::string names[MAX];
int scores[MAX];
int size = 0;
```
- Uses **two parallel arrays** to store player names and scores separately
- Index correlation: `names[i]` corresponds to `scores[i]`
- Requires passing both arrays to functions
- Higher risk of desynchronization if not handled carefully

**6.13 (Class-Based):**
```cpp
class Player {
private:
    std::string name;
    int score;
public:
    void setName(const std::string& namePlayer);
    void setScore(int scorePlayer);
    std::string getName() const;
    int getScore() const;
};

Player players[MAX];
int size = 0;
```
- Uses **a single array of Player objects**
- Each `Player` encapsulates both name and score together
- **Better data cohesion** - related data is bundled
- Impossible to have mismatched names and scores

### 2. **Encapsulation & Data Hiding**

**5.19:** Direct array manipulation
```cpp
names[size] = enterName();
scores[size++] = enterScore();
```

**6.13:** Access through class methods
```cpp
players[size].setName(namePlayer);
players[size].setScore(scorePlayer);
size++;
```
- Private member variables prevent direct access
- Controlled access via public getters/setters
- Future-proof: can add validation, logging, or constraints easily

#### 3. **Function Signatures**

**5.19:**
```cpp
void addPlayer(std::string names[], int scores[], int maxSize, int& size);
void showPlayers(const std::string names[], const int scores[], int size);
int findPlayer(const std::string& name, const std::string names[], int size);
```
- Functions require **both arrays** as parameters
- More parameters = more complex function calls
- Easy to accidentally swap parameter order

**6.13:**
```cpp
void addPlayer(Player players[], int maxSize, int& size);
void showPlayers(Player players[], int size);
int findPlayer(Player players[], int size, const std::string& name);
```
- Functions only need **one array** parameter
- Cleaner, more maintainable function signatures
- Less prone to parameter ordering errors

#### 4. **Code Maintainability**

**5.19 - Removing a player:**
```cpp
for (int idx = playerRanked; idx < size - 1; ++idx) {
    names[idx] = names[idx + 1];      // Must update both arrays
    scores[idx] = scores[idx + 1];
}
```
- Must remember to update **both arrays**
- If we forget one, data becomes corrupted

**6.13 - Removing a player:**
```cpp
for (int idx = idxPlayer; idx < size - 1; ++idx)
    players[idx] = players[idx + 1];  // Single assignment
```
- **Single assignment** updates both name and score automatically
- Uses default assignment operator
- Less code, fewer bugs

#### 5. **Type Safety & Semantics**

**5.19:**
- Functions work with primitive types (`std::string[]`, `int[]`)
- No semantic meaning in the type system
- We could accidentally pass the wrong arrays

**6.13:**
- Functions work with `Player[]` - a domain-specific Abstract Data Type
- **Self-documenting code**: function signature clearly shows intent
- Compiler enforces type safety

#### 6. **Menu System**

**5.19:**
```cpp
void menu(char& choice);  // Pass by reference, modifies parameter
```
- Uses pass-by-reference to return the choice
- Less conventional in modern C++

**6.13:**
```cpp
char menu();  // Returns the choice directly
```
- Returns the value directly
- More idiomatic style

#### 7. **Input Validation**

**Both implementations** have input validation:
- Trim leading/trailing whitespace
- Handle EOF correctly
- Validate empty names and invalid scores

### Advantages of Class-Based Approach (6.13)

**Encapsulation**: Data and behavior bundled together  
**Single Responsibility**: Player class manages player data  
**Easier to extend**: Can add more player attributes (e.g., level, team) without changing function signatures  
**Type safety**: Compiler prevents misuse  
**Cleaner code**: Fewer parameters, simpler logic  
**Less error-prone**: Impossible to desynchronize name/score arrays  