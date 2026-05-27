#include <StableMarriage/OptionR.h>
#include <StableMarriage/Globals.h>
#include <StableMarriage/NumberOfSMFunctions.h>
#include <StableMarriage/MatrixManipFunctions.h>
#include <StableMarriage/UIUtils.h>
#include <iostream>
#include <chrono>

void optionR() {
    clearScreen();
    std::cout << "--- Generate And Calculate Random Samples ---\n\n";

    auto start = std::chrono::high_resolution_clock::now();
    clearHistogram();
    for (int i = 0; i < 1000; i ++){
        randomizer();
        numberOfStableMatchings();
    }
    std::cout << "Histogram:\n";
    printHistogram();
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Time taken by function: " << duration.count() << " ms" << std::endl << '\n';
}
