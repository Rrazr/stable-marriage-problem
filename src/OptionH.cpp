#include <StableMarriage/OptionH.h>
#include <StableMarriage/Globals.h>
#include <StableMarriage/NumberOfSMFunctions.h>
#include <StableMarriage/MatrixManipFunctions.h>
#include <StableMarriage/UIUtils.h>
#include <iostream>
#include <fstream>

void optionH(){
    clearScreen();
    std::cout << "--- Hill Climbing Search ---\n\n";

    bool notFromFile = false;
    std::cout << "(A) Randomized matrix\n";
    std::cout << "(B) Input normal matrix\n";
    std::cout << "(C) Input Latin matrix\n";
    std::cout << "(D) Input File\n";
    std::cout << "(E) Misc.\n\n";
    std::cout << "Enter choice: ";
    std::cin >> ch;
    if (ch == 'A' || ch == 'a'){
        randomizer();
        notFromFile = true;
    }else if (ch == 'B' || ch == 'b'){
        int m, w;
        for (int i = 0; i < n; i ++){
            std::cout << "Enter Row " << i + 1 << ": ";
            for (int j = 0; j < n; j ++){
                std::cin >> m >> w;
                matrix[i][j].m = m - 1;
                matrix[i][j].w = w - 1;
            }
        }
        std::cout << "This is the given matrix:\n";
        for (int i = 0; i < n; i ++){
            for (int j = 0; j < n; j ++){
                std::cout << matrix[i][j].m + 1 << ',' << matrix[i][j].w + 1 << "  ";
            }
            std::cout << '\n';
        }
        notFromFile = true;
    }else if (ch == 'C' || ch == 'c'){
        int num;
        for (int i = 0; i < n; i ++){
            std::cout << "Enter Row " << i + 1 << ": ";
            for(int j = 0; j < n; j++){
                std::cin >> num;
                matrix[i][j].m = num - 1;
                matrix[i][j].w = n - num;
            }
        }
        std::cout << "This is the given matrix:\n";
        for (int i = 0; i < n; i ++){
            for (int j = 0; j < n; j ++){
                std::cout << matrix[i][j].m + 1 << ',' << matrix[i][j].w + 1 << "  ";
            }
            std::cout << '\n';
        }
        notFromFile = true;
    }else if (ch == 'E' || ch =='e'){
        int i;
        for (i = 0; i < 1000; i ++){
            randomizer();
            largest = 0;
            numberOfStableMatchings();
            fattest = largest;
            for (int i = 0; i < n; i ++){
                for (int j = 0; j < n; j ++){
                    fattestMatrix[i][j].m = largestMatrix[i][j].m;
                    fattestMatrix[i][j].w = largestMatrix[i][j].w;
                }
            }
            while (1) {
                largest = 0;
                for (int i = 0; i < n; i ++){
                    for (int j = 0; j < n - 1; j ++){
                        for (int k = j + 1; k < n; k ++){
                            swapMen(i, j, k);
                            numberOfStableMatchings();
                            swapMen(i, j, k);
                        }
                    }
                }
                for (int i = 0; i < n; i ++){
                    for (int j = 0; j < n - 1; j ++){
                        for (int k = j + 1; k < n; k ++){
                            swapWomen(i, j, k);
                            numberOfStableMatchings();
                            swapWomen(i, j, k);
                        }
                    }
                }
                if (largest <= fattest){
                    break;
                }
                else{
                    std::cout << "Largest: " << largest << '\n';
                    fattest = largest;
                    for (int i = 0; i < n; i ++){
                        for (int j = 0; j < n; j ++){
                            fattestMatrix[i][j].m = largestMatrix[i][j].m;
                            fattestMatrix[i][j].w = largestMatrix[i][j].w;
                            matrix[i][j].m = largestMatrix[i][j].m;
                            matrix[i][j].w = largestMatrix[i][j].w;
                        }
                    }
                }
            }
            histogram[fattest] ++;
            mean += fattest;
            std::cout << "Fattest: " << fattest << '\n';
        }
        printHistogram();
    }
    
    if (notFromFile){
        largest = 0;
        numberOfStableMatchings();
        fattest = largest;
        for (int i = 0; i < n; i ++){
            for (int j = 0; j < n; j ++){
                fattestMatrix[i][j].m = largestMatrix[i][j].m;
                fattestMatrix[i][j].w = largestMatrix[i][j].w;
            }
        }
        while (1) {
            largest = 0;
            for (int i = 0; i < n; i ++){
                for (int j = 0; j < n - 1; j ++){
                    for (int k = j + 1; k < n; k ++){
                        swapMen(i, j, k);
                        numberOfStableMatchings();
                        swapMen(i, j, k);
                    }
                }
            }
            for (int i = 0; i < n; i ++){
                for (int j = 0; j < n - 1; j ++){
                    for (int k = j + 1; k < n; k ++){
                        swapWomen(i, j, k);
                        numberOfStableMatchings();
                        swapWomen(i, j, k);
                    }
                }
            }
            if (largest <= fattest){
                std::cout << 1 << '\n';
                break;
            }else{
                std::cout << "Largest: " << largest << '\n';
                fattest = largest;
                for (int i = 0; i < n; i ++){
                    for (int j = 0; j < n; j ++){
                        fattestMatrix[i][j].m = largestMatrix[i][j].m;
                        fattestMatrix[i][j].w = largestMatrix[i][j].w;
                        matrix[i][j].m = largestMatrix[i][j].m;
                        matrix[i][j].w = largestMatrix[i][j].w;
                    }
                }
            }
        }
        std::cout << "Fattest: " << fattest << '\n';
    }else if (!notFromFile && (ch == 'D' || ch == 'd')){
        std::string randy;
        int counter = 0;
        int randyInt;
        int seedSM;
        std::ofstream outputFile;
        outputFile.open("/Users/ryan/Desktop/6CrossTo7AllMatricesAfterHC.txt", std::ios::app);
        std::string fileName;
        std::cout << "Enter file name: ";
        std::cin >> fileName;
        std::ifstream inputFile("/Users/ryan/Desktop/" + fileName);
        while(inputFile >> randy){
            int m, w;
            for (int i = 0; i < 3; i ++){
                inputFile >> randy;
            }
            inputFile >> randyInt;
            for (int i = 0; i < n; i ++){
                for (int j = 0; j < n; j ++){
                    inputFile >> m >> w;
                    matrix[i][j].m = m - 1;
                    matrix[i][j].w = w - 1;
                }
            }
            largest = 0;
            numberOfStableMatchings();
            seedSM = largest;
            fattest = largest;
            for (int i = 0; i < n; i ++){
                for (int j = 0; j < n; j ++){
                    fattestMatrix[i][j].m = largestMatrix[i][j].m;
                    fattestMatrix[i][j].w = largestMatrix[i][j].w;
                }
            }
            while (1) {
                largest = 0;
                for (int i = 0; i < n; i ++){
                    for (int j = 0; j < n - 1; j ++){
                        for (int k = j + 1; k < n; k ++){
                            swapMen(i, j, k);
                            numberOfStableMatchings();
                            swapMen(i, j, k);
                        }
                    }
                }
                for (int i = 0; i < n; i ++){
                    for (int j = 0; j < n - 1; j ++){
                        for (int k = j + 1; k < n; k ++){
                            swapWomen(i, j, k);
                            numberOfStableMatchings();
                            swapWomen(i, j, k);
                        }
                    }
                }
                if (largest <= fattest){
                    std::cout << 1 << '\n';
                    break;
                }else{
                    std::cout << "Largest: " << largest << '\n';
                    fattest = largest;
                    for (int i = 0; i < n; i ++){
                        for (int j = 0; j < n; j ++){
                            fattestMatrix[i][j].m = largestMatrix[i][j].m;
                            fattestMatrix[i][j].w = largestMatrix[i][j].w;
                            matrix[i][j].m = largestMatrix[i][j].m;
                            matrix[i][j].w = largestMatrix[i][j].w;
                        }
                    }
                }
            }
            outputFile << "Seed: " << seedSM << '\n';
            outputFile << "Number of Stable Marriages: " << fattest << '\n';
            for (int i = 0; i < n; i ++){
                for (int j = 0; j < n; j ++){
                    outputFile << fattestMatrix[i][j].m + 1 << ' ' << fattestMatrix[i][j].w + 1 << "  ";
                }
                outputFile << '\n';
            }
            histogram[fattest]++;
            mean += fattest;
            counter ++;
            std::cout << "Counter: " << counter << '\n';
        }
        printHistogram();
        inputFile.close();
        outputFile.close();
    }
}
