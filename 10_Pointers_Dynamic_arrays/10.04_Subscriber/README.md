Create a class named Subscriber that has three member variables:
name – A string that stores the name of the subscriber
numChannels – An integer that tracks how many channels the subscriber subscribes
to.
channelList – A dynamic array of strings used to store the names of the
channels the subscriber subscribes to.
Write appropriate constructor(s), mutator, and accessor functions for the class
along with the following:
• A function that inputs all values from the user, including the list of channel names.
This function will have to support input for an arbitrary number of channels.
• A function that outputs the name and list of all channels.
• A function that resets the number of channels to 0 and the channelList to an
empty list.
• An overloaded assignment operator that correctly makes a new copy of the list
of channels.
• A destructor that releases all memory that has been allocated.
Write a main function that tests all your functions.

---

# Subscriber Class 

## Overview
This project demonstrates the use of dynamic memory management in C++ through a `Subscriber` class. 
The class models a subscriber who can register for an arbitrary number of channels, with channel names stored 
in a dynamically allocated array. 

## Features
- **Dynamic Array of Channels:**
  - Stores channel names in a dynamically allocated array of `std::string`.
  - Supports adding new channels interactively.
- **Constructors:**
  - Default constructor: Initializes an empty subscriber.
  - Name constructor: Initializes a subscriber with a name and no channels.
  - Name and channel list constructor: Initializes a subscriber with a name and a list of channels.
  - Copy constructor: Deep-copies the channel list from another subscriber (does not copy the name).
- **Assignment Operator:**
  - Deep-copies the channel list from another subscriber (does not copy the name).
  - Handles self-assignment and memory management.
- **Destructor:**
  - Releases all dynamically allocated memory.
- **Reset Function:**
  - Clears the channel list and sets the number of channels to zero.
- **Input/Output Operators:**
  - `operator>>`: Allows interactive input of subscriber data and channels.
  - `operator<<`: Outputs subscriber name and channel list.
- **Channel Access:**
  - `operator[]`: Accesses channel names by index with bounds checking.

## Memory Management
- All channel lists are managed with manual `new[]` and `delete[]` operations.
- Copy constructor and assignment operator ensure deep copies to prevent memory leaks and dangling pointers.

## Usage
1. Create subscribers with or without initial channels.
2. Input new channels interactively.
3. Output subscriber data.
4. Copy and assign subscribers to test deep copy semantics.

## Example Main Function
The main function demonstrates:
- Creating subscribers with initial channels.
- Inputting new subscriber data.
- Copying and assigning channel preferences between subscribers.
- Resetting channel lists.

## Learning Outcomes
- Manual dynamic memory management in C++
- Implementing deep copy semantics
- Operator overloading for input/output and assignment
- Safe array access and exception handling

---

