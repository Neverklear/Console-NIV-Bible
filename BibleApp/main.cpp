#include "BibleApp.h"
#include <iostream>

int main() {
    char continueChoice;
    do {
        intro();
        menu();
        std::cout << "\nReturn to main menu? (y/n): ";
        std::cin >> continueChoice;
        std::cout << std::endl;
    } while (continueChoice == 'y' || continueChoice == 'Y');
    return 0;
}
