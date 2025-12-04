#include <iostream>
#include <thread>
#include <chrono>
#include <conio.h> // _kbhit, _getch

void print_test_windows() {
    int n = 100000;

    for (int i = 0; i < n; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        std::cout << "\rnumber: " << i << "      " << std::flush; // overwrite line

        if (_kbhit()) { // optional: allow user interrupt
            char c = _getch();
            if (c == 27) break; // ESC to exit
        }
    }

    std::cout << std::endl;
}

int main() {
    print_test_windows();
    return 0;
}
