#include <iostream>     // for std::cout, std::cin
#include <iomanip>      // for std::setw
#include <sstream>      // for std::istringstream
#include <string>       // for std::string

constexpr int VARIATIONS = 5;

void makeChoice(const std::string flavors[], int nFlavors, int quantity[],
                int& choice, int& qtyChosen);
//   Precondition: flavors is an array of strings representing the ice-cream flavors.
// nFlavors is the declared size of the array `flavors` and `quantity`.
// `quantity` is an array of integers representing the quantity available for each flavor.
//   Postcondition: The function prompts the user to make a choice of flavor
// and quantity. The user's choice is placed in `choice` (0-based index)
// and `qtyChosen`. If the user signals to end the program, `choice` is set to -1.

void addChoice(int cart[], int nFlavors, int choice, int qtyChosen);
//   Precondition: cart is an array of integers representing the user's cart.
// nFlavors is the declared size of the array `cart`.
//   Postcondition: The function adds `qtyChosen` of the flavor indicated by
// `choice` (0-based index) to the user's cart.

void showOffer(const std::string flavors[], int nFlavors, const int quantity[]);
//   Precondition: flavors is an array of strings representing the ice-cream flavors.
// nFlavors is the declared size of the array `flavors` and `quantity`.
// `quantity` is an array of integers representing the quantity available for each flavor.
//   Postcondition: The function displays the available flavors with their codes
// and the remaining quantity for each flavor.

void showCart(const std::string flavors[], int nFlavors, const int cart[]);
//   Precondition: flavors is an array of strings representing the ice-cream flavors.
// nFlavors is the declared size of the array `flavors` and `cart`.
// `cart` is an array of integers representing the user's cart.
//   Postcondition: The function displays the contents of the user's cart.

int main( ) {
    std::string flavors[VARIATIONS] = {"Chocolate", "Vanilla", "Strawberry", "Raspberry", "Butterscotch"};
    int quantity[VARIATIONS] = {20, 15, 15, 20, 20};
    int cart[VARIATIONS] = {0};

    int choice, qtyChosen = 0;
    while (true) {
        makeChoice(flavors, VARIATIONS, quantity, choice, qtyChosen);
        if (choice == -1)
            break;
        addChoice(cart, VARIATIONS, choice, qtyChosen);
    }

    showOffer(flavors, VARIATIONS, quantity);
    showCart(flavors, VARIATIONS, cart);

    std::cout << "\n";
    return 0;
}

void makeChoice(const std::string flavors[], const int nFlavors,
                int quantity[], int& choice, int& qtyChosen) {
    choice = -1;
    std::string line;
    while (true) {
        showOffer(flavors, nFlavors, quantity);
        std::cout << "\nEnter item and quantity (separated by space).\n"
                     "To exit, press `-1` :\n";

        // EOF or error
        if (!std::getline(std::cin, line)) {
            choice = -1;
            return;
        }
        std::istringstream iss(line);
        if (!(iss >> choice)) {
            std::cout << "Not a valid choice. Retry\n";
            continue;
        }
        if (choice == -1)
            return;
        if (!(iss >> qtyChosen)) {
            std::cout << "Wrong quantity. Retry\n";
            continue;
        }

        // adjust to zero-based-idx array
        --choice;
        if ((choice < nFlavors) && (choice >= 0) &&
            (qtyChosen > 0) && (qtyChosen <= quantity[choice]) ) {
            quantity[choice] -= qtyChosen;
            break;
        }
        std::cout << "Product not available. Retry\n";
    }
}

void showOffer(const std::string flavors[], const int nFlavors, const int quantity[]) {
    std::cout << "Remaining stock:\n";
    std::cout << std::setw(15)  << "Code"
              << std::setw(15) << "Flavor"
              << std::setw(8)  << "Q.ty\n";

    for (int idx = 0; idx < nFlavors; ++idx)
        std::cout << std::setw(15)  << idx + 1
                  << std::setw(15) << flavors[idx]
                  << std::setw(8)  << quantity[idx] << "\n";
}

void addChoice(int cart[], const int nFlavors, const int choice, const int qtyChosen) {
    if ((choice >= 0) && (choice < nFlavors))
        cart[choice] += qtyChosen;
}

void showCart(const std::string flavors[], const int nFlavors, const int cart[]) {
    bool emptyCart = true;

    std::cout << "\nYour cart: \n";
    for (int idx = 0; idx < nFlavors; ++idx)
        if (cart[idx] > 0) {
            emptyCart = false;
            std::cout << flavors[idx] << ", "
                      << cart[idx] << " scoop(s)\n";
        }
    if (emptyCart)
        std::cout << "Empty cart\n";
}
