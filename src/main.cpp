#include <StableMarriage/Globals.h>
#include <StableMarriage/OptionL.h>
#include <StableMarriage/OptionH.h>
#include <StableMarriage/OptionB.h>
#include <StableMarriage/OptionE.h>
#include <StableMarriage/OptionR.h>
#include <StableMarriage/OptionI.h>
#include <StableMarriage/OptionG.h>
#include <iostream>
#include <ctime>

int main() {
    std::srand((unsigned int)std::time(0));
    
    while(1) {
        std::cout << "Choose an option below:\n";
        std::cout << "(R) Generate And Calculate Random Samples\n";
        std::cout << "(L) Test Latin Matrix\n";
        std::cout << "(H) Hill Climbing Search\n";
        std::cout << "(B) Best First Search\n";
        std::cout << "(I) Input Matrix\n";
        std::cout << "(E) Extract Top Seeds\n";
        std::cout << "(G) Generate a new matrix that is n + 1\n\n";
        std::cout << "Enter choice: ";
        std::cin >> ch;
        std::cout << '\n' << '\n';
        if (ch == 'R' || ch == 'r'){
            optionR();
        }else if (ch == 'L' || ch == 'l'){
            optionL();
        }else if (ch == 'I' || ch == 'i'){
            optionI();
        }else if (ch == 'H' || ch == 'h'){
            optionH();
        }else if (ch == 'B' || ch == 'b'){
            optionB();
        }else if (ch == 'E' || ch == 'e'){
            optionE();
        }else if (ch == 'G' || ch == 'g'){
            optionG();
        }
    }
    return 0;
}
