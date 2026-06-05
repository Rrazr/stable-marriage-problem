#include <StableMarriage/OptionR.h>
#include <StableMarriage/Globals.h>
#include <StableMarriage/NumberOfSMFunctions.h>
#include <StableMarriage/MatrixManipFunctions.h>
#include <StableMarriage/UIUtils.h>
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <ios>
#include <limits>

void dropToOneLessN(const std::string& inputFilename, const std::string& outputFilename, bool printSMCount){
    // sourceN is the size of the matrix we are reading (one larger than current system n)
    int sourceN = n + 1;

    // Construct cross-platform paths
    std::filesystem::path inputPath = std::filesystem::path("inputs") / inputFilename;
    std::filesystem::path outputPath = std::filesystem::path("outputs") / outputFilename;

    // Ensure outputs directory exists
    std::filesystem::create_directories("outputs");

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


    int m;
    for (int i = 0; i < sourceN; i++)
    {
        for (int j = 0; j < sourceN; j++)
        {
            inputFile >> m;
            startNArray[i][j] = m;
        }
    }

    int row = 0;
    int col = 0;
    int maxSM = 0;

    for (int badRow = 0; badRow < sourceN; badRow++)
    {
        for (int badCol = 0; badCol < sourceN; badCol++)
        {
            row = 0;
            col = 0;

            for (int i = 0; i < sourceN; i++)
            {
                for (int j = 0; j < sourceN; j++)
                {
                    if ((i != badRow && j != badCol))
                    {
                        matrix[row][col].m = startNArray[i][j];
                        matrix[row][col].w = sourceN + 1 - matrix[row][col].m;

                        if (col == n - 1)
                        {
                            row++;
                        }
                        col = (col + 1) % n;
                    }
                }
            }

            convertToGeneral();
            numberOfStableMatchings();
            if (printSMCount) {
                outputFile << "Number of SM is " << cnt << '\n';
            }

            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    outputFile << matrix[i][j].m + 1 << ' ' << matrix[i][j].w + 1 << "  ";
                }
                outputFile << '\n';
            }
            outputFile << '\n';

            if (cnt > maxSM)
            {
                maxSM = cnt;
            }
        }
    }
    

    outputFile.close();
    inputFile.close();
    std::cout << '\n' << "Max SM is " << maxSM << '\n';
}

void optionR() {
    clearScreen();
    std::cout << "--- Matrix Reduction ---\n\n";
    std::cout << "Target Size (n): " << n << "\n";
    std::cout << "Source Size: " << n + 1 << "\n\n";

    std::string inputFilename, outputFilename;

    // Clear the input buffer of any leftover newline characters from main menu selection
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter input filename (default: input.txt): ";
    std::getline(std::cin, inputFilename);
    if (inputFilename.empty()) {
        inputFilename = "input.txt";
    } else if (std::filesystem::path(inputFilename).extension() != ".txt") {
        inputFilename += ".txt";
    }

    std::cout << "Enter output filename (default: output.txt): ";
    std::getline(std::cin, outputFilename);
    if (outputFilename.empty()) {
        outputFilename = "output.txt";
    } else if (std::filesystem::path(outputFilename).extension() != ".txt") {
        outputFilename += ".txt";
    }

    std::string smChoice;
    std::cout << "Print SM count for each matrix? (Y/N, default: N): ";
    std::getline(std::cin, smChoice);
    bool printSMCount = (smChoice == "Y" || smChoice == "y");

    std::cout << "\nReducing matrix from " << n + 1 << " to " << n << "...\n";
    dropToOneLessN(inputFilename, outputFilename, printSMCount);

    std::cout << "\nMatrix reduction complete\n\n";
}
