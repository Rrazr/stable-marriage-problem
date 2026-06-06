#include <StableMarriage/OptionC.h>
#include <StableMarriage/Globals.h>
#include <StableMarriage/NumberOfSMFunctions.h>
#include <StableMarriage/MatrixManipFunctions.h>
#include <StableMarriage/UIUtils.h>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <limits>

void optionC(){
    clearScreen();
    std::cout << "--- Calculate Stable Marriages for Matrices ---\n\n";

    std::cout << "(A) Standard matrices\n";
    std::cout << "(B) Latin matrices\n\n";
    std::cout << "Enter choice: ";
    
    char choice;
    std::cin >> choice;
    
    // Clear newline
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << '\n';

    if (choice != 'A' && choice != 'a' && choice != 'B' && choice != 'b') {
        std::cout << "Invalid choice.\n";
        return;
    }

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

    clearHistogram();
    int counter = 0;

    if (choice == 'A' || choice == 'a') {
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
            
            numberOfStableMatchings();

            histogram[cnt]++;
            mean += cnt;

            outputFile << "Number of SM is " << cnt << '\n';

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    outputFile << matrix[i][j].m + 1 << ' ' << matrix[i][j].w + 1 << "  ";
                }
                outputFile << '\n';
            }
            outputFile << '\n';

            counter++;
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
            numberOfStableMatchings();

            histogram[cnt]++;
            mean += cnt;

            outputFile << "Number of SM is " << cnt << '\n';

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    outputFile << matrix[i][j].m + 1 << ' ' << matrix[i][j].w + 1 << "  ";
                }
                outputFile << '\n';
            }
            outputFile << '\n';

            counter++;
        }
    }

    std::cout << "\nProcessed " << counter << " matrices\n";
    printHistogram(counter);
    std::cout << "\n";
    
    inputFile.close();
    outputFile.close();
}
