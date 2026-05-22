#include <StableMarriage/OptionB.h>
#include <StableMarriage/Globals.h>
#include <StableMarriage/NumberOfSMFunctions.h>
#include <StableMarriage/MatrixManipFunctions.h>
#include <iostream>
#include <fstream>

void optionB(){
    bool inputFromFile = true;
    
    // Choose Input Method
    std::cout << '\n';
    std::cout << "(A) Randomized matrix\n";
    std::cout << "(B) Input normal matrix\n";
    std::cout << "(C) Input Latin matrix\n";
    std::cout << "(D) Input file\n\n";
    std::cout << "Enter choice: ";
    std::cin >> ch;
    if (ch == 'A' || ch == 'a'){
        randomizer();
        inputFromFile = false;
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
        inputFromFile = false;
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
        inputFromFile = false;
    }
    
    // Choose Generation Mode
    std::cout << '\n';
    std::cout << "(A) Systematic Generation\n";
    std::cout << "(B) Random Generation\n\n";
    std::cout << "Enter choice: ";
    std::cin >> ch;
    
    if (!inputFromFile){
        largest = 0;
        numberOfStableMatchings();
        std::cout << "Starting number: " << largest << '\n';
        fattest = largest;
        for (int i = 0; i < n; i ++){
            for (int j = 0; j < n; j ++){
                fattestMatrix[i][j].m = largestMatrix[i][j].m;
                fattestMatrix[i][j].w = largestMatrix[i][j].w;
            }
        }
        if (ch == 'A' || ch == 'a'){
            while (1) {
                largest = 0;
                bool endIteration = false;
                for (int i = 0; i < n; i ++){
                    for (int j = 0; j < n - 1; j ++){
                        for (int k = j + 1; k < n; k ++){
                            swapMen(i, j, k);
                            numberOfStableMatchings();
                            if (largest > fattest){
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
                                if (largest > 71){
                                    std::ofstream outputFile;
                                    outputFile.open("/Users/ryan/Desktop/greaterThanSeventyOne.txt");
                                    outputFile << "Number of Stable Marriages: " << largest << '\n';
                                    for (int i = 0; i < n; i ++){
                                        for (int j = 0; j < n; j ++){
                                            std::cout << largestMatrix[i][j].m + 1 << ',' << largestMatrix[i][j].w + 1 << "  ";
                                        }
                                        std::cout << '\n';
                                    }
                                    outputFile.close();
                                }
                                endIteration = true;
                                break;
                            }
                            swapMen(i, j, k);
                        }
                        if (endIteration){
                            break;
                        }
                    }
                    if (endIteration){
                        break;
                    }
                }
                if (!endIteration){
                    for (int i = 0; i < n; i ++){
                        for (int j = 0; j < n - 1; j ++){
                            for (int k = j + 1; k < n; k ++){
                                swapWomen(i, j, k);
                                numberOfStableMatchings();
                                if (largest > fattest){
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
                                    if (largest > 71){
                                        std::ofstream outputFile;
                                        outputFile.open("/Users/ryan/Desktop/greaterThanSeventyOne.txt");
                                        outputFile << "Number of Stable Marriages: " << largest << '\n';
                                        for (int i = 0; i < n; i ++){
                                            for (int j = 0; j < n; j ++){
                                                std::cout << largestMatrix[i][j].m + 1 << ',' << largestMatrix[i][j].w + 1 << "  ";
                                            }
                                            std::cout << '\n';
                                        }
                                        outputFile.close();
                                    }
                                    endIteration = true;
                                    break;
                                }
                                swapWomen(i, j, k);
                            }
                            if (endIteration){
                                break;
                            }
                        }
                        if (endIteration){
                            break;
                        }
                    }
                }
                if (!endIteration){
                    std::cout << 1 << '\n';
                    break;
                }
            }
        }else if (ch == 'B' || ch == 'b'){
            int ind, ind2, ind3, temp = 0;
            PAIR Temp[n][n];
            while (1) {
                bool endIteration = true;
                for (int i = 0; i < 10; i ++){
                    std::cout << i << '\n';
                    ind = std::rand() % 2;
                    if (ind == 0){
                        ind = std::rand() % n;
                        ind2 = std::rand() % n;
                        do{
                            ind3 = std::rand() % n;
                        }while (ind3 == ind2);
                        swapMen(ind, ind2, ind3);
                        numberOfStableMatchings();
                        
                        if (largest > temp){
                            endIteration = false;
                            temp = largest;
                            for (int i = 0; i < n; i ++){
                                for (int j = 0; j < n; j ++){
                                    Temp[i][j].m = largestMatrix[i][j].m;
                                    Temp[i][j].w = largestMatrix[i][j].w;
                                }
                            }
                            if (largest > 71){
                                std::ofstream outputFile;
                                outputFile.open("/Users/ryan/Desktop/greaterThanSeventyOne.txt");
                                outputFile << "Number of Stable Marriages: " << largest << '\n';
                                for (int i = 0; i < n; i ++){
                                    for (int j = 0; j < n; j ++){
                                        std::cout << largestMatrix[i][j].m + 1 << ',' << largestMatrix[i][j].w + 1 << "  ";
                                    }
                                    std::cout << '\n';
                                }
                                outputFile.close();
                            }
                        }
                        swapMen(ind, ind2, ind3);
                    }else if (ind == 1){
                        ind = std::rand() % n;
                        ind2 = std::rand() % n;
                        do{
                            ind3 = std::rand() % n;
                        }while (ind3 == ind2);
                        swapWomen(ind, ind2, ind3);
                        numberOfStableMatchings();
                        
                        if (largest > temp){
                            endIteration = false;
                            temp = largest;
                            for (int i = 0; i < n; i ++){
                                for (int j = 0; j < n; j ++){
                                    Temp[i][j].m = largestMatrix[i][j].m;
                                    Temp[i][j].w = largestMatrix[i][j].w;
                                }
                            }
                            if (largest > 71){
                                std::ofstream outputFile;
                                outputFile.open("/Users/ryan/Desktop/greaterThanSeventyOne.txt");
                                outputFile << "Number of Stable Marriages: " << largest << '\n';
                                for (int i = 0; i < n; i ++){
                                    for (int j = 0; j < n; j ++){
                                        std::cout << largestMatrix[i][j].m + 1 << ',' << largestMatrix[i][j].w + 1 << "  ";
                                    }
                                    std::cout << '\n';
                                }
                                outputFile.close();
                            }
                        }
                        swapWomen(ind, ind2, ind3);
                    }
                }
                if (temp > fattest){
                    for (int i = 0; i < n; i ++){
                        for (int j = 0; j < n; j ++){
                            fattestMatrix[i][j].m = Temp[i][j].m;
                            fattestMatrix[i][j].w = Temp[i][j].w;
                            matrix[i][j].m = Temp[i][j].m;
                            matrix[i][j].w = Temp[i][j].w;
                        }
                    }
                }
                if (endIteration){
                    std::cout << 1 << '\n';
                    break;
                }
            }
        }
        std::cout << "Fattest: " << fattest << '\n';
        std::cout << "Matrix:\n";
        for (int i = 0; i < n; i ++){
            for (int j = 0; j < n; j ++){
                std::cout << fattestMatrix[i][j].m + 1 << ',' << fattestMatrix[i][j].w + 1 << "  ";
            }
            std::cout << '\n';
        }
    }else{
        std::string fileName;
        std::cout << "Enter file name: ";
        std::cin >> fileName;
        std::ifstream inputFile("/Users/ryan/Desktop/" + fileName);
        while(inputFile >> ch){
            int m, w;
            for (int i = 0; i < n; i ++){
                for (int j = 0; j < n; j ++){
                    inputFile >> m >> w;
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
            
            largest = 0;
            numberOfStableMatchings();
            std::cout << "Starting number: " << largest << '\n';
            fattest = largest;
            for (int i = 0; i < n; i ++){
                for (int j = 0; j < n; j ++){
                    fattestMatrix[i][j].m = largestMatrix[i][j].m;
                    fattestMatrix[i][j].w = largestMatrix[i][j].w;
                }
            }
        }
    }
}
