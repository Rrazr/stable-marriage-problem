#include <StableMarriage/Globals.h>
#include <StableMarriage/OptionC.h>
#include <StableMarriage/OptionH.h>
#include <StableMarriage/OptionG.h>
#include <StableMarriage/OptionR.h>
#include <StableMarriage/OptionS.h>
#include <StableMarriage/UIUtils.h>
#include <iostream>
#include <ctime>

int main() {
    std::srand((unsigned int)std::time(0));
    
    int initialN;
    std::cout << "Enter the initial matrix size (n): ";
    std::cin >> initialN;
    initializeSystem(initialN);
    
    while(1) {
        clearScreen();
        std::cout << "Choose an option below:\n\n";
        std::cout << "(G) Generate and Calculate Random Samples\n";
        std::cout << "(C) Calculate SM for Matrices\n";
        std::cout << "(H) Hill Climbing Search\n";
        std::cout << "(R) Matrix Reduction\n\n";
        std::cout << "(S) Settings\n";
        std::cout << "(Q) Quit Program\n";
        std::cout << "\nEnter choice: ";
        
        std::cin >> ch;
        std::cout << '\n' << '\n';

        if (ch == 'Q' || ch == 'q') {
            std::cout << "Exiting program...\n";
            break;
        }
        else if (ch == 'S' || ch == 's') {
            optionS();
        } 
        else if (ch == 'G' || ch == 'g'){
            optionG();
            waitForEnter();
        }
        else if (ch == 'C' || ch == 'c'){
            optionC();
            waitForEnter();
        }
        else if (ch == 'H' || ch == 'h'){
            optionH();
            waitForEnter();
        }
        else if (ch == 'R' || ch == 'r'){
            optionR();
            waitForEnter();
        }
    }
    return 0;
}
