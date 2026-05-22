#include <StableMarriage/OptionS.h>
#include <StableMarriage/Globals.h>
#include <StableMarriage/NumberOfSMFunctions.h>
#include <StableMarriage/MatrixManipFunctions.h>
#include <iostream>

bool isStableMatching(){
    for (int i = 1; i < n; i ++){
        for (int j = 0; j < i; j ++){
            if (matrix[i][matching[j]].m < matrix[i][matching[i]].m &&
                matrix[i][matching[j]].w < matrix[j][matching[j]].w) {
                return false;
            }else if (matrix[j][matching[i]].m < matrix[j][matching[j]].m &&
                      matrix[j][matching[i]].w < matrix[i][matching[i]].w){
                return false;
            }
        }
    }
    return true;
}

void optionS() {
    int num;
    std::cout << "Enter matchings in order:\n";
    for (int i = 0; i < n; i ++){
        std::cout << "Man " << i + 1 << "'s pair: ";
        std::cin >> num;
        matching[i] = num - 1;
    }
    for (int i = 0; i < n; i ++){
        std::cout << matching[i] << " ";
    }
    std::cout << '\n';
    std::cout << (isStableMatching() ? "The given matching is stable\n" : "The given matching is unmatching\n");
    std::cout << '\n' << '\n';
}
