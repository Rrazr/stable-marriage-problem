#include <StableMarriage/Globals.h>
#include <StableMarriage/OptionL.h>
#include <StableMarriage/OptionH.h>
#include <StableMarriage/OptionE.h>
#include <StableMarriage/OptionR.h>
#include <StableMarriage/OptionP.h>
#include <iostream>
#include <ctime>

int main() {
    std::srand((unsigned int)std::time(0));
    
    int initialN;
    std::cout << "Enter the initial matrix size (n): ";
    std::cin >> initialN;
    initializeSystem(initialN);
    
    while(1) {
        std::cout << "Choose an option below:\n\n";
        std::cout << "(S) Settings (Change n)\n";
        std::cout << "(R) Generate And Calculate Random Samples\n";
        std::cout << "(L) Test Latin Matrix\n";
        std::cout << "(H) Hill Climbing Search\n";
        std::cout << "(P) Input Psuedo Latin Matrix\n";
        std::cout << "(E) Extract Top Seeds\n";
        std::cout << "(Q) Quit Program\n";
        std::cout << "\nEnter choice: ";
        
        std::cin >> ch;
        std::cout << '\n' << '\n';

        if (ch == 'Q' || ch == 'q') {
            std::cout << "Exiting program...\n";
            break;
        } else if (ch == 'S' || ch == 's') {
            int newN;
            std::cout << "Current n = " << n << ".\nEnter new matrix size (n): ";
            std::cin >> newN;
            initializeSystem(newN);
            std::cout << "System initialized with n = " << n << ".\n\n";
        } else if (ch == 'R' || ch == 'r'){
            optionR();
        }else if (ch == 'L' || ch == 'l'){
            optionL();
        }else if (ch == 'H' || ch == 'h'){
            optionH();
        }else if (ch == 'P' || ch == 'p'){
            optionP();
        }else if (ch == 'E' || ch == 'e'){
            optionE();
        }
    }
    return 0;
}
