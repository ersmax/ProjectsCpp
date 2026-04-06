Create a class for a simple blog. The owner of the blog should be able to (a) post a
new message, (b) numerically list and display all messages, and (c) select a specific
message and delete it.
Viewers of the blog should only be able to numerically list and display all posted
messages.
Create a class Viewer and a class Owner that uses inheritance to help implement
the blog functionality. Store the data messages using any format you like (a vector
of type string may be easiest). A menu function should be implemented for each
class that outputs the legal choices for the type of user. To test your classes, the
main function of the program should allow the user to invoke the menus from the
Viewer and Owner objects.

---

## Implementation Overview

This project implements the required blog using four main components:

- `Message` (`14_08_Message.h/.cpp`)
  - Represents a single blog entry with `title` and `text`.
  - Provides constructors with basic validation (title cannot be empty).
  - Overloads `operator>>` to read a message (title + text) from `std::istream`.
  - Overloads `operator<<` to print a formatted message to `std::ostream`.

- `Blog` (`14_08_Blog.h/.cpp`)
  - Owns a dynamic array of `Message` objects using a raw pointer (`MessagePtr blogMessages`) and an `int nMessages` size.
  - Implements the “blog storage” abstraction:
    - `addNewMessage(const Message&)` reallocates the array and appends a new message.
    - `deleteMessage(int index)` removes a message at a zero-based index, compacts the array, and updates the size.
    - `getNumMessages() const` returns the current number of messages.
    - `operator[](int)` and `operator[](int) const` provide indexed access with bounds checking.
  - Supports copy construction, assignment, and proper destruction of the dynamic array.

- `Viewer` (`14_08_Viewer.h/.cpp`)
  - Models a user that can only **view** messages.
  - Holds a pointer `BlogPtr blog` to a `Blog` instance; the default constructor sets this to `nullptr`, while other constructors bind it to an existing `Blog`.
  - If `blog` is `nullptr`, all operations report that no blog is associated and return early.
  - Provides the public interface:
    - `void menu()` – loops and offers options:
      - `1` – list all messages (titles only).
      - `2` – display a single message (title + text).
      - `0` – exit the viewer menu.
  - Internal helpers used by `menu()`:
    - `printAllTitles() const` – prints each message title with a 1-based index.
    - `printTheMessage() const` – lets the user choose a message number and prints its full contents.

- `Owner` (`14_08_Owner.h/.cpp`)
  - Inherits from `Viewer` and represents a user that can **view and modify** the blog.
  - Reuses all viewing behavior from `Viewer` and extends the menu with owner-specific options.
  - Public interface:
    - `void menu() override` – loops and offers options:
      - `1` – list titles (via `printAllTitles()`).
      - `2` – show a single message (via `printTheMessage()`).
      - `3` – add a new message (`postNewMessage()`).
      - `4` – delete an existing message (`deleteOldMessage()`).
      - `0` – exit the owner menu.
  - Modification helpers:
    - `postNewMessage()` – reads a `Message` from input and calls `blog->addNewMessage(...)`.
    - `deleteOldMessage()` – shows all titles, reads a 1-based index, validates it, and calls `blog->deleteMessage(...)`.
  - If `blog` is `nullptr`, all owner operations print a warning and return without modifying anything.

- `Validation` helpers (`14_08_Validation.h/.cpp`)
  - `readText(std::istream&, std::string&)` – safely reads a full line of text.
  - `readNumber(std::istream&, int&)` – safely reads an `int`, with error reporting and input cleanup.

## Program Flow (`main`)

File: `14_08_Application.cpp`

- Creates a `Blog aBlog;` instance which holds all messages for this run.
- Creates owners/viewers:
  - `Owner oliver("Oliver", aBlog);` – owner bound to `aBlog` (can view + modify).
  - `Viewer aViewer(aBlog);` – viewer bound to the same `aBlog` (can only view).
  - `Owner willie;` – default-constructed owner with no associated blog; used to test the `nullptr`-safe behavior.
- Reads viewer details from the console (`operator>>` on `Viewer`).
- In a loop:
  - Calls `oliver.menu()` to exercise the owner menu (post, list, show, delete).
  - Calls `aViewer.menu()` to exercise the viewer menu (list, show).
  - Asks whether to continue.
- After the loop, calls `willie.menu()` to demonstrate that an owner with no associated blog is handled gracefully.

This structure satisfies the assignment: messages are stored centrally in a `Blog`, owners can post/delete and list/display, viewers can only list/display, and both roles see the same blog content when they share the same `Blog` instance.
