#include <StableMarriage/OptionS.h>
#include <StableMarriage/Globals.h>
#include <StableMarriage/UIUtils.h>
#include <iostream>

void optionS() {
    char settingChoice;
    while (true) {
        clearScreen();
        std::cout << "Settings:\n\n";
        std::cout << "(1) Change matrix size (n)\n";
        std::cout << "(2) Change MAX_SM\n\n";
        std::cout << "(B) Back to Main Menu\n\n";
        std::cout << "Enter choice: ";
        std::cin >> settingChoice;
        
        if (settingChoice == 'B' || settingChoice == 'b') {
            break;
        } else if (settingChoice == '1') {
            int newN;
            std::cout << "Current n = " << n << "\nEnter new matrix size (n): ";
            std::cin >> newN;
            initializeSystem(newN);
            std::cout << "System initialized with n = " << n << "\n\n";
            waitForEnter();
        } else if (settingChoice == '2') {
            int newMax;
            std::cout << "Current MAX_SM = " << MAX_SM << "\nEnter new MAX_SM: ";
            std::cin >> newMax;
            MAX_SM = newMax;
            std::cout << "MAX_SM updated to " << MAX_SM << "\n\n";
            waitForEnter();
        }
    }
}
