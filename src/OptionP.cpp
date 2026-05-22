#include <StableMarriage/OptionP.h>
#include <StableMarriage/Globals.h>
#include <StableMarriage/NumberOfSMFunctions.h>
#include <StableMarriage/MatrixManipFunctions.h>
#include <iostream>

void optionP() {
    int m;
    std::cout << "(A) Enter your own psuedo latin" << std::endl;
    std::cout << "(C) Generate all the SM's of n - 1" << std::endl;
    std::cout << "(D) Drop three" << std::endl;
    std::cout << "(E) Drop two" << std::endl;

    std::cout << "Enter choice: " << std::endl;
    std::cin >> ch;
    if(ch == 'a' || ch == 'A'){
        for (int i = 0; i < n; i ++){
           std::cout << "Enter Row " << i + 1 << ": ";
           for (int j = 0; j < n; j ++){
               std::cin >> m;
               matrix[i][j].m = m - 1;
               matrix[i][j].w =  n - matrix[i][j].m;
           }
           std::cout << '\n';
        }
        convertToGeneral();
        std::cout << "This is the given matrix";
        printMatrix();
        numberOfStableMatchings();
        std::cout << "The number of SM's is " << cnt<< std::endl;
    }
    
    if(ch == 'c' || ch == 'C'){
        int startingN;
        std::cout << "Enter the n you would like to start with" << std::endl;
        std::cin >> startingN;
        dropToOneLessN(startingN);
    }else if(ch == 'd' || ch == 'D'){
        int startingN;
        std::cout << "Enter the n you would like to start with" << std::endl;
        std::cin >> startingN;
        dropToLessN(startingN);
    }else if(ch == 'e' || ch == 'E'){
        int startingN;
        std::cout << "Enter the n you would like to start with" << std::endl;
        std::cin >> startingN;
        dropTo2LessN(startingN);
    }
}
