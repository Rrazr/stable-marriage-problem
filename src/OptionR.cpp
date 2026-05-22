#include <StableMarriage/OptionR.h>
#include <StableMarriage/Globals.h>
#include <StableMarriage/NumberOfSMFunctions.h>
#include <StableMarriage/MatrixManipFunctions.h>
#include <iostream>
#include <chrono>

void optionR() {
    auto start = std::chrono::high_resolution_clock::now();
    clearHistogram();
    for (int i = 0; i < 1000; i ++){
        randomizer();
        numberOfStableMatchings();
    }
    std::cout << "Histogram 1:\n";
    printHistogram();
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Time taken by function: " << duration.count() << " milliseconds" << std::endl << '\n';
}
