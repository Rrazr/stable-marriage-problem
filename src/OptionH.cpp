#include <StableMarriage/OptionH.h>
#include <StableMarriage/Globals.h>
#include <StableMarriage/NumberOfSMFunctions.h>
#include <StableMarriage/MatrixManipFunctions.h>
#include <StableMarriage/UIUtils.h>
#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include <filesystem>

inline void updateLargestIfBetter() {
    if (cnt > largest) {
        largest = cnt;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                largestMatrix[i][j].m = matrix[i][j].m;
                largestMatrix[i][j].w = matrix[i][j].w;
            }
        }
    }
}

void hillClimb() {
    largest = 0;
    numberOfStableMatchings();
    localMax = cnt;
    for (int i = 0; i < n; i ++){
        for (int j = 0; j < n; j ++){
            localMaxMatrix[i][j].m = matrix[i][j].m;
            localMaxMatrix[i][j].w = matrix[i][j].w;
        }
    }
    while (1) {
        largest = 0;
        for (int i = 0; i < n; i ++){
            for (int j = 0; j < n - 1; j ++){
                for (int k = j + 1; k < n; k ++){
                    swapMen(i, j, k);
                    numberOfStableMatchings();
                    updateLargestIfBetter();
                    swapMen(i, j, k);
                }
            }
        }
        for (int i = 0; i < n; i ++){
            for (int j = 0; j < n - 1; j ++){
                for (int k = j + 1; k < n; k ++){
                    swapWomen(i, j, k);
                    numberOfStableMatchings();
                    updateLargestIfBetter();
                    swapWomen(i, j, k);
                }
            }
        }
        if (largest <= localMax){
            break;
        }else{
            std::cout << "Largest: " << largest << '\n';
            localMax = largest;
            for (int i = 0; i < n; i ++){
                for (int j = 0; j < n; j ++){
                    localMaxMatrix[i][j].m = largestMatrix[i][j].m;
                    localMaxMatrix[i][j].w = largestMatrix[i][j].w;
                    matrix[i][j].m = largestMatrix[i][j].m;
                    matrix[i][j].w = largestMatrix[i][j].w;
                }
            }
        }
    }
}

void optionH(){
    clearScreen();
    clearHistogram();
    std::cout << "--- Hill Climbing Search ---\n\n";

    std::cout << "(A) Randomized matrix\n";
    std::cout << "(B) Standard matrices\n";
    std::cout << "(C) Latin matrices\n\n";
    std::cout << "Enter choice: ";
    std::cin >> ch;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << '\n';

    if (ch == 'A' || ch == 'a'){
        randomizer();
        hillClimb();
        std::cout << "\nLocal Max: " << localMax << "\n\n";
    }
    else if (ch == 'B' || ch == 'b' || ch == 'C' || ch == 'c') {
        std::filesystem::path inputPath, outputPath;
        getIOFilePaths(inputPath, outputPath);

        std::ifstream inputFile(inputPath);
        if (!inputFile) {
            std::cout << "\n[ERROR] Could not open input file: " << inputPath.string() << "\n";
            std::cout << "Please ensure the file is located in the 'inputs' folder.\n";
            return;
        }

        std::ofstream outputFile(outputPath);
        if (!outputFile) {
            std::cout << "\n[ERROR] Could not create output file: " << outputPath.string() << "\n";
            return;
        }

        std::cout << "\n";

        int counter = 0;
        if (ch == 'B' || ch == 'b') {
            int m, w;
            while (inputFile >> m >> w) {
                matrix[0][0].m = m - 1;
                matrix[0][0].w = w - 1;
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                        if (i == 0 && j == 0) continue;
                        inputFile >> m >> w;
                        matrix[i][j].m = m - 1;
                        matrix[i][j].w = w - 1;
                    }
                }
                hillClimb();
                outputFile << "Number of Stable Marriages: " << localMax << '\n';
                for (int i = 0; i < n; i ++){
                    for (int j = 0; j < n; j ++){
                        outputFile << localMaxMatrix[i][j].m + 1 << ' ' << localMaxMatrix[i][j].w + 1 << "  ";
                    }
                    outputFile << '\n';
                }
                outputFile << '\n';
                histogram[localMax]++;
                mean += localMax;
                counter++;
                std::cout << "Hill-climbed matrix " << counter << " (Local Max: " << localMax << ")\n\n";
            }
        }
        else {
            int latinVal;
            while (inputFile >> latinVal) {
                matrix[0][0].m = latinVal - 1;
                matrix[0][0].w = n - latinVal;
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                        if (i == 0 && j == 0) continue;
                        inputFile >> latinVal;
                        matrix[i][j].m = latinVal - 1;
                        matrix[i][j].w = n - latinVal;
                    }
                }
                convertToGeneral();
                hillClimb();
                outputFile << "Number of Stable Marriages: " << localMax << '\n';
                for (int i = 0; i < n; i ++){
                    for (int j = 0; j < n; j ++){
                        outputFile << localMaxMatrix[i][j].m + 1 << ' ' << localMaxMatrix[i][j].w + 1 << "  ";
                    }
                    outputFile << '\n';
                }
                outputFile << '\n';
                histogram[localMax]++;
                mean += localMax;
                counter++;
                std::cout << "Hill-climbed matrix " << counter << " (Local Max: " << localMax << ")\n";
            }
        }

        std::cout << "\nHill-climbed " << counter << " matrices\n";
        printHistogram(counter);
        std::cout << "\n";

        inputFile.close();
        outputFile.close();
    }
}
