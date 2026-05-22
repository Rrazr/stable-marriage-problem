#include <StableMarriage/OptionG.h>
#include <StableMarriage/Globals.h>
#include <StableMarriage/NumberOfSMFunctions.h>
#include <StableMarriage/MatrixManipFunctions.h>
#include <iostream>

void optionG() {
    int nEntered = 0;
    std::cout << "Enter the n you would like to start with " << std::endl;
    std::cin >> nEntered;
    int high = 0;
    high = cnt;
    for(int i = 0; i < 1000; i++){
        increaseNByOne(nEntered);
        histogram[cnt]++;
        if(high < cnt){
            high = cnt;
        }
    }
    for(int j = 0; j < 75; j++){
        std::cout << histogram[j] << " matrices have " << j << " SMs";
        std::cout << std::endl;
    }
    std::cout <<"The high is " << high;
}
