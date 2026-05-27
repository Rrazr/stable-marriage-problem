#include <StableMarriage/OptionR.h>
#include <StableMarriage/Globals.h>
#include <StableMarriage/NumberOfSMFunctions.h>
#include <StableMarriage/MatrixManipFunctions.h>
#include <StableMarriage/UIUtils.h>
#include <iostream>
#include <fstream>
#include <string>

void dropToOneLessN(int orignalN){
    int badRow = 0;
    int badCol = 0;
    int row = 0;
    int col = 0;
    int count = 0;
    int max = 0;
    int lastIteraation = 0;

    for (int i = 0; i < orignalN; i++)
    {
        for (int j = 0; j < orignalN; j++)
        {
            displayArr[i][j] = 0;
        }
    }
    std::ifstream FileToRead;
    FileToRead.open("/Users/thecownextdoorr/Desktop/eightcross.txt");
    std::ofstream specialMatrixFile("/Users/thecownextdoorr/Desktop/eightToSevenForHeatMap.txt", std::ios::app);
    std::string str;

    while (FileToRead >> str)
    {
        badRow = 0;
        badCol = 0;
        row = 0;
        col = 0;
        max = 0;
        lastIteraation = 0;
        int m;
        for (int i = 0; i < n + 1; i++)
        {
            for (int j = 0; j < n + 1; j++)
            {
                FileToRead >> m;
                startNArray[i][j] = m;
            }
        }
        do
        {
            row = 0;
            col = 0;
            for (int i = 0; i < orignalN; i++)
            {
                for (int j = 0; j < orignalN; j++)
                {
                    if ((i != badRow && j != badCol))
                    {
                        matrix[row][col].m = startNArray[i][j];
                        matrix[row][col].w = n - matrix[row][col].m;
                        if (col < orignalN - 2)
                        {
                            col++;
                        }
                        else if (col == orignalN - 2)
                        {
                            col = 0;
                            row++;
                        }
                    }
                }
            }
            convertToGeneral();
            numberOfStableMatchings();
            specialMatrixFile << "Number of SM is " << cnt << '\n';
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    specialMatrixFile << matrix[i][j].m + 1 << ' ' << matrix[i][j].w + 1 << "  ";
                }
                specialMatrixFile << '\n';
            }
            if (cnt > max)
            {
                max = cnt;
            }
            updateDisplayArray(badRow, badCol);
            if (badRow == orignalN - 1 && badCol == orignalN - 1)
            {
                lastIteraation++;
            }
            else if (badRow < orignalN - 1)
            {
                badRow++;
            }
            else if (badRow == orignalN - 1)
            {
                badCol++;
                badRow = 0;
            }
        } while ((badRow != orignalN || badCol != orignalN) && lastIteraation != 1);
        count++;
        specialMatrixFile << "Count is " << count << '\n';
        for (int i = 0; i < n + 1; i++)
        {
            for (int j = 0; j < n + 1; j++)
            {
                specialMatrixFile << startNArray[i][j] + 1 << " ";
            }
            specialMatrixFile << '\n';
        }
        for (int i = 0; i < n + 1; i++)
        {
            for (int j = 0; j < n + 1; j++)
            {
                specialMatrixFile << displayArr[i][j] << "   ";
            }
            specialMatrixFile << '\n';
        }
        std::cout << "count is " << count << '\n';
    }
    specialMatrixFile.close();
    FileToRead.close();
    std::cout << '\n' << "max is " << max << '\n';
    std::cout << "count is " << count << '\n';
}

void optionR() {
    clearScreen();
    std::cout << "--- Matrix Reduction ---\n\n";

    int startingN;
    std::cout << "Enter the n you would like to start with: ";
    std::cin >> startingN;
    
    std::cout << "\nReducing matrix to n - 1...\n";
    dropToOneLessN(startingN);

    std::cout << "\nMatrix reduction complete\n";
}
