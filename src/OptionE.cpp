#include <StableMarriage/OptionE.h>
#include <StableMarriage/Globals.h>
#include <StableMarriage/NumberOfSMFunctions.h>
#include <StableMarriage/MatrixManipFunctions.h>
#include <StableMarriage/UIUtils.h>
#include <iostream>
#include <fstream>
#include <string>

void optionE(){
    clearScreen();
    std::cout << "--- Extract Top Seeds ---\n\n";

    std::string fileName, randStr;
    int SM, m, w, topSeed = 0;
    std::cout << "Enter seeds file: ";
    std::cin >> fileName;
    std::ifstream seedsFile;
    std::ofstream outputFile;
    seedsFile.open("/Users/ryan/Desktop/" + fileName);
    while (seedsFile >> randStr){
        for (int i = 0; i < 3; i ++){
            seedsFile >> randStr;
        }
        seedsFile >> SM;
        topSeed = SM > topSeed ? SM : topSeed;
        for (int i = 0; i < n; i ++){
            for (int j = 0; j < n; j ++){
                seedsFile >> m >> w;
            }
        }
    }
    std::cout << "Top Seed: " << topSeed << '\n';
    seedsFile.close();
    seedsFile.open("/Users/ryan/Desktop/" + fileName);
    std::string name = "/Users/ryan/Desktop/16CrossTo15TopSeeds" + std::to_string(topSeed) + ".txt";
    outputFile.open(name, std::ios::app);
    while (seedsFile >> randStr){
        for (int i = 0; i < 3; i ++){
            seedsFile >> randStr;
        }
        seedsFile >> SM;
        if (SM == topSeed){
            outputFile << "Number of SM is " << topSeed << '\n';
        }
        for (int i = 0; i < n; i ++){
            for (int j = 0; j < n; j ++){
                seedsFile >> m >> w;
                if (SM == topSeed){
                    outputFile << m << " " << w << "  ";
                }
            }
            if (SM == topSeed){
                outputFile << '\n';
            }
        }
        if (SM == topSeed){
            outputFile << '\n';
        }
        std::cout << "SM: " << SM << '\n';
    }
    seedsFile.close();
    outputFile.close();
}
