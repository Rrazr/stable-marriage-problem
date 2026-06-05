#include <StableMarriage/OptionG.h>
#include <StableMarriage/Globals.h>
#include <StableMarriage/NumberOfSMFunctions.h>
#include <StableMarriage/MatrixManipFunctions.h>
#include <StableMarriage/UIUtils.h>
#include <iostream>
#include <chrono>
#include <limits>

void optionG() {
    clearScreen();
    std::cout << "--- Generate And Calculate Random Samples ---\n\n";

    int numSamples;
    std::cout << "Enter the number of samples: ";
    std::cin >> numSamples;

    auto start = std::chrono::high_resolution_clock::now();
    clearHistogram();
    for (int i = 0; i < numSamples; i ++){
        randomizer();
        numberOfStableMatchings();
    }
    std::cout << "\nHistogram:\n";
    printHistogram(numSamples);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "\nTime taken by function: " << duration.count() << " ms" << "\n\n";

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
