// I/O

#include <iostream>
#include <limits>

using namespace std;

// application's starting point
int main (void) {
    int number;
    while (true) {
        std::cout << " Enter an integer " << "\n";
        std::cin >> number;

        // Check if the input is a number
        if (std::cin.fail()) {
            std::cin.clear(); // Clear the fail state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
            std::cout << "That's not a valid number. Please try again." << std::endl;
        } else {
            // Valid input
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
            break; // Exit the loop
        }
    }
    std::cout << "You entered: " << number << std::endl;
    return 0;
}