#include <StableMarriage/OptionL.h>
#include <StableMarriage/Globals.h>
#include <StableMarriage/NumberOfSMFunctions.h>
#include <StableMarriage/MatrixManipFunctions.h>
#include <StableMarriage/UIUtils.h>
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <limits>

void optionL(){
    clearScreen();
    std::cout << "--- Test Latin Matrix ---\n\n";

    std::string fileName;
    largest = 0;
    int Counter = 1, latinVal;
    
    std::cout << "Enter file name: ";
    std::cin >> fileName;
    std::ifstream inputFile;
    inputFile.open("/Users/ryan/Desktop/" + fileName);
    if (!inputFile) {
        std::cout << "Error opening file.txt" << '\n';
        std::exit(1);
    }
    while (inputFile >> latinVal){
        matrix[0][0].m = latinVal - 1;
        matrix[0][0].w = n - latinVal;
        for (int i = 0; i < n; i ++){
            for(int j = 0; j < n; j++){
                if (i == 0 && j == 0) continue;
                inputFile >> latinVal;
                matrix[i][j].m = latinVal - 1;
                matrix[i][j].w = n - latinVal;
            }
        }
        auto start = std::chrono::high_resolution_clock::now();
        numberOfStableMatchings();
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
         
        std::cout << "Time taken by profile " << Counter << ": "
        << duration.count() << " milliseconds" << "\n\n";
        Counter++;
    }

    std::cout << "Most number of stable matchings: " << largest << '\n' << '\n';
    printHistogram();
    inputFile.close();

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
